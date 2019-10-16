#pragma once
#include "Image.h"
#include "../lib/TXLib.h"

struct  DragNDrop {
	Image *img;
	int    xImageClick;
	int    yImageClick;
};

DragNDrop setDragNDrop(Image *obj) {
	DragNDrop dnd;

	dnd.img = obj;
	dnd.xImageClick = obj->area.x - txMouseX();
	dnd.yImageClick = obj->area.y - txMouseY();

	return dnd;
}

void moveDragNDropImg(DragNDrop &dnd) {
	if (dnd.img != NULL) {
		if (!txMouseButtons() & 1) {
			dnd.img = NULL;
			return;
		}

		dnd.img->area.x = txMouseX() + dnd.xImageClick;
		dnd.img->area.y = txMouseY() + dnd.yImageClick;
	}
}