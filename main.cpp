#include "lib/TXLib.h"
#include <string>
#include "Const.h"
#include "WindowObject\Button.h"

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
	
	Button b1(20, 20, 120, 100, RGB(255, 0, 0), RGB(255, 255, 255));
	Button b2(20, 130, 120, 220, RGB(255, 0, 0), RGB(255, 255, 255));
	int stutusButton;

	while (true) {
		txBegin();

		txSetFillColor(RGB(255, 255, 255));
		txClear();

		b1.draw();
		b2.draw();

		stutusButton = b1.getStatus();
		if (stutusButton & MOUSE_DOWM_LEFT_BUTTON) {
			std::cout << "One button down left" << std::endl;
		}
		
		if (stutusButton & MOUSE_DOWN_RIGHT_BUTTON) {
			std::cout << "One button down right" << std::endl;
		}

		if (stutusButton & MOUSE_UP_LEFT_BUTTON) {
			txMessageBox("Кнопка #1 нажата");
		}

		if (stutusButton & MOUSE_UP_RIGHT_BUTTON) {
			std::cout << "One button up right" << std::endl;
		}

		if (stutusButton & MOUSE_HOVER) {
			std::cout << "One button hover" << std::endl;
		}

		stutusButton = b2.getStatus();
		if (stutusButton & MOUSE_DOWM_LEFT_BUTTON) {
			std::cout << "Two button down left" << std::endl;
		}

		if (stutusButton & MOUSE_DOWN_RIGHT_BUTTON) {
			std::cout << "Two button down right" << std::endl;
		}

		if (stutusButton & MOUSE_UP_LEFT_BUTTON) {
			txMessageBox("Кнопка #2 нажата");
		}

		if (stutusButton & MOUSE_UP_RIGHT_BUTTON) {
			std::cout << "Two button up right" << std::endl;
		}

		if (stutusButton & MOUSE_HOVER) {
			std::cout << "Two button hover" << std::endl;
		}

		txSleep(10);
	}

	return 0;
}
