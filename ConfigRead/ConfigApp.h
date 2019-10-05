#pragma once
#include <string>
#include <fstream>
#include <vector>
#include "Setting.h"
using namespace std;

struct ConfigApp {
	string pathFile;
	vector<Setting> settings;
};

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

void createConfigFile(string nameFile) {
	ofstream file;
	file.open(nameFile.c_str());

	file << "wight: 800" << endl;
	file << "height: 600" << endl;

	file.close();
}

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

string getValueSetting(ConfigApp &config, string id) {
	int countSetting = config.settings.size();
	for (int i = 0; i < countSetting; i++) {
		if (config.settings[i].id == id) {
			return config.settings[i].value;
		}
	}

	throw "ID not fount";
}
