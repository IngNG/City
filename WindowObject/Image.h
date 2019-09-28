#pragma once
#include "../lib/TXLib.h"
#include "Area.h"

struct Image {
	AreaCoord area;
 int shirina;
 int vysota;
	HDC img;
};

void drawImage(Image p) {
	txRectangle     (p.area.x, p.area.y, p.area.x2, p.area.y2);
	Win32::TransparentBlt (txDC(),p.area.x, p.area.y, p.area.x2 - p.area.x, p.area.y2 - p.area.y, p.img,0,0, p.shirina,p.vysota, TX_WHITE);

              //txBitBlt(txDC(), p.area.x, p.area.y, p.area.x2 - p.area.x, p.area.y2 - p.area.y, p.img);
}
