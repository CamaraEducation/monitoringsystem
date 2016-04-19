// monitoringclient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ddeutil.h"
#include <fstream>
#include "retriever.h"
#include <conio.h>

using namespace std;

void panic(char *what)
{
	MessageBoxA(NULL, what, "camaratracker", MB_OK);
	exit(0);
}

int main()
{
	if (!ddeinit()) panic("CT: Cannot initialize DDE");

	
	ofstream out_file;
	out_file.open("sample_output.txt");

	MSG msg;
	SetTimer(NULL, NULL, 2*1000, retriever);


	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		if (_kbhit()) {
			break;
		}
	}
	char waitchar;

	cin >> waitchar;

	out_file.close();

	ddeclean();


    return 0;
}

