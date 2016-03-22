// monitoringclient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fcntl.h>
#include <io.h>
#include <string>

using namespace std;


int main()
{
	_setmode(_fileno(stdout), _O_U16TEXT);

	for (int i = 0; i < 50; i++) {
		Sleep(4000);

		HWND handle = GetForegroundWindow();

		if (handle){
			int bufsize = GetWindowTextLength(handle) + 1;
			LPWSTR title = new WCHAR[bufsize];
			GetWindowText(handle, title, bufsize);
			wprintf(L"%s\n", title);

			delete [] title;
		}
	}

	char waitchar;

	cin >> waitchar;

    return 0;
}

