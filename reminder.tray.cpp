// reminder.tray.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Reminder.h"

int _tmain(int argc, _TCHAR* argv[])
{
	CReminder::ShowNotification(L"Water", L"gu-is.ru", NIIF_INFO);
	return 0;
}

