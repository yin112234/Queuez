#include "StdAfx.h"
#include "TMutex.h"

TMutex::TMutex(void)
{
	_mutex = CreateMutex(0,FALSE, NULL);
	if (0==_mutex)
		throw "TMutex::TMutex : CreateMutex";
}

TMutex::~TMutex(void)
{
	if (!CloseHandle(_mutex)) 
		throw "TMutex::~TMutex : CloseHandle";
}

void TMutex::Acquire()
{
	DWORD rc = WaitForSingleObject(_mutex,INFINITE);
	switch(rc) {
	case WAIT_OBJECT_0:
			break;
	case WAIT_ABANDONED:
		throw "TMutex::Acquire : WAIT_ABANDONED";
		break;
	case WAIT_TIMEOUT:
		throw "TMutex::Acquire : WAIT_TIMEOUT";
	}
}

void TMutex::Release()
{
	DWORD rc = ReleaseMutex(_mutex);
	if (!rc) throw "TMutex::Release SYSTEM ERROR";
}
