#pragma once
#include <Windows.h>
#include <string>
using namespace std;

string appendExt(string name, string ext) {
	if (name == "") {
		return "";
	}
	
	if (name.find("." + ext) == -1) {
		return name + "." + ext;
	}

	return name;
}

string selectFile(HWND hWnd, bool save) {
	const int SIZE = 100;
	char nameFile[SIZE];
	OPENFILENAMEA ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = nameFile;
	ofn.lpstrFile[0] = '\0';
	ofn.lpstrFilter = "Файл сохранения (*.scity)\0*.scity\0";
	ofn.nMaxFile = SIZE;
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.lpstrInitialDir = ".";
	ofn.Flags = OFN_CREATEPROMPT;

	if (save) {
		GetSaveFileNameA(&ofn);
	}
	else {
		GetOpenFileNameA(&ofn);
	}
	
	return appendExt(nameFile, "scity");
}
