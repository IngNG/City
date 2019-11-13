/*!
\file
\brief Функции создание сейва игры
*/
#pragma once

#include "../WindowObject/Image.h"
#include "../WindowObject/Area.h"
#include <string>
#include <fstream>
using namespace std;

void SaveGameInFile(string nameFile, vector<Image> &objs) {

	ofstream file;
	file.open(nameFile);

	for (int i = 0; i < objs.size(); i++) {
		Image &obj = objs[i];
		file << "--OBJ--\n";
		file << "path=" << obj.adress + "\n";

		char width[100];
		sprintf(width,"%d", obj.widht);
		file << "widht=" << width << "\n";

		char height[100];
		sprintf(height,"%d", obj.height);
		file << "height=" << height << "\n";

		file << "coord=" << obj.area.x << "|" << obj.area.y << "|" << obj.area.widht << "|" << obj.area.height << "\n";
	}

	file.close();
}
