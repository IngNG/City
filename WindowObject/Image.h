/*!
\file
\brief ������

�������� ������� � ��������� ��� ��������� ��������
*/
#pragma once
#include "../lib/TXLib.h"
#include "Area.h"
#include <fstream>

// ��� ���-�� VS �� �������
#pragma warning(disable:4996)

/*!
\brief ��������
*/
struct Image {
	AreaCoord area; ///< �������, ��� �������� ��������
	string adress;
	string category; ///< ��������� ��������
	HDC    img; ///< ���������� ��������� � ���������. �������� ����� �������� `txLoadImage` �� ���������� TXLib

	int    widht; ///< ������ ��������
	int    height; ///< ������ ��������
	bool   visible; ///< �������� �� ��������

	/*!
	��������� ������ �� ��������.

	���������� ��� `img.area.events.mouseButtonUpLeft`.
	\return true - ���� ������, ����� false
	*/
	bool click() {
		return area.events.mouseButtonUpLeft;
	}

	bool downClick() {
		return area.events.mouseButtonDownLeft;
	}
};

void drawImage(Image i) {
	if (i.visible) {
		Win32::TransparentBlt(
			txDC(),
			i.area.x, i.area.y,
			i.area.widht, i.area.height,
			i.img,
			0, 0,
			i.widht, i.height,
			TX_WHITE
		);
	}
}

void updateStatusImage(Image &img) {
	updateStatusArea(img.area);
}

int getWidhtImg(string adress) {
	unsigned char info[54];

	FILE* f = fopen(adress.c_str(), "rb");
	fread(info, sizeof(unsigned char), 54, f);
	fclose(f);

	int width = *(int*)&info[18];
	return width;
}

int getHeightImg(string adress) {
	unsigned char info[54];

	FILE* f = fopen(adress.c_str(), "rb");
	fread(info, sizeof(unsigned char), 54, f);
	fclose(f);

	int height = *(int*)&info[22];
	return height;
}
