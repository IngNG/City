/*!
\file
\brief ������� �������� ����� ����
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
		Image obj = objs[i];
		file << "--OBJ--\n";
		file << "path=" << obj.adress + "\n";
		file << "widht=" << obj.widht + "\n";
		file << "height=" << obj.height + "\n";
		file << "coord=" << obj.area.x << "|" <<obj.area.y << "|" << obj.area.widht << "|" << obj.area.height << "\n";
	}

	file.close();
}
