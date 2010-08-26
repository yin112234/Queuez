#pragma once

#ifdef WIN32
#include <windows.h>
#endif	


class TEvent
{
#ifdef WIN32
	HANDLE _event;
#endif	
public:
	TEvent(void);
	~TEvent(void);
	void Set();
	void Reset();
	void Wait(unsigned long millis = 0);
};
