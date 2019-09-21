#pragma once
#include "Object.h"
#include <string>

class Button: public Object {
private:
	COLORREF borderColor;
	COLORREF textColor;
	COLORREF fillColor;
	string text;

	int thicknessBorder = 3;

public:
	Button():
	Object(0, 0, 0, 0) {
		this->borderColor = RGB(0, 0, 0);
		this->fillColor = RGB(0, 0, 0);
		this->textColor = RGB(255, 255, 255);
		this->text = "";
	}

	Button(
		int x,
		int y,
		int x2,
		int y2,
		COLORREF borderColor,
		COLORREF fillColor
	):
	Object(x, y, x2, y2) {
		this->borderColor = borderColor;
		this->fillColor = fillColor;
		this->textColor = RGB(255, 255, 255);
		this->text = "";
	}

	Button(
		int x,
		int y,
		int x2,
		int y2,
		string text,
		COLORREF borderColor,
		COLORREF fillColor,
		COLORREF textColor
	):
	Object(x, y, x2, y2) {
		this->borderColor = borderColor;
		this->fillColor = fillColor;
		this->textColor = textColor;
		this->text = text;
	}

	void draw() {
		txSetColor(this->borderColor, this->thicknessBorder);
		txSetFillColor(this->fillColor);

		txRectangle(this->getX(), this->getY(), this->getX2(), this->getY2());
		if (this->text.length() != 0) {
			txDrawText(this->getX(), this->getY(), this->getX2(), this->getY2(), this->text.c_str());
		}
	}
//-------------TEXT----------------
	string getText() {
		return this->text;
	}

	void setText(string text) {
		this->text = text;
	}
//-----------COLOR----------------
	void setColor(
		COLORREF borderColor,
		COLORREF fillColor,
		COLORREF textColor
	) {
		this->borderColor = borderColor;
		this->fillColor = fillColor;
		this->textColor = textColor;
	}
//--------FILL-COLOR----------------
	void setFillColor(COLORREF color) {
		this->fillColor = color;
	}
};