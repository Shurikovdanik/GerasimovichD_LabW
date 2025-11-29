// CriticalSection.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <conio.h>
#define _WIN32_WINNT 0x0400
#include <windows.h>
#include <process.h>
#include <stdlib.h>

unsigned nThreads=2;

HANDLE		   hThreads[64]={0};
unsigned int tidThreads[64]={0};
int              Shared[64]={0};

bool bTerminate=false;
CRITICAL_SECTION cs;

unsigned int _stdcall ThreadFunc(void * p);

int main(int argc, char* argv[]) {
	printf("Hello World!\n");

	while(true){
		printf("Press ENTER to exit or any key to continue:\n");
		if(getch()==13) break;

		printf("Type a number of threads, no more than %d:\n",MAXIMUM_WAIT_OBJECTS);
		scanf("%u",&nThreads);
		if(nThreads < 2 || MAXIMUM_WAIT_OBJECTS < nThreads)
			{perror("Invalid the number of threads.\n"); continue;}

		InitializeCriticalSection(&cs);
		bTerminate=false;  
		for(unsigned i=0; i < nThreads; i++) {//CreateThread
				Shared[i]= 0;

		    //    hThreads[i] = (void*) _beginthreadex(0,  // pointer to security attributes
						//			0,  // initial thread stack size
						//  ThreadFunc,  // pointer to thread function
						//	(void *)i,  // argument for new thread
					 //CREATE_SUSPENDED,  // creation flags //0
						//&tidThreads[i]  // pointer to receive thread ID	
						//		);
				hThreads[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadFunc, (void*)i, CREATE_SUSPENDED, (LPDWORD)&tidThreads[i]);
				if(!hThreads[i]){ perror("Invalid a thread's handle.\n"); return 1;	}
			};//for
		//Start, that is   Do ResumeThread(s)
		srand(17);	//The number 17 is the seed 
					//for a new sequence of pseudorandom numbers in the range 0 to RAND_MAX == 0x7fff.

		printf("Press any key to ResumeThread(s):\n");
		getch();

		for(int i=0; i < nThreads; i++) ResumeThread(hThreads[i]);

		Sleep(1000);//	Set up bTerminate=true;
		  InterlockedExchange((long*) &bTerminate,  // pointer to the destination pointer
									true  );   // the exchange value   
		DWORD dwRes=WaitForMultipleObjects(nThreads,hThreads,TRUE,INFINITE);

		if(dwRes==WAIT_FAILED) {perror("dwRes==WAIT_FAILED.\n"); return 1; };
		 
		for(int i=0;i < nThreads;i++) {printf("Shared[%2d]=%d\n",i,Shared[i]);CloseHandle(hThreads[i]);
        };
		DeleteCriticalSection(&cs);
	}//while	
	return 0;
}//main

#define TIME_TO_SLEEP 0
#define STRATEGY      1 //0 or 1 or 2

unsigned int _stdcall ThreadFunc(void * p){
	unsigned int i =(unsigned int)p;
	while(!bTerminate)	{		
		EnterCriticalSection(&cs);			
			//Shared[i]+=1;	//inside critical section
				//Shared[k] = 1 + Shared[(k+1)% nThreads];
				//Shared[k] = 1 + (Shared[(k + 1) % nThreads] + Shared[(k - 1+ nThreads) % nThreads])/2;
				//Shared[k] = 1+ (Shared[(k + 1) % nThreads] - Shared[(k - 1 + nThreads) % nThreads]) / 2;
			//RAND_MAX == 0x7fff;
			int di_rand = rand(); //0 <= di_random <= RAND_MAX
			int i_rand = (i + di_rand) % nThreads;
			Shared[i] = 1 + Shared[i_rand]; //random dependency of k from i_rand		

		LeaveCriticalSection(&cs);
		#if STRATEGY == 1
		    Sleep(TIME_TO_SLEEP);
		#elif STRATEGY == 2
			SwitchToThread();//for Windows NT 4.0 or later versions
		#endif
	}
	return 0;
}//ThreadFunc

