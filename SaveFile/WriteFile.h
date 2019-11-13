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

/*!
�������� �������� � ���� ������
\param name �������� ���������
\param value �������� ���������
\return ������ ������� "name=value"
*/
string encodeParams(string name, string value) {
	return name + "=" + value + "\n";
}

/*!
������������ `AreaCoord` � `string`
\param obj ������ ��� ���������������
\return ������ ������� "x|y|widht|height"
*/
string encodeAreaCoord(AreaCoord &obj) {
	string x = to_string(obj.x);
	string y = to_string(obj.y);
	string w = to_string(obj.widht);
	string h = to_string(obj.height);

	return x + "|" + y + "|" + w + "|" + h;
}

/*!
����������� `Image` � `string`
\param obj ������ ��� ���������������
\return ������ ������� "--OBJ--\nparamname1=value1\nparamname2=value2"
*/
string encodeImage(Image &obj) {
	string result = "--OBJ--\n";

	result += encodeParams("path", obj.adress);
	result += encodeParams("widht", to_string(obj.widht));
	result += encodeParams("height", to_string(obj.height));
	result += encodeParams("coord", encodeAreaCoord(obj.area));

	return result;
}

/*!
����������� `vector<Image>` � `string`
\param objs ������� ��� ���������������
\return ��������������� ������
*/
string encodeArrImages(vector<Image> &objs) {
	string result = "";
	for (int i = 0; i < objs.size(); i++) {
		result += encodeImage(objs[i]);
	}

	return result;
}

void SaveGameInFile(string nameFile, vector<Image> &objs) {
	ofstream file;
	file.open(nameFile);

	string text = encodeArrImages(objs);
	file << text;
	file.close();
}
