// Win32 GUI app: Dining Philosophers (Dijkstra-style)
// - Global binary semaphore guards state[] and signaling
// - Private semaphores s[i] unblock philosophers when forks free
// - GUI: colored labels for states + protocol log
// - Clean shutdown and thread-safe UI updates via posted messages

#include <windows.h>
#include <process.h>
#include <stdio.h>
#include <string>
#include <vector>

#include "Resource.h"

#define N            5
#define LEFT(i)      (((i) - 1 + N) % N)
#define RIGHT(i)     (((i) + 1) % N)

#define THINKING     0
#define HUNGRY       1
#define EATING       2

typedef unsigned int(__stdcall* THREADFUNC)(void*);

// Globals
HINSTANCE g_hInst = nullptr;
HWND g_hDlg = nullptr;

static volatile LONG gRunning = FALSE;          // run flag
static int gState[N] = { THINKING, THINKING, THINKING, THINKING, THINKING };

static HANDLE hMutex = NULL;                    // binary semaphore (global mutex)
static HANDLE s[N] = { 0 };                     // private semaphores
static HANDLE threads[N] = { 0 };

static HBRUSH gBrushThinking = nullptr;
static HBRUSH gBrushHungry = nullptr;
static HBRUSH gBrushEating = nullptr;

// Forward declarations
INT_PTR CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
void InitBrushes();
void FreeBrushes();
void SetPhStateText(int i, int state);
void LogLine(const char* text);
void LogFmt(const char* fmt, ...);
void StartSimulation();
void StopSimulation();
unsigned __stdcall PhilosopherThread(void* pParam);
void think(int i);
void eat(int i);
void take_forks(int i);
void put_forks(int i);
void test(int i);
DWORD ms_since_start();

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) {
    g_hInst = hInstance;
    DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_MAIN_DIALOG), NULL, DlgProc, 0);
    return 0;
}

INT_PTR CALLBACK DlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_INITDIALOG:
        g_hDlg = hDlg;
        if (HICON hIcon = (HICON)LoadImage(g_hInst, MAKEINTRESOURCE(IDI_APPICON), IMAGE_ICON, 32, 32, 0)) {
            SendMessage(hDlg, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
            SendMessage(hDlg, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
        }
        InitBrushes();
        for (int i = 0; i < N; ++i) SetPhStateText(i, THINKING);
        EnableWindow(GetDlgItem(hDlg, IDC_STOP_BUTTON), FALSE);
        return TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDC_START_BUTTON:
            StartSimulation();
            return TRUE;
        case IDC_STOP_BUTTON:
            StopSimulation();
            return TRUE;
        case IDCANCEL:
            StopSimulation();
            EndDialog(hDlg, 0);
            return TRUE;
        }
        break;

    case WM_APP_STATE: {
        int i = (int)wParam;
        int st = (int)lParam;
        if (i >= 0 && i < N) {
            gState[i] = st;
            SetPhStateText(i, st);
        }
        return TRUE;
    }

    case WM_APP_LOG: {
        char* p = (char*)lParam;
        if (p) {
            LogLine(p);
            HeapFree(GetProcessHeap(), 0, p);
        }
        return TRUE;
    }

    case WM_CTLCOLORSTATIC: {
        HWND hCtl = (HWND)lParam;
        int id = GetDlgCtrlID(hCtl);
        if (id >= IDC_PH0 && id <= IDC_PH4) {
            int idx = id - IDC_PH0;
            HDC hdc = (HDC)wParam;
            SetBkMode(hdc, OPAQUE);
            SetTextColor(hdc, RGB(0, 0, 0));
            switch (gState[idx]) {
            case THINKING:
                SetBkColor(hdc, RGB(180, 200, 255));
                return (INT_PTR)gBrushThinking;
            case HUNGRY:
                SetBkColor(hdc, RGB(255, 220, 100));
                return (INT_PTR)gBrushHungry;
            case EATING:
                SetBkColor(hdc, RGB(160, 230, 160));
                return (INT_PTR)gBrushEating;
            }
        }
        break;
    }

    case WM_DESTROY:
        FreeBrushes();
        break;
    }
    return FALSE;
}

void InitBrushes() {
    gBrushThinking = CreateSolidBrush(RGB(180, 200, 255)); // blue-ish
    gBrushHungry   = CreateSolidBrush(RGB(255, 220, 100)); // yellow
    gBrushEating   = CreateSolidBrush(RGB(160, 230, 160)); // green
}

void FreeBrushes() {
    if (gBrushThinking) { DeleteObject(gBrushThinking); gBrushThinking = nullptr; }
    if (gBrushHungry)   { DeleteObject(gBrushHungry);   gBrushHungry   = nullptr; }
    if (gBrushEating)   { DeleteObject(gBrushEating);   gBrushEating   = nullptr; }
}

void SetPhStateText(int i, int state) {
    static const char* names[] = { "THINKING", "HUNGRY", "EATING" };
    char buf[64];
    wsprintfA(buf, "%s", names[state]);
    int id = IDC_PH0 + i;
    SetWindowTextA(GetDlgItem(g_hDlg, id), buf);
}

void LogLine(const char* text) {
    HWND hLog = GetDlgItem(g_hDlg, IDC_LOG);
    int idx = (int)SendMessage(hLog, LB_ADDSTRING, 0, (LPARAM)text);
    SendMessage(hLog, LB_SETCURSEL, idx, 0);
}

void PostLogFmt(const char* fmt, ...) {
    char* heapBuf = (char*)HeapAlloc(GetProcessHeap(), 0, 512);
    if (!heapBuf) return;
    va_list args; va_start(args, fmt);
    _vsnprintf_s(heapBuf, 512, _TRUNCATE, fmt, args);
    va_end(args);
    PostMessage(g_hDlg, WM_APP_LOG, 0, (LPARAM)heapBuf);
}

void StartSimulation() {
    if (InterlockedCompareExchange(&gRunning, TRUE, FALSE) == TRUE) return;

    // Reset UI
    SendMessage(GetDlgItem(g_hDlg, IDC_LOG), LB_RESETCONTENT, 0, 0);
    for (int i = 0; i < N; ++i) { gState[i] = THINKING; SetPhStateText(i, THINKING); }

    // Create global mutex (binary semaphore)
    if (!hMutex) {
        hMutex = CreateSemaphoreA(NULL, 1, 1, NULL);
        if (!hMutex) {
            PostLogFmt("CreateSemaphore(hMutex) failed err=%lu", GetLastError());
            InterlockedExchange(&gRunning, FALSE);
            return;
        }
    }

    // Create per-philosopher semaphores
    for (int i = 0; i < N; ++i) {
        if (!s[i]) {
            s[i] = CreateSemaphoreA(NULL, 0, 1, NULL);
            if (!s[i]) {
                PostLogFmt("CreateSemaphore(s[%d]) failed err=%lu", i, GetLastError());
                StopSimulation();
                return;
            }
        }
    }

    // Threads
    unsigned tid[N];
    for (int i = 0; i < N; ++i) {
        if (!threads[i]) {
            threads[i] = (HANDLE)_beginthreadex(NULL, 0, (THREADFUNC)PhilosopherThread, (void*)(INT_PTR)i, 0, &tid[i]);
            if (!threads[i]) {
                PostLogFmt("BeginThread philosopher %d failed", i);
                StopSimulation();
                return;
            }
        }
    }

    EnableWindow(GetDlgItem(g_hDlg, IDC_START_BUTTON), FALSE);
    EnableWindow(GetDlgItem(g_hDlg, IDC_STOP_BUTTON), TRUE);
    PostLogFmt("Simulation started.");
}

void StopSimulation() {
    if (InterlockedCompareExchange(&gRunning, FALSE, TRUE) == TRUE) {
        // Unblock waits
        for (int i = 0; i < N; ++i) {
            if (s[i]) ReleaseSemaphore(s[i], 1, NULL);
        }
        // Join threads
        HANDLE alive[N]; int cnt = 0;
        for (int i = 0; i < N; ++i) if (threads[i]) alive[cnt++] = threads[i];
        if (cnt > 0) WaitForMultipleObjects(cnt, alive, TRUE, INFINITE);

        // Close handles
        for (int i = 0; i < N; ++i) {
            if (threads[i]) { CloseHandle(threads[i]); threads[i] = NULL; }
            if (s[i]) { CloseHandle(s[i]); s[i] = NULL; }
        }
        if (hMutex) { CloseHandle(hMutex); hMutex = NULL; }

        PostLogFmt("Simulation stopped.");
        EnableWindow(GetDlgItem(g_hDlg, IDC_START_BUTTON), TRUE);
        EnableWindow(GetDlgItem(g_hDlg, IDC_STOP_BUTTON), FALSE);
    }
}

unsigned __stdcall PhilosopherThread(void* pParam) {
    int i = (int)(INT_PTR)pParam;
    Sleep(50 * i); // stagger starts
    while (InterlockedCompareExchange(&gRunning, TRUE, TRUE)) {
        // THINKING
        PostMessage(g_hDlg, WM_APP_STATE, (WPARAM)i, THINKING);
        PostLogFmt("t=%lu | P(%d) THINKING", ms_since_start(), i);
        think(i);

        // HUNGRY
        PostMessage(g_hDlg, WM_APP_STATE, (WPARAM)i, HUNGRY);
        PostLogFmt("t=%lu | P(%d) HUNGRY", ms_since_start(), i);
        take_forks(i);

        // EATING
        PostMessage(g_hDlg, WM_APP_STATE, (WPARAM)i, EATING);
        PostLogFmt("t=%lu | P(%d) EATING", ms_since_start(), i);
        eat(i);

        put_forks(i);
    }
    return 0;
}

void think(int i) { Sleep(200 + (i * 20)); }
void eat(int i)   { Sleep(220 + (i * 25)); }

void take_forks(int i) {
    // Enter global critical region
    WaitForSingleObject(hMutex, INFINITE);

    // Declare intent to eat
    gState[i] = HUNGRY;
    PostLogFmt("t=%lu | P(%d) STATE=HUNGRY", ms_since_start(), i);

    // Try to acquire forks
    test(i);

    // Exit global region
    ReleaseSemaphore(hMutex, 1, NULL);

    // Wait until allowed to eat
    WaitForSingleObject(s[i], INFINITE);
}

void put_forks(int i) {
    WaitForSingleObject(hMutex, INFINITE);

    gState[i] = THINKING;
    PostLogFmt("t=%lu | P(%d) STATE=THINKING", ms_since_start(), i);

    // Neighbors may proceed now
    test(LEFT(i));
    test(RIGHT(i));

    ReleaseSemaphore(hMutex, 1, NULL);
}

void test(int i) {
    if (gState[i] == HUNGRY
        && gState[LEFT(i)] != EATING
        && gState[RIGHT(i)] != EATING) {

        gState[i] = EATING;
        PostLogFmt("t=%lu | P(%d) ALLOW=EATING", ms_since_start(), i);
        ReleaseSemaphore(s[i], 1, NULL);
    }
}

DWORD ms_since_start() {
    static DWORD base = 0;
    DWORD now = GetTickCount();
    if (base == 0) base = now;
    return now - base;
}
