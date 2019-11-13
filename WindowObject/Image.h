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
		return
			(txMouseButtons() == 1 &&
			txMouseX() > area.x &&
			txMouseY() > area.y &&
			txMouseX() < area.x + area.widht &&
			txMouseY() < area.y + area.height);
	}

	bool downClick() {
		return area.mouseButtonDownLeft;
	}
};

void drawImage(Image i, int CAM_X) {
	if (i.visible) {
		Win32::TransparentBlt(
			txDC(),
			i.area.x + CAM_X, i.area.y,
			i.area.widht, i.area.height,
			i.img,
			0, 0,
			i.widht, i.height,
			TX_WHITE
		);
	}
}

void updateStatusImage(Image &img, int CAM_X = 0) {
	updateStatusArea(img.area, CAM_X);
}

int getWidhtImage(string adress) {
	unsigned char info[54];

	FILE* f = fopen(adress.c_str(), "rb");
	fread(info, sizeof(unsigned char), 54, f);
	fclose(f);

	int width = *(int*)&info[18];
	return width;
}

int getHeightImage(string adress) {
	unsigned char info[54];

	FILE* f = fopen(adress.c_str(), "rb");
	fread(info, sizeof(unsigned char), 54, f);
	fclose(f);

	int height = *(int*)&info[22];
	return height;
}

Image loadImage(AreaCoord area, string pathimg) {
	Image img;
	img.area     = area;
	img.adress   = pathimg;

	string st = img.adress;
	int pos1 = st.find ("\\");
	int pos2 = st.find ("\\", pos1 + 1);
	img.category = st.substr(pos1 + 1, pos2 - pos1 - 1);

	img.widht    = getWidhtImage(pathimg);
	img.height   = getHeightImage(pathimg);
	img.img      = txLoadImage(img.adress.c_str());
	img.visible  = true;
	return img;
}

Image copyImage(Image original, string category="", bool visable=true) {
	Image copy;
	copy.area = original.area;
	copy.adress = original.adress;
	copy.category = category;
	copy.widht = original.widht;
	copy.height = original.height;
	copy.img = original.img;
	copy.visible = true;
	return copy;
}
