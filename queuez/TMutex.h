#pragma once

#ifdef WIN32
#include <windows.h>
#endif

class TMutex
{
#ifdef WIN32
	HANDLE _mutex;
#endif

public:
	TMutex(void);
	~TMutex(void);
	void Acquire();
	void Release();
};

class TLocker
{
	TMutex * _m;
public:
	TLocker(TMutex * m)
	{
		_m = m;
		_m->Acquire();
	}
	~TLocker() 
	{
		_m->Release();
	}
};