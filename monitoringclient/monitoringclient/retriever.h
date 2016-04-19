#pragma once

#include "stdafx.h"
#include <iostream>
#include <fcntl.h>
#include <io.h>
#include <string>
#include <fstream>
#include "ddeutil.h"
#include <regex>

using namespace std;

const int MAXSTR = 1000;

char exename[MAXSTR];

char url[MAXSTR];

regex url_grabber("\"(.*?)\"");

VOID CALLBACK retriever(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
	*exename = 0;
	*url = 0;
	cregex_iterator empty;

	HWND win_handle = GetForegroundWindow();

	if (win_handle) {
		int bufsize = GetWindowTextLength(win_handle) + 1;
		LPWSTR title = new WCHAR[bufsize];
		GetWindowText(win_handle, title, bufsize);

		char* ascii_title = new char[bufsize + 1];

		setlocale(LC_ALL, ".1252");
		wcstombs(ascii_title, title, bufsize);

		for (int i = 0; i <= bufsize; i++) {
			if ((int)ascii_title[i] == -105)
				ascii_title[i] = '-';
		}
		cout << ascii_title << endl;
		//out_file << "Window Title: " << ascii_title << endl;

		delete[] title;
		delete[] ascii_title;

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

		cout << "Exename: " << exename << endl;
		//out_file << "Exename: " << exename << endl;

		if (strcmp(exename, "firefox") == 0 || strcmp(exename, "iexplore") == 0 /*|| strcmp(exename, "chrome") == 0 ||
																				strcmp(exename, "opera") == 0 || strcmp(exename, "netscape") == 0 || strcmp(exename, "netscape6") == 0*/)
		{
			// TODO: can we get a UTF-8 URL out of this somehow, if the URL contains percent encoded unicode chars?
			ddereq(exename, "WWW_GetWindowInfo", "0xFFFFFFFF", url, MAXSTR);
			url[MAXSTR - 1] = 0;

			cregex_iterator iterator(url, url + MAXSTR - 1, url_grabber);

			if (iterator == empty) {
				cout << "Failed to grab url" << endl;
				cout << "Full yoke: " << url << endl << endl;
			}
			else {
				cout << "Url: " << (*iterator).str() << endl << endl;
			}
			//out_file << "Url: " << url << endl << endl;
		}
		else {
			cout << endl;
			//out_file << endl;
		}
	}
}
