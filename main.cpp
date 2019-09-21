#include "lib/TXLib.h"
#include <string>
#include "Const.h"
#include "WindowObject/Button.h"

void darwRoundedRectangle(int x, int y, int x2, int y2, int r) {
	txSetColour(RGB(0, 0, 0));
	txSetFillColour(RGB(0, 0, 0));

	Win32::RoundRect(txDC(), x, y, x2, y2, r, r);
}

void drawMenu(string *arrText, int countButton, int wight, int height, int r, int spase)
{
	txSelectFont("Arial", 20);
	int x_center_window = WIDTH_WINDOW / 2;
	int y_center_window = HEIGHT_WINDOW / 2;

	//TODO
}

int main()
{
	txCreateWindow(WIDTH_WINDOW, HEIGHT_WINDOW);

	int stutusButton;
	Button b1;
	b1.area.x = 20;
	b1.area.y = 20;
	b1.area.x2 = 120;
	b1.area.y2 = 100;
	b1.fillColor = RGB(255, 0, 0);
	b1.borderColor = RGB(0, 0, 0);
	b1.textColor = RGB(255, 0, 0);
	b1.text = "Button";

	while (true) {
		txBegin();

		txSetFillColor(RGB(255, 255, 255));
		txClear();

		drawButton(b1);
		updateStatusArea(b1.area);
		eventArea events = getEventArea(b1.area);

		if (events.mouseHover) {
			std::cout << "Hover" << std::endl;
		}

		if (events.mouseUnHover) {
			std::cout << "Un Hover" << std::endl;
		}

		if (events.mouseButtonDownRight) {
			std::cout << "Down Right" << std::endl;
		}

		if (events.mouseButtonUpRight) {
			std::cout << "Up Right" << std::endl;
		}

		if (events.mouseButtonDownLeft) {
			b1.fillColor = RGB(255, 255, 0);
			std::cout << "Down Left" << std::endl;
		}

		if (events.mouseButtonUpLeft) {
			b1.fillColor = RGB(255, 0, 0);
			std::cout << "Up Left" << std::endl;
		}



		txSleep(10);
	}

	return 0;
}
