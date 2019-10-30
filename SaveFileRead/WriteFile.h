#pragma once

#include "../WindowObject/Image.h"
#include "../WindowObject/Area.h"
#include <string>
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

string encodeImage(Image &obj) {
	string result = "--OBJ--\n";

	result += encodeParams("path", obj.adress);
	result += encodeParams("widht", to_string(obj.widht));
	result += encodeParams("height", to_string(obj.height));
	result += encodeParams("coord", encodeAreaCoord(obj.area));

	return result;
}

string encodeArrImages(vector<Image> &objs) {
	string result = "";
	for (int i = 0; i < objs.size(); i++) {
		result += encodeImage(objs[i]);
	}

	return result;
}
