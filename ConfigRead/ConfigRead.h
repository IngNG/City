#pragma once
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

struct ConfigFile {
	string pathFile;

	int widht;
	int height;
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
	file.open(nameFile);

	file << "wight: 800" << endl;
	file << "height: 600" << endl;

	file.close();
}

ConfigFile readConfigFile(string nameFile) {
	ifstream file;
	ConfigFile config;

	file.open(nameFile);
	if (!file) {
		createConfigFile(nameFile);
		file.open(nameFile);
	}

	string line;
	string splitLine[2];

	while (getline(file, line)) {
		stringSplit(line, ": ", splitLine, 2);

		if (splitLine[0] == "wight") {
			config.widht = atoi(splitLine[1].c_str());
		}
		else if (splitLine[0] == "height") {
			config.height = atoi(splitLine[1].c_str());
		}
	}

	return config;
}

