#pragma once
#include "../lib/TXLib.h"
#include <string>
#include "Area.h"

struct ButtonText {
	AreaCoord area;

	string text;
	COLORREF fillColor;
	COLORREF borderColor;
	COLORREF textColor;

	bool visible;

	int sizeFont;
	string nameFont;
};

void drawButton(ButtonText b) {
	if (b.visible) {
		txSetFillColor(b.fillColor);
		txSetColor(b.borderColor);
		txSelectFont(b.nameFont.c_str(), b.sizeFont);

		txRectangle(b.area.x, b.area.y, b.area.x2, b.area.y2);
		if (b.text.length() != 0) {
			txDrawText(b.area.x, b.area.y, b.area.x2, b.area.y2, b.text.c_str());
		}
	}
}

EventArea getEventImage(ButtonText& button) {
	return getEventArea(button.area);
}
