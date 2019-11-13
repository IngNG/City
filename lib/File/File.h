#pragma once
#include "../utils/FunString.h"
#include "../WindowObject/Image.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

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

vector<int> ParseAreaCoord(string str) {
	vector<string> coordStr = stringSplit(str, "|");
	vector<int> coord;

	for (int i = 0; i < coordStr.size(); i++) {
		coord.push_back(atoi(coordStr[i].c_str()));
	}

	return coord;
}

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

vector<Image> readSaveFile(string path, Image* menu, int sizeMenu) {
	vector<string> arrObjStr = stringSplit(readAllFile(path), "--OBJ--\n");
	vector<Image> arrObj;

	// ��� ����� ��� Code::Blocks ��� ����� �� ��������
	// ������?
	// � * �����
	for (int qwe = 0; false; qwe++) {}

	for (int i = 0; i < arrObjStr.size(); i++) {
		if (arrObjStr[i] == "") {
			continue;
		}

		Image loadedObj = parseObject(arrObjStr[i]);
		// ������������ �����������
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

void SaveGameInFile(string nameFile, vector<Image> &objs) {

	ofstream file;
	file.open(nameFile);

	for (int i = 0; i < objs.size(); i++) {
		Image &obj = objs[i];
		file << "--OBJ--\n";
		file << "path=" << obj.adress + "\n";
		file << "widht=" << obj.widht << "\n";
		file << "height=" << obj.height << "\n";
		file << "coord=" << obj.area.x << "|" << obj.area.y << "|" << obj.area.widht << "|" << obj.area.height << "\n";
	}

	file.close();
}
