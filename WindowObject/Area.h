/*!
\file
\brief Область координат
Файл содержит структуру `Area`,
вспомогательные структуры и функции для работы с ней
*/
#pragma once

/*!
\brief События произошедшие в области
*/
struct EventArea {
	bool mouseButtonUpLeft    = false; ///< Нажата ЛКМ
	bool mouseButtonUpRight   = false; ///< Нажата ПКМ

	bool mouseButtonDownLeft  = false; ///< Отпущена ЛКМ
	bool mouseButtonDownRight = false; ///< Отпущена ПКМ

	bool mouseHover           = false; ///< Мыжка попала в область
	bool mouseUnHover         = false; ///< Мыжка вышла за пределы области
};

/*!
\brief Область координат
*/
struct AreaCoord {
	int        x; ///< Координата X
	int        y; ///< Координата Y
	int        widht; ///< Ширина
	int        height; ///< Высота

	EventArea  events; ///< События произошедшие в области

	bool mouseClickLeft  ; ///< Нажата ЛКМ
	bool mouseClickRight ; ///< Нажата ПКМ
	bool mouseOver       ; ///< Мыжка находится в областе
};

/*!
Проверяет нахождение мышки в области
\param area Проверяемая область
\return true - если да, иначе false
*/
bool isMouseOver(AreaCoord area, int CAM_X = 0) {
	return
	In(txMouseX(),	area.x + CAM_X,	area.x + CAM_X + area.widht) &&
	In(txMouseY(), 	area.y, 		area.y + area.height);
}

/*!
Обновляет параметры `events` и `status` структуры `AreaCoord`
\param area Обновляемая область
*/
void updateStatusArea(AreaCoord& area, int CAM_X) {

	//Текущее состояние области
	bool mouseOver = isMouseOver(area, CAM_X);
	bool mouseClickLeft = mouseOver && (txMouseButtons() & 1);
	bool mouseClickRight = mouseOver && (txMouseButtons() & 2);

	EventArea events;

	bool oldMouseOver       = area.mouseOver; 		//Мыжка находится в областе
	if (!oldMouseOver && mouseOver) {
		events.mouseHover = true;
	}
	else if (oldMouseOver && !mouseOver) {
		events.mouseUnHover = true;
	}

	bool oldMouseClickLeft  = area.mouseClickLeft; 	//Нажата ЛКМ
	if (!oldMouseClickLeft && mouseClickLeft) {
		events.mouseButtonDownLeft = true;
	}
	else if (oldMouseClickLeft && !mouseClickLeft) {
		events.mouseButtonUpLeft = true;
	}

	bool oldMouseClickRight = area.mouseClickRight; //Нажата ПКМ
	if (!oldMouseClickRight && mouseClickRight) {
		events.mouseButtonDownRight = true;
	}
	else if (oldMouseClickRight && !mouseClickRight) {
		events.mouseButtonUpRight = true;
	}

	area.events = events;

	area.mouseClickLeft = mouseClickLeft; 		//Нажата ЛКМ
	area.mouseClickRight = mouseClickRight; 	//Нажата ПКМ
	area.mouseOver = mouseOver; 				//Мыжка находится в областе
}
