#pragma once
#include "../lib/TXLib.h"
#include <string>
#include "Area.h"

struct ButtonText {
	AreaCoord area;

	string    text;
	COLORREF  fillColor;
	COLORREF  borderColor;
	COLORREF  textColor;

	bool      visible;
    string    category;
	int       sizeFont;
	string    nameFont;

	bool click() {
		return area.events.mouseButtonUpLeft;
	}

	bool downClick() {
		return area.events.mouseButtonDownLeft;
	}
};

void drawButton(ButtonText b) {
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

void updateStatusButton(ButtonText& button) {
	updateStatusArea(button.area);
}
