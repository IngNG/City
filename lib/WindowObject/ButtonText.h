/*!
\file
\brief Кнопка

Содержит функции и структуры для рисования кнопок
*/
#pragma once
#include "../TXLib.h"
#include <string>
#include "Area.h"

/*!
\brief Кнопка с текстом
*/
struct ButtonText {
	AreaCoord area; ///< Область, где рисуется кнопка

	string    text; ///< Текст
	COLORREF  fillColor; ///< Цвет заливки
	COLORREF  borderColor; ///< Цвет границы
	COLORREF  textColor; ///< Цвет текста

	bool      visible; ///< Рисуется ли кнопка
    string    category; ///< Категория которая быдет активирована при нажатии
	int       sizeFont; ///< Размер шрифта
	string    nameFont; ///< Шрифт

	/*!
	Проверяет нажата ли кнопка.

	Сокращение для `button.area.events.mouseButtonUpLeft`.
	\return true - если нажата, иначе false
	*/
	bool click() {
		return area.mouseButtonUpLeft;
	}

	bool downClick() {
		return area.mouseButtonDownLeft;
	}
};

/*!
Если `visible` равно true, то рисует кнопку, иначе ничего не делает
\param b Кнопка которую нужно нарисовать
*/
void drawButton(ButtonText &b) {
	updateStatusArea(b.area);
	if (b.visible) {
		txSetFillColor(b.fillColor);
		txSetColor(b.borderColor);
		txSelectFont(b.nameFont.c_str(), b.sizeFont);

		txRectangle(
			b.area.x, b.area.y,
			b.area.x + b.area.widht, b.area.y + b.area.height
		);
		if (b.text.length() != 0) {
			txDrawText(
				b.area.x, b.area.y,
				b.area.x + b.area.widht, b.area.y + b.area.height,
				b.text.c_str()
			);
		}
	}
}

/*!
Автоматически просчитовает координаты кнопок в меню
\param[out] button Указатель на массив с объектами для инициализации
\param countButton Кол-во кнопок
\param x X-координата меню
\param y Y-координата начала меню
\param widhtButton Ширина кнопок
\param heightButton Высота кнопок
\param indent Отступ между кнопками
\param fill Цвет заливки
\param border Цвет границы
\param text Цвет текста
*/
void initButtonMenu(
	ButtonText* button, int countButton,
	int x, int y,
	int widhtButton, int heightButton, int indent,
	COLORREF fill, COLORREF border, COLORREF text
) {
	for (int i = 0; i < countButton; i++) {
		button[i].area.x = x;
		button[i].area.y = y + (indent * i) + (heightButton * i);
		button[i].area.widht = widhtButton;
		button[i].area.height = heightButton;
		button[i].fillColor = fill;
		button[i].borderColor = border;
		button[i].textColor = text;
		button[i].category = "";

		button[i].area.mouseButtonUpLeft = false;
		button[i].area.mouseButtonUpRight = false;
		button[i].area.mouseButtonDownLeft = false;
		button[i].area.mouseButtonDownRight = false;
		button[i].area.mouseHover = false;
		button[i].area.mouseUnHover = false;

		button[i].area.mouseOver = false;
		button[i].area.mouseClickRight = false;
		button[i].area.mouseClickLeft = false;
	}
}
