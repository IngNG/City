/*!
\file
\brief ������

�������� ������� � ��������� ��� ��������� ��������
*/
#pragma once
#include "../lib/TXLib.h"
#include "Area.h"

/*!
\brief �������� 
*/
struct Image {
	AreaCoord area; ///< �������, ��� �������� ��������
	int    widht; ///< ������ ��������
	int    height; ///< ������ ��������
	HDC    img; ///< ���������� ��������� � ���������. �������� ����� �������� `txLoadImage` �� ���������� TXLib

	bool   visible; ///< �������� �� ��������
	string category; ///< ��������� ��������

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
