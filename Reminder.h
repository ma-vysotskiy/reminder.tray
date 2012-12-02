#pragma once

#include <shobjidl.h>
#include <Windows.h>
#include <string>
#include <iostream>

#include "QueryContinue.h"

class CReminder {

	static const bool needLog = true;
	static void ReminderLog( std::basic_string<TCHAR> str ) {
		if( needLog ) {
			std::wcout << str << std::endl;
			}
		}
public:
	static bool ShowNotification(std::basic_string<TCHAR> title, std::basic_string<TCHAR> text, DWORD type) {
		HRESULT result = E_FAIL;
		IUserNotification *notificationOne = 0;
		IUserNotification2 *notificationTwo = 0;
		CQueryContinue query(10000);

		//Get icon.
		HICON icon = LoadIcon(NULL, IDI_QUESTION); 
				
		//Try Vista interface first.
		result = CoInitialize((void*)notificationTwo);
		result = CoCreateInstance(CLSID_UserNotification, 0, CLSCTX_ALL, IID_IUserNotification2, (void**)&notificationTwo);

		//On faile try XP.
		if (!SUCCEEDED(result))
		{
			ReminderLog(L"Using Windows XP interface IUserNotification\n");
			result = CoInitialize( (LPVOID)notificationOne);
			result = CoCreateInstance(CLSID_UserNotification, 0, CLSCTX_ALL, IID_IUserNotification, (LPVOID*)&notificationOne);
		} else {
			ReminderLog(L"Using Vista interface IUserNotification2\n");
			notificationOne = (IUserNotification*)notificationTwo; //Rather ugly cast saves some code...
		}

		if (SUCCEEDED(result)) {
			ReminderLog(L"SUCCEEDED\n");

			result = notificationOne->SetIconInfo(icon, title.c_str());
			result = notificationOne->SetBalloonInfo(title.c_str(), text.c_str(), type);

			//Looks like it controls what happends when the X button is
			//clicked on
			result = notificationOne->SetBalloonRetry(0, 250, 0);

			

			if (notificationTwo) {
				result = notificationTwo->Show(&query, 250, NULL);
			} else {
				result = notificationOne->Show(NULL, 250);
			}
		
			notificationOne->Release();
		}
		return query.TimeoutReached();
	}
};