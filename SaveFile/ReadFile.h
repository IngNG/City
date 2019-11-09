#pragma once
#include "../utils/ValueName.h"
#include "../utils/FunString.h"
#include "../utils/ReadFile.h"
#include "../WindowObject/Image.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

ValueName parseParams(string str) {
	vector<string> strSplited = stringSplit(str, "=", 2);

	ValueName parms;
	parms.id = strSplited[0];
	parms.value = strSplited[1];
	
	return parms;
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

		ValueName params = parseParams(lines[i]);
		if (params.id == "path") {
			img.adress = params.value;
		}
		else if (params.id == "widht") {
			img.widht = atoi(params.value.c_str());
		}
		else if (params.id == "height") {
			img.height = atoi(params.value.c_str());
		}
		else if (params.id == "coord") {
			vector<int> coord = ParseAreaCoord(params.value);
			img.area.x = coord[0];
			img.area.y = coord[1];
			img.area.widht = coord[2];
			img.area.height = coord[3];
		}
	}

	return img;
}

vector<Image> parseArrImages(string str, Image *menu, int sizeMenu) {
	vector<string> arrObjStr = stringSplit(str, "--OBJ--\n");
	vector<Image> arrObj;

	for (int i = 0; i < arrObjStr.size(); i++) {
		if (arrObjStr[i] == "") {
			continue;
		}

		Image loadedObj = parseObject(arrObjStr[i]);
		for (int i = 0; i < sizeMenu; i++) {
			if (loadedObj.adress == menu[i].adress) {
				loadedObj.img = menu[i].img;
				loadedObj.category = menu[i].category;
			}
		}
		arrObj.push_back(loadedObj);
	}

	return arrObj;
}

vector<Image> readSaveFile(string path, Image* menu, int sizeMenu) {
	cout << readAllFile(path) << endl;
	return parseArrImages(readAllFile(path), menu, sizeMenu);
}
