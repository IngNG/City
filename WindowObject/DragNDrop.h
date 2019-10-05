#pragma once
#include "Image.h"

struct  DragNDrop {
	Image* img;
	int xImageClick;
	int yImageClick;
};

void setDragNDrop(DragNDrop &dnd, Image *obj) {
	dnd.img = obj;
	dnd.xImageClick = obj->area.x - txMouseX();
	dnd.yImageClick = obj->area.y - txMouseY();
}

void moveDragNDropImg(DragNDrop &dnd) {
	if (dnd.img != NULL) {
		dnd.img->area.x = txMouseX() + dnd.xImageClick;
		dnd.img->area.y = txMouseY() + dnd.yImageClick;
	}
}