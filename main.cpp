#include "lib/TXLib.h"
#include <string>

#include "Const.h"
#include "WindowObject/ButtonText.h"
#include "ConfigRead/ConfigRead.h"

using namespace std;

int main()
{
	ConfigFile config;
	config = readConfigFile("config.txt");

	txCreateWindow(config.widht, config.height);
	txDisableAutoPause();

    HDC pic = txLoadImage("img\\Houses\\Hospital.bmp");
    HDC pik = txLoadImage("img\\Houses\\LowBlueHome.bmp");
    HDC pil = txLoadImage("img\\Houses\\LowGreenHome.bmp");

    HDC fon = txLoadImage ("img\\fon.bmp");
    HDC skver = txLoadImage ("img\\skver.bmp");

	ButtonText b1 =  {{20, 10, 120, 50}, "Начать", RGB(255, 0, 0), RGB(0, 0, 0), RGB(255, 0, 0)};
    ButtonText b2 =  {{20, 60, 120, 100}, "Дома", RGB(255, 0, 0), RGB(0, 0, 0), RGB(255, 0, 0)};
    ButtonText b5 =  {{20, 110, 120, 150}, "Фонтан", RGB(255, 0, 0), RGB(0, 0, 0), RGB(255, 0, 0)};
    ButtonText b8 =  {{20, 160, 120, 200}, "Машина", RGB(255, 0, 0), RGB(0, 0, 0), RGB(255, 0, 0)};
    ButtonText b10 = {{20, 210, 120, 250}, "Госпиталь", RGB(255, 0, 0), RGB(0, 0, 0), RGB(255, 0, 0)};
    ButtonText b11 = {{20, 260, 120, 300}, "Снеговик", RGB(255, 0, 0), RGB(0, 0, 0), RGB(255, 0, 0)};
    ButtonText b12 = {{20, 310, 120, 350}, "Единорог", RGB(255, 0, 0), RGB(0, 0, 0), RGB(255, 0, 0)};

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

		txBitBlt (txDC(), 700, 10, 100, 100, pic, 0, 0);
		txBitBlt (txDC(), 700, 120, 100, 100, pik, 0, 0);
		txBitBlt (txDC(), 700, 230, 100, 100, pil, 0, 0);

		txSleep(10);
	}

    txDeleteDC(pic);
    txDeleteDC(pik);
    txDeleteDC(pil);
    txDeleteDC(fon);
    txDeleteDC(skver);

	return 0;
}
