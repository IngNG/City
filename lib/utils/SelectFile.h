#pragma once
#include <Windows.h>
#include <string>
using namespace std;

string selectFile(HWND hWnd) {
	const int SIZE = 100;
	char nameFile[SIZE];
	OPENFILENAMEA ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = nameFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = SIZE;
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_CREATEPROMPT;

	GetOpenFileNameA(&ofn);
	return nameFile;
}
