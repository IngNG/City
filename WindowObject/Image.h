#pragma once
#include "../lib/TXLib.h"
#include "Area.h"

struct Image {
	AreaCoord area;
	int widht;
	int height;
	HDC img;

	bool visible = true;
};

void drawImage(Image i) {
	if (i.visible) {
		Win32::TransparentBlt(txDC(), i.area.x, i.area.y, i.area.x2 - i.area.x, i.area.y2 - i.area.y, i.img, 0, 0, i.widht, i.height, TX_WHITE);
	}
}

EventArea getEventImage(Image &img) {
	return getEventArea(img.area);
}