/*!
\file
\brief Область координат
Файл содержит структуру `Area`,
вспомогательные структуры и функции для работы с ней
*/
#pragma once

/*!
\brief Область координат
*/
struct AreaCoord {
	int        x; ///< Координата X
	int        y; ///< Координата Y
	int        widht; ///< Ширина
	int        height; ///< Высота

	bool mouseClickLeft  ; ///< Нажата ЛКМ
	bool mouseClickRight ; ///< Нажата ПКМ
	bool mouseOver       ; ///< Мыжка находится в областе

	bool mouseButtonUpLeft    ; ///< Нажата ЛКМ
	bool mouseButtonUpRight   ; ///< Нажата ПКМ
	bool mouseButtonDownLeft  ; ///< Отпущена ЛКМ
	bool mouseButtonDownRight ; ///< Отпущена ПКМ
	bool mouseHover           ; ///< Мыжка попала в область
	bool mouseUnHover         ; ///< Мыжка вышла за пределы области
};

/*!
Проверяет нахождение мышки в области
\param area Проверяемая область
\return true - если да, иначе false
*/
bool isMouseOver(AreaCoord area) {
	return
	In(txMouseX(),	area.x,	area.x + area.widht) &&
	In(txMouseY(), 	area.y, area.y + area.height);
}

/*!
Обновляет параметры `events` и `status` структуры `AreaCoord`
\param area Обновляемая область
*/
void updateStatusArea(AreaCoord& area) {

	//Текущее состояние области
	bool mouseOver = isMouseOver(area);
	bool mouseClickLeft = mouseOver && (txMouseButtons() & 1);
	bool mouseClickRight = mouseOver && (txMouseButtons() & 2);

	//События
	area.mouseButtonUpLeft    = false;
	area.mouseButtonUpRight   = false;
	area.mouseButtonDownLeft  = false;
	area.mouseButtonDownRight = false;
	area.mouseHover           = false;
	area.mouseUnHover         = false;

	//Мыжка находится в областе
	bool oldMouseOver       = area.mouseOver;
	if (!oldMouseOver && mouseOver) {
		area.mouseHover = true;
	} else if (oldMouseOver && !mouseOver) {
		area.mouseUnHover = true;
	}

 	//Нажата ЛКМ
	bool oldMouseClickLeft  = area.mouseClickLeft;
	if (!oldMouseClickLeft && mouseClickLeft) {
		area.mouseButtonDownLeft = true;
	} else if (oldMouseClickLeft && !mouseClickLeft) {
		area.mouseButtonUpLeft = true;
	}

	//Нажата ПКМ
	bool oldMouseClickRight = area.mouseClickRight;
	if (!oldMouseClickRight && mouseClickRight) {
		area.mouseButtonDownRight = true;
	} else if (oldMouseClickRight && !mouseClickRight) {
		area.mouseButtonUpRight = true;
	}

	//Новое состояние области
	area.mouseClickLeft = mouseClickLeft;
	area.mouseClickRight = mouseClickRight;
	area.mouseOver = mouseOver;
}
