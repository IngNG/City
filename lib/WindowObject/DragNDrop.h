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
void moveDragNDropImg(DragNDrop &dnd, int min_x, int max_x, int min_y, int max_y) {
	if (dnd.img != NULL) {
		if (!txMouseButtons() & 1) {
			dnd.img = NULL;
			return;
		}

		/*dnd.img->area.x = txMouseX() + dnd.xImageClick;
		dnd.img->area.y = txMouseY() + dnd.yImageClick;*/

		int new_x = txMouseX() + dnd.xImageClick;
		int new_y = txMouseY() + dnd.yImageClick;

		max_x = max_x - dnd.img->area.widht;
		max_y = max_y - dnd.img->area.height;

		if (new_x > max_x) {
			new_x = max_x;
		}
		else if (new_x < min_x) {
			new_x = min_x;
		}

		if (new_y > max_y) {
			new_y = max_y;
		}
		else if (new_y < min_y) {
			new_y = min_y;
		}

		dnd.img->area.x = new_x;
		dnd.img->area.y = new_y;
	}
}
