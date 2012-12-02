// reminder.tray.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Reminder.h"

int _tmain(int argc, _TCHAR* argv[])
{
	SYSTEMTIME curTime;
	GetSystemTime(&curTime);
	while( (curTime.wDay >= 22) && (curTime.wDay <= 31)  && CReminder::ShowNotification(L"Water", L"gu-is.ru", NIIF_INFO) ) {
		GetSystemTime(&curTime);
		Sleep(1000*60*20);
	}
	return 0;
}

