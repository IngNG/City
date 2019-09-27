#pragma once
#include "../lib/TXLib.h"
#include "Area.h"

struct Image {
	AreaCoord area;

	HDC img;
};

void drawImage(Image p) {
	txRectangle(p.area.x, p.area.y, p.area.x2, p.area.y2);
	txBitBlt(txDC(), p.area.x, p.area.y, p.area.x2, p.area.y2, p.area.img);
}