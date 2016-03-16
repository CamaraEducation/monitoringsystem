// monitoringclient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;


int main()
{
	for (int i = 0; i < 10; i++) {
		Sleep(10000);

		HWND handle = GetForegroundWindow();
		int bufsize = GetWindowTextLength(handle) + 1;
		LPWSTR title = new WCHAR[bufsize];
		GetWindowText(handle, title, bufsize);
		
		wcout << title << endl;

		delete title;
	}

	char waitchar;

	cin >> waitchar;

    return 0;
}

