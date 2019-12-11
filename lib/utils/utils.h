/*!
\file
\brief Различные функции
*/
#pragma once
#include <Windows.h>
#include <string>
#include <vector>
using namespace std;

/*!
Добовляет расширение если оно не существует
\param name Имя файла
\param ext Расширение
\return Новое имя
*/
string appendExt(string name, string ext) {
	if (name == "") {
		return "";
	}

	if (name.find("." + ext) == -1) {
		return name + "." + ext;
	}

	return name;
}

/*!
Вызывает системное меню выбора файла
\param hWnd Дискриптьор окна
\param save Если true, то открывется меню сохранения, иначе меню открытия
\return Выбраный пользователем файл
*/
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
\param str Строка для разделения
\param delim Делитель
\param max Максимальное кол-во подстрок
\return Вектор из строк
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
