/*!
\file
\brief Реализует DragNDrop
*/
#pragma once
#include "Image.h"
#include "../TXLib.h"

/*!
\brief Передвигаемое изображение
*/
struct  DragNDrop {
	Image *img; ///< Указатель на картинку
	int    xImageClick; ///< Относительная координата X нажатия на картинку
	int    yImageClick; ///< Относительная координата Y нажатия на картинку
};

/*!
Привязывает новый объект к структуре
\param obj Изображение для перемещения
\return Новый объекст `DragNDrop`
*/
DragNDrop setDragNDrop(Image *obj) {
	DragNDrop dnd;

	dnd.img = obj;
	dnd.xImageClick = obj->area.x - txMouseX();
	dnd.yImageClick = obj->area.y - txMouseY();

	return dnd;
}

/*!
Перемещает объект вслед за мышкой, если ЛКМ отпущена,
то отвязывает изображение от структуры
\param dnd Перемещаемый объект
*/
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
