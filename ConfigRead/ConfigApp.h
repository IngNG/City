/*!
\file
\brief Чтение файла настроек
*/
#pragma once
#include <string>
#include <fstream>
#include <vector>
#include "Setting.h"
/*!
\file
\brief Чтение файла настроек
*/
using namespace std;

/*!
\brief Представляет файл настроек

Данный класс нужен для хранение обработанных натроек, из
	файла настроек
*/
struct ConfigApp {
	string pathFile; ///< Путь до файла
	vector<Setting> settings; ///< Значения
};

/*!
Делит строку по разделителю
\param[out] str Строка для разделения
\param[out] delim Делитель
\param[in] output Массив для результата деления
\param[in] maxCountOutput Размер массива `output`
\return Кол-во разделенных элементов
*/
int stringSplit(string str, string delim, string *output, int maxCountOutput) {
	int pos = 0;
	int i = 0;

	string tmp;

	while ((pos = str.find(delim)) != std::string::npos && i != maxCountOutput - 1) {
		tmp = str.substr(0, pos);
		output[i] = tmp;
		str.erase(0, pos + delim.length());
		i++;
	}

	if (i != maxCountOutput) {
		output[i] = str;
		i++;
	}

	return i;
}

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
	string splitLine[2];

	while (getline(file, line)) {
		stringSplit(line, ": ", splitLine, 2);

		Setting a{ splitLine[0], splitLine[1] };
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
