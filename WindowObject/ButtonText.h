#pragma once
#include "../lib/TXLib.h"
#include "Const.h"
#include <string>
#include "Area.h"

struct ButtonText {
	AreaCoord area;

	string text;
	COLORREF fillColor;
	COLORREF borderColor;
	COLORREF textColor;

	int sizeFont = 25;
	string nameFont = "Comic Sans MS";
};

void drawButton(ButtonText b) {
	txSetFillColor(b.fillColor);
	txSetColor(b.borderColor);
	txSelectFont(b.nameFont.c_str(), b.sizeFont);

	txRectangle(b.area.x, b.area.y, b.area.x2, b.area.y2);
	if (b.text.length() != 0) {
		txDrawText(b.area.x, b.area.y, b.area.x2, b.area.y2, b.text.c_str());
	}
}