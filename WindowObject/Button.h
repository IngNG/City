#pragma once
#include "../lib/TXLib.h"
#include "Const.h"
#include <string>
#include "Struct.h"

bool isMouseOver(areaCoord area) {
	if (
		In(txMouseX(), area.x, area.x2) &&
		In(txMouseY(), area.y, area.y2)
		) {
		return true;
	}
	else {
		return false;
	}
}

void drawButton(Button b) {
	txSetFillColor(b.fillColor);
	txSetColor(b.borderColor);

	txRectangle(b.area.x, b.area.y, b.area.x2, b.area.y2);
	if (b.text.length() != 0) {
		txDrawText(b.area.x, b.area.y, b.area.x2, b.area.y2, b.text.c_str());
	}
}

void updateStatusArea(areaCoord &area) {
	int statusMouseButton = txMouseButtons();

	area.status.mouseOver = isMouseOver(area);
	area.status.mouseClickLeft = statusMouseButton & 1;
	area.status.mouseClickRight = statusMouseButton & 2;
}

eventArea getEventArea(areaCoord &area) {
	int statusMouseButton = txMouseButtons();
	eventArea newEvents;

	// Наведение на объект
	if (area.status.mouseOver && !area.flags.mouseHover) {
		newEvents.mouseHover = true;
		area.flags.mouseHover = true;
	}
	else if (!area.status.mouseOver && area.flags.mouseHover) {
		area.flags.mouseHover = false;
	}

	// Убирание мышки с объекта
	if (!area.status.mouseOver && !area.flags.mouseUnHover) {
		newEvents.mouseUnHover = true;
		area.flags.mouseUnHover = true;
	}
	else if (area.status.mouseOver && area.flags.mouseUnHover) {
		area.flags.mouseUnHover = false;
	}

	// Нажатие левой кнопки мыши
	if (area.status.mouseOver && area.status.mouseClickLeft && !area.flags.mouseButtonDownLeft) {
		area.flags.mouseButtonDownLeft = true;
		newEvents.mouseButtonDownLeft = true;
	}
	else if (!area.status.mouseClickLeft && area.flags.mouseButtonDownLeft) {
		if (area.status.mouseOver) {
			newEvents.mouseButtonUpLeft = true;
		}
		area.flags.mouseButtonDownLeft = false;
	}

	// Нажатие правой кнопки мыши
	if (area.status.mouseOver && area.status.mouseClickRight && !area.flags.mouseButtonDownRight) {
		area.flags.mouseButtonDownRight = true;
		newEvents.mouseButtonDownRight = true;
	}
	else if (!area.status.mouseClickRight && area.flags.mouseButtonDownRight) {
		if (area.status.mouseOver) {
			newEvents.mouseButtonUpRight = true;
		}
		area.flags.mouseButtonDownRight = false;
	}

	return newEvents;
}