/*!
\file
\brief Область координат
Файл содержит структуру `Area`,
вспомогательные структуры и функции для работы с ней
*/
#pragma once

/*!
\brief Текущее состояние области
*/
struct StatusArea {
	bool mouseClickLeft  = false; ///< Нажата ЛКМ
	bool mouseClickRight = false; ///< Нажата ПКМ

	bool mouseOver       = false; ///< Мыжка находится в областе
};

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
	StatusArea status; ///< Состояние области
};

/*!
Проверяет нахождение мышки в области
\param area Проверяемая область
\return true - если да, иначе false
*/
bool isMouseOver(AreaCoord area) {
	return In(txMouseX(), area.x, area.x + area.widht) && In(txMouseY(), area.y, area.y + area.height);
}

/*!
Проверяет текущее состояние области
\param area Проверяемая область
\return Текущее состояние области 
*/
StatusArea getStatusArea(AreaCoord area) {
	int statusMouseButton = txMouseButtons();
	StatusArea status;

	status.mouseOver = isMouseOver(area);
	if (status.mouseOver) {
		status.mouseClickLeft = statusMouseButton & 1;
		status.mouseClickRight = statusMouseButton & 2;
	}

	return status;
}

/*!
Обновляет параметры `events` и `status` структуры `AreaCoord`
\param area Обновляемая область
*/
void updateStatusArea(AreaCoord& area) {
	StatusArea newStatus = getStatusArea(area);
	StatusArea oldStatus = area.status;
	EventArea events;

	if (!oldStatus.mouseOver && newStatus.mouseOver) {
		events.mouseHover = true;
	}
	else if (oldStatus.mouseOver && !newStatus.mouseOver) {
		events.mouseUnHover = true;
	}

	if (!oldStatus.mouseClickLeft && newStatus.mouseClickLeft) {
		events.mouseButtonDownLeft = true;
	}
	else if (oldStatus.mouseClickLeft && !newStatus.mouseClickLeft) {
		events.mouseButtonUpLeft = true;
	}

	if (!oldStatus.mouseClickRight && newStatus.mouseClickRight) {
		events.mouseButtonDownRight = true;
	}
	else if (oldStatus.mouseClickRight && !newStatus.mouseClickRight) {
		events.mouseButtonUpRight = true;
	}

	area.events = events;
	area.status = newStatus;
}
