/*!
\file
\brief Чтение файла настроек
*/
#pragma once
#include <string>
#include <fstream>
#include <vector>
#include "../FunString.h"
#include "Setting.h"
/*!
\file
\brief Чтение файла настроек
*/
using namespace std;

/*!
\brief Файл настроек

Данная структура нужена для хранение обработанных натроек, из
	файла настроек
*/
struct ConfigApp {
	string pathFile; ///< Путь до файла
	vector<Setting> settings; ///< Значения
};

/*!
Создает новый файл с настройками по умолчанию
\param nameFile Путь до файла
*/
void createConfigFile(string nameFile) {
	ofstream file;
	file.open(nameFile.c_str());

	file << "wight: 800" << endl;
	file << "height: 600" << endl;

	file.close();
}

/*!
Читает файл, если файла нет, то создает его при помощи `createConfigFile`
\param nameFile Путь до файла
\return Отпарсенные настройки
*/
ConfigApp readConfigFile(string nameFile) {
	ifstream file;
	ConfigApp config;

	file.open(nameFile.c_str());
	if (!file) {
		createConfigFile(nameFile);
		file.open(nameFile.c_str());
	}

	string line;

	while (getline(file, line)) {
		vector<string> splitLines = stringSplit(line, ": ", 2);

		Setting a{ splitLines[0], splitLines[1] };
		config.settings.push_back(a);
	}

	return config;
}

/*!
Ищет значение настройки по текстовому идификатору
\param config Отпарсенные настройки
\param id Текстовый индификатор
*/
string getValueSetting(ConfigApp &config, string id) {
	int countSetting = config.settings.size();
	for (int i = 0; i < countSetting; i++) {
		if (config.settings[i].id == id) {
			return config.settings[i].value;
		}
	}

	throw "ID not fount";
}
