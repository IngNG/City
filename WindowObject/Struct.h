#pragma once
#include "../lib/TXLib.h"
#include <string>

struct statusArea {
	bool mouseClickLeft = false;
	bool mouseClickRight = false;

	bool mouseOver = false;
};

struct eventArea {
	bool mouseButtonUpLeft = false;
	bool mouseButtonUpRight = false;

	bool mouseButtonDownLeft = false;
	bool mouseButtonDownRight = false;

	bool mouseHover = false;
	bool mouseUnHover = false;
};

struct areaCoord {
	int x;
	int y;
	int x2;
	int y2;

	eventArea flags = {false, false, false, false, false, true};
	statusArea status;
};

struct Button {
	areaCoord area;

	string text;
	COLORREF fillColor;
	COLORREF borderColor;
	COLORREF textColor;
};