#include "lib/TXLib.h"
#include <string>
#include "Const.h"
#include "WindowObject/Button.h"

struct Pic
{
int x;
int y ;
int width;
int visota;
HDC pic;
};

void drawPic (Pic p)
{
    txSetFillColor(TX_GRAY);
    txRectangle(p.x + 0, p.y + 100, p.x + 700, p.y + 600);
    txBitBlt(txDC(), p.x +200,p.y + 200, p.width, p.visota, p.pic);
}

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
	txDisableAutoPause();

HDC fon = txLoadImage ("img\\fon.bmp");
HDC skver = txLoadImage ("img\\skver.bmp");
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

	while (!GetAsyncKeyState(VK_ESCAPE)) {
		txBegin();

		txSetFillColor(RGB(255, 255, 255));
		txClear();

Win32::TransparentBlt (txDC(),200,0,600,600,fon,0,0, 123,124, TX_WHITE);
Win32::TransparentBlt (txDC(),300,200,200,160,skver,0,0, 175,110, TX_WHITE);
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
