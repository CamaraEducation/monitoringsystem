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
	const int MAXSTR = 1000;

	char exename[MAXSTR];
	*exename = 0;

	for (int i = 0; i < 50; i++) {
		Sleep(4000);

		HWND win_handle = GetForegroundWindow();

		if (win_handle){
			int bufsize = GetWindowTextLength(win_handle) + 1;
			LPWSTR title = new WCHAR[bufsize];
			GetWindowText(win_handle, title, bufsize);

			char* ascii_title = new char[bufsize + 1];

			setlocale(LC_ALL, ".1252");
			wcstombs(ascii_title, title, bufsize);

			for (int i = 0; i <= bufsize; i++) {
				if ((int)ascii_title[i]==-105)
					ascii_title[i] = '-';
			}
			cout << ascii_title << endl;

			DWORD proc_id = 0;
			GetWindowThreadProcessId(win_handle, &proc_id);
			HANDLE proc_handle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ /*|PROCESS_SET_QUOTA*/, FALSE, proc_id);

			wchar_t uexename[MAXSTR];
			DWORD testl = sizeof(uexename);
			QueryFullProcessImageNameW(proc_handle, 0, uexename, &testl);
			uexename[MAXSTR - 1] = 0;
			WideCharToMultiByte(CP_UTF8, 0, uexename, -1, exename, MAXSTR, NULL, NULL);
			exename[MAXSTR - 1] = 0;

			char *trim = strrchr(exename, '\\');
			if (trim) memmove(exename, trim + 1, strlen(trim));
			char *ext = strrchr(exename, '.');
			if (ext) *ext = 0;
			for (char *p = exename; *p; p++) *p = tolower(*p);
			CloseHandle(proc_handle);

			cout << "Exename: " << exename << endl << endl;

			delete [] title;
			delete [] ascii_title;
		}
	}

	char waitchar;

	cin >> waitchar;

    return 0;
}

