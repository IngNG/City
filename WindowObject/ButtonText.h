/*!
\file
\brief Кнопка

Содержит функции и структуры для рисования кнопок
*/
#pragma once
#include "../lib/TXLib.h"
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
		return area.events.mouseButtonUpLeft;
	}

	bool downClick() {
		return area.events.mouseButtonDownLeft;
	}
};

/*!
Если `visible` равно true, то рисует кнопку, иначе ничего не делает
\param b Кнопка которую нужно нарисовать
*/
void drawButton(ButtonText b) {
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
Обновляет состояние кнопки

Сокращение для `updateStatusArea(button.area)`
\param button Обновляемая кнопка
*/
void updateStatusButton(ButtonText& button) {
	updateStatusArea(button.area, 0);
}
