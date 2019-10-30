/*!
\file
\brief ������ ����� ��������
*/
#pragma once
#include <string>
#include <fstream>
#include <vector>
#include "../FunString.h"
#include "Setting.h"
/*!
\file
\brief ������ ����� ��������
*/
using namespace std;

/*!
\brief ���� ��������

������ ��������� ������ ��� �������� ������������ �������, ��
	����� ��������
*/
struct ConfigApp {
	string pathFile; ///< ���� �� �����
	vector<Setting> settings; ///< ��������
};

/*!
������� ����� ���� � ����������� �� ���������
\param nameFile ���� �� �����
*/
void createConfigFile(string nameFile) {
	ofstream file;
	file.open(nameFile.c_str());

	file << "wight: 800" << endl;
	file << "height: 600" << endl;

	file.close();
}

/*!
������ ����, ���� ����� ���, �� ������� ��� ��� ������ `createConfigFile`
\param nameFile ���� �� �����
\return ����������� ���������
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
���� �������� ��������� �� ���������� �����������
\param config ����������� ���������
\param id ��������� �����������
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
