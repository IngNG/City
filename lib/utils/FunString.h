/*!
\file
\brief Фуекции для работы со `string`
*/
#pragma once
#include <string>
#include <vector>
using namespace std;

/*!
Делит строку по разделителю
\param[out] str Строка для разделения
\param[out] delim Делитель
\param[in] output Массив для результата деления
\param[in] maxCountOutput Размер массива `output`
\return Кол-во разделенных элементов
*/
vector<string> stringSplit(string str, string delim, int max=0) {
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
