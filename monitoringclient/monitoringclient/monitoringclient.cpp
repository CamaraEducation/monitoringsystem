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
	for (int i = 0; i < 50; i++) {
		Sleep(4000);

		HWND handle = GetForegroundWindow();

		if (handle){
			int bufsize = GetWindowTextLength(handle) + 1;
			LPWSTR title = new WCHAR[bufsize];
			GetWindowText(handle, title, bufsize);

			char* ascii_title = new char[bufsize + 1];

			setlocale(LC_ALL, ".1252");
			wcstombs(ascii_title, title, bufsize);

			for (int i = 0; i <= bufsize; i++) {
				if ((int)ascii_title[i]==-105)
					ascii_title[i] = '-';
			}
			cout << ascii_title << endl;

			delete [] title;
			delete [] ascii_title;
		}
	}

	char waitchar;

	cin >> waitchar;

    return 0;
}

