/*!
\file
\brief Работа с файлами
*/
#pragma once
#include "../utils/utils.h"
#include "../WindowObject/Image.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <Windows.h>
using namespace std;

/*!
Читает весь файл
\param path Путь до файла
\return Содержание файла
*/
string readAllFile(string path) {
	ifstream file;
	file.open(path);

	string line;
	string result = "";
	while (getline(file, line)) {
		result += line + "\n";
	}
	file.close();
	return result;
}

/*!
Парсит коордиты записаные строкой
\param str Строка для парсинга
\return Вектор содержащий координаты
*/
vector<int> ParseAreaCoord(string str) {
	vector<string> coordStr = stringSplit(str, "|");
	vector<int> coord;

	for (int i = 0; i < coordStr.size(); i++) {
		coord.push_back(atoi(coordStr[i].c_str()));
	}

	return coord;
}

/*!
Парсит объект записаный текстом
\param str Текст для парсинга
\return Полученный объект
*/
Image parseObject(string str) {
	Image img;
	vector<string> lines = stringSplit(str, "\n");
	for (int i = 0; i < lines.size(); i++) {
		if (lines[i] == "") {
			continue;
		}

		vector<string> strSplited = stringSplit(lines[i], "=", 2);
		string id = strSplited[0];
		string value = strSplited[1];

		if (id == "path") {
			img.adress = value;
		}
		else if (id == "widht") {
			img.widht = atoi(value.c_str());
		}
		else if (id == "height") {
			img.height = atoi(value.c_str());
		}
		else if (id == "coord") {
			vector<int> coord = ParseAreaCoord(value);
			img.area.x = coord[0];
			img.area.y = coord[1];
			img.area.widht = coord[2];
			img.area.height = coord[3];
		}
	}

	return img;
}

/*!
Парсит файл сохранений и присваевает нужные HDC
\param path Путь до файла
\param menu Меню. Нужно для получения HDC
\param sizeMenu Количесво элементов в меню
\return Массив объектов
*/
vector<Image> readSaveFile(string path, Image* menu, int sizeMenu) {
	vector<string> arrObjStr = stringSplit(readAllFile(path), "--OBJ--\n");
	vector<Image> arrObj;

	// Это нужно для Code::Blocks, без этого не работает
	// Почему?
	// Я не знаю
	for (int qwe = 0; false; qwe++) {}

	for (int i = 0; i < arrObjStr.size(); i++) {
		if (arrObjStr[i] == "") {
			continue;
		}

		Image loadedObj = parseObject(arrObjStr[i]);
		// Инитиализуем изображение
		for (int j = 0; j < sizeMenu; j++) {
			if (loadedObj.adress == menu[j].adress) {
				loadedObj.img = menu[j].img;
				loadedObj.category = menu[j].category;
			}
		}
		arrObj.push_back(loadedObj);
	}

	return arrObj;
}

/*!
Сохраняет игру в файл
\param nameFile Путь до файла
\param objs Массив объектов для сохранения
*/
void SaveGameInFile(string nameFile, vector<Image> &objs, int offset_x = 0) {

	ofstream file;
	file.open(nameFile);

	for (int i = 0; i < objs.size(); i++) {
		Image &obj = objs[i];
		file << "--OBJ--\n";
		file << "path=" << obj.adress + "\n";
		file << "widht=" << obj.widht << "\n";
		file << "height=" << obj.height << "\n";
		file << "coord=" << obj.area.x + offset_x << "|" << obj.area.y << "|" << obj.area.widht << "|" << obj.area.height << "\n";
	}

	file.close();
}
