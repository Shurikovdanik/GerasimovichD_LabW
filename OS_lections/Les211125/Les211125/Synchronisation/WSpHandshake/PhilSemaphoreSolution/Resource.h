#pragma once

// Icon
#define IDI_APPICON         101

// Dialog
#define IDD_MAIN_DIALOG     201

// Controls
#define IDC_START_BUTTON    1001
#define IDC_STOP_BUTTON     1002
#define IDC_LOG             1101

// Philosopher state labels (STATIC)
#define IDC_PH0             1200
#define IDC_PH1             1201
#define IDC_PH2             1202
#define IDC_PH3             1203
#define IDC_PH4             1204

// Custom messages (WM_APP + X)
#define WM_APP_STATE        (WM_APP + 1)  // wParam = philosopher index, lParam = state
#define WM_APP_LOG          (WM_APP + 2)  // lParam = pointer to heap-allocated char*
