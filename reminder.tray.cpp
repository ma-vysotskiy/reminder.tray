// reminder.tray.cpp : Defines the entry point for the console application.
//
//test
#include "stdafx.h"
#include "Reminder.h"

int _tmain(int argc, _TCHAR* argv[])
{
	SYSTEMTIME curTime;
	bool continueRun = true;
	HWND hWnd = GetConsoleWindow();
	//Minimaze to tray.
	ShowWindow(hWnd, SW_MINIMIZE);
	//Run until X button on balloon is not pressed.
	while( continueRun ) {
		//Get time.
		GetSystemTime(&curTime);	
		if( (curTime.wDay >= 22) && (curTime.wDay <= 31) ) {
			//Show notification
			continueRun = CReminder::ShowNotification(L"Water", L"gu-is.ru", NIIF_INFO);
		}
		//Wait.
		Sleep(1000*60*20);
	}
	return 0;
}

