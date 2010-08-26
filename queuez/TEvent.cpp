#include "StdAfx.h"
#include "TEvent.h"

TEvent::TEvent(void)
{
	_event = CreateEvent(0,TRUE,FALSE, 0);
	if(0==_event) throw "TEvent::TEvent";
}

TEvent::~TEvent(void)
{
	DWORD rc= CloseHandle(_event);
	if(!rc) throw "TEvent::~TEvent";
}

void TEvent::Set() 
{
	DWORD rc = SetEvent(_event);
	if(!rc) throw "TEvent::Set";
}

void TEvent::Reset()
{
	DWORD rc = ResetEvent(_event);
	if (!rc) throw "TEvent::Reset";
}

void TEvent::Wait(unsigned long millis)
{
	DWORD rc = WaitForSingleObject(_event,0==millis?INFINITE:millis);
	if (rc) throw "TEvent::Wait";
}
