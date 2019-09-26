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

struct HouseVariant
{
   int x;
   int y;
   int height;
   HDC pic;
};

void drawButon(HouseVariant c)
{
    txRectangle(c.x+0, c.y+100, c.x+700, c.y+600);
    txBitBlt(txDC(), c.x+200, c.y+200, 100, c.height, c.pic);
/*

    BUTON c1 = {0,0,200,pic};
    drawButon(c1);
*/
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

    HDC pic = txLoadImage("img\\Houses\\Hospital.bmp");
    HDC pik = txLoadImage("img\\Houses\\LowBlueHome.bmp");
    HDC pil = txLoadImage("img\\Houses\\LowGreenHome.bmp");

    HDC fon = txLoadImage ("img\\fon.bmp");
    HDC skver = txLoadImage ("img\\skver.bmp");

	int stutusButton;
	Button b1 =  {{20, 10, 120, 50}, "Начать", RGB(255, 0, 0), RGB(0, 0, 0), RGB(255, 0, 0)};
    Button b2 =  {{20, 60, 120, 100}, "дома", RGB(255, 0, 0), RGB(0, 0, 0), RGB(255, 0, 0)};
    Button b5 =  {{20, 110, 120, 150}, "фонтан", RGB(255, 0, 0), RGB(0, 0, 0), RGB(255, 0, 0)};
    Button b8 =  {{20, 160, 120, 200}, "машина", RGB(255, 0, 0), RGB(0, 0, 0), RGB(255, 0, 0)};
    Button b10 = {{20, 210, 120, 250}, "госпиталь", RGB(255, 0, 0), RGB(0, 0, 0), RGB(255, 0, 0)};
    Button b11 = {{20, 260, 120, 300}, "снеговик", RGB(255, 0, 0), RGB(0, 0, 0), RGB(255, 0, 0)};
    Button b12 = {{20, 310, 120, 350}, "единорог", RGB(255, 0, 0), RGB(0, 0, 0), RGB(255, 0, 0)};

	while (!GetAsyncKeyState(VK_ESCAPE)) {
		txBegin();

		txSetFillColor(RGB(255, 255, 255));
		txClear();

        Win32::TransparentBlt (txDC(),200,0,600,600,fon,0,0, 123,124, TX_WHITE);
        Win32::TransparentBlt (txDC(),300,200,200,160,skver,0,0, 175,110, TX_WHITE);

		drawButton(b1);
		drawButton(b2);
		drawButton(b5);
		drawButton(b8);
		drawButton(b10);
		drawButton(b11);
		drawButton(b12);
		updateStatusArea(b1.area);
		eventArea events = getEventArea(b1.area);

		txBitBlt (txDC(), 700, 10, 100, 100, pic, 0, 0);
		txBitBlt (txDC(), 700, 120, 100, 100, pik, 0, 0);
		txBitBlt (txDC(), 700, 230, 100, 100, pil, 0, 0);

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

    txDeleteDC(pic);
    txDeleteDC(pik);
    txDeleteDC(pil);
    txDeleteDC(fon);
    txDeleteDC(skver);

	return 0;
}
