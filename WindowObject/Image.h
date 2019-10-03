#pragma once
#include "../lib/TXLib.h"
#include "Area.h"

struct Image {
	AreaCoord area;
	int widht;
	int height;
	HDC img;
};

void drawImage(Image i) {
	Win32::TransparentBlt(txDC(), i.area.x, i.area.y, i.area.x2 - i.area.x, i.area.y2 - i.area.y, i.img,0,0, i.widht, i.height, TX_WHITE);
}

EventArea getEventImage(Image &img) {
	return getEventArea(img.area);
}