#include "TQueue.h"

TQueue q;

DWORD WINAPI LocalThread(LPVOID parms)
{
	try {
		for(int i=0;i<1000;i++)
		{
			printf("put %d\n",i);
			q.Put(i);
			Sleep(10);
		}
	}
	catch(const char * c) 
	{
		printf("EXCEPTION in THREAD: %s, err=%d\n",c,GetLastError());
	}
	return 0;
}

#define THREADS 10
int _tmain(int argc, _TCHAR* argv[])
{
	DWORD id;
	HANDLE thread[THREADS];
	for(unsigned int i=0;i<THREADS;i++) 
		thread[i] = CreateThread(0,10000,LocalThread, 0, 0, &id);
	
	try {
		for(int x=0;;)
		{
			x = q.Get();
			printf("x = %d\n",x);
			if (x==999) break;
		}
		for(int i=0;i<THREADS;i++)
			CloseHandle(thread[i]);
	}
	catch(const char * c) 
	{
		printf("EXCEPTION: %s, err=%d\n",c,GetLastError());
	}

	return 0;
}
