/*!
\file
\brief ������

�������� ������� � ��������� ��� ��������� ������
*/
#pragma once
#include "../TXLib.h"
#include <string>
#include "Area.h"

/*!
\brief ������ � �������
*/
struct ButtonText {
	AreaCoord area; ///< �������, ��� �������� ������

	string    text; ///< �����
	COLORREF  fillColor; ///< ���� �������
	COLORREF  borderColor; ///< ���� �������
	COLORREF  textColor; ///< ���� ������

	bool      visible; ///< �������� �� ������
    string    category; ///< ��������� ������� ����� ������������ ��� �������
	int       sizeFont; ///< ������ ������
	string    nameFont; ///< �����

	/*!
	��������� ������ �� ������.

	���������� ��� `button.area.events.mouseButtonUpLeft`.
	\return true - ���� ������, ����� false
	*/
	bool click() {
		return area.mouseButtonUpLeft;
	}

	bool downClick() {
		return area.mouseButtonDownLeft;
	}
};

/*!
���� `visible` ����� true, �� ������ ������, ����� ������ �� ������
\param b ������ ������� ����� ����������
*/
void drawButton(ButtonText &b) {
	updateStatusArea(b.area);
	if (b.visible) {
		txSetFillColor(b.fillColor);
		txSetColor(b.borderColor);
		txSelectFont(b.nameFont.c_str(), b.sizeFont);

		txRectangle(
			b.area.x, b.area.y,
			b.area.x + b.area.widht, b.area.y + b.area.height
		);
		if (b.text.length() != 0) {
			txDrawText(
				b.area.x, b.area.y,
				b.area.x + b.area.widht, b.area.y + b.area.height,
				b.text.c_str()
			);
		}
	}
}

/*!
������������� ������������ ���������� ������ � ����
\param[out] button ��������� �� ������ � ��������� ��� �������������
\param countButton ���-�� ������
\param x X-���������� ����
\param y Y-���������� ������ ����
\param widhtButton ������ ������
\param heightButton ������ ������
\param indent ������ ����� ��������
\param fill ���� �������
\param border ���� �������
\param text ���� ������
*/
void initButtonMenu(
	ButtonText* button, int countButton,
	int x, int y,
	int widhtButton, int heightButton, int indent,
	COLORREF fill, COLORREF border, COLORREF text
) {
	for (int i = 0; i < countButton; i++) {
		button[i].area.x = x;
		button[i].area.y = y + (indent * i) + (heightButton * i);
		button[i].area.widht = widhtButton;
		button[i].area.height = heightButton;
		button[i].fillColor = fill;
		button[i].borderColor = border;
		button[i].textColor = text;
		button[i].category = "";

		button[i].area.mouseButtonUpLeft = false;
		button[i].area.mouseButtonUpRight = false;
		button[i].area.mouseButtonDownLeft = false;
		button[i].area.mouseButtonDownRight = false;
		button[i].area.mouseHover = false;
		button[i].area.mouseUnHover = false;

		button[i].area.mouseOver = false;
		button[i].area.mouseClickRight = false;
		button[i].area.mouseClickLeft = false;
	}
}
