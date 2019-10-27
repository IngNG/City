/*!
\file
\brief Кнопка

Содержит функции и структуры для рисования картинок
*/
#pragma once
#include "../lib/TXLib.h"
#include "Area.h"
#include <fstream>

// Это что-бы VS не ругался
#pragma warning(disable:4996)

/*!
\brief Картинка
*/
struct Image {
	AreaCoord area; ///< Область, где рисуется картинка
	string adress;
	string category; ///< Категория картинки
	HDC    img; ///< Дескриптор рисования с картинкой. Получить можно функцией `txLoadImage` из библиотеки TXLib

	int    widht; ///< Ширина картинки
	int    height; ///< Высота картинки
	bool   visible; ///< Рисуется ли картинка

	/*!
	Проверяет нажата ли картинка.

	Сокращение для `img.area.events.mouseButtonUpLeft`.
	\return true - если нажата, иначе false
	*/
	bool click() {
		return area.events.mouseButtonUpLeft;
	}

	bool downClick() {
		return area.events.mouseButtonDownLeft;
	}
};

void drawImage(Image i) {
	if (i.visible) {
		Win32::TransparentBlt(
			txDC(),
			i.area.x, i.area.y,
			i.area.widht, i.area.height,
			i.img,
			0, 0,
			i.widht, i.height,
			TX_WHITE
		);
	}
}

void updateStatusImage(Image &img) {
	updateStatusArea(img.area);
}

int getWidhtImg(string adress) {
	unsigned char info[54];

	FILE* f = fopen(adress.c_str(), "rb");
	fread(info, sizeof(unsigned char), 54, f);
	fclose(f);

	int width = *(int*)&info[18];
	return width;
}

int getHeightImg(string adress) {
	unsigned char info[54];

	FILE* f = fopen(adress.c_str(), "rb");
	fread(info, sizeof(unsigned char), 54, f);
	fclose(f);

	int height = *(int*)&info[22];
	return height;
}
