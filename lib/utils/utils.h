#pragma once
#include <Windows.h>
#include <string>
#include <vector>
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

/*!
Делит строку по разделителю
\param[out] str Строка для разделения
\param[out] delim Делитель
\param[in] output Массив для результата деления
\param[in] maxCountOutput Размер массива `output`
\return Кол-во разделенных элементов
*/
vector<string> stringSplit(string str, string delim, int max = 0) {
	int pos = 0;
	int i = 0;

	vector<string> result;

	while ((pos = str.find(delim)) != std::string::npos && (i != max | i == 0)) {
		string buff = str.substr(0, pos);
		result.push_back(buff);
		str.erase(0, pos + delim.length());
		i++;
	}

	if (i != max | i == 0) {
		result.push_back(str);
		i++;
	}

	return result;
}
