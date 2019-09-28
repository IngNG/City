#include "lib/TXLib.h"
#include <string>
#include "Const.h"

#include "WindowObject/ButtonText.h"

int main()
{
	txCreateWindow(WIDTH_WINDOW, HEIGHT_WINDOW);
	txDisableAutoPause();

    HDC pic = txLoadImage("img\\Houses\\Hospital.bmp");
    HDC pik = txLoadImage("img\\Houses\\LowBlueHome.bmp");
    HDC pil = txLoadImage("img\\Houses\\LowGreenHome.bmp");
    HDC pit = txLoadImage("img\\Houses\\LowYellowHome.bmp");
    HDC pin = txLoadImage("img\\Houses\\TallBlueHome.bmp");
    HDC pim = txLoadImage("img\\Houses\\TallGreenHome.bmp");

    HDC fon = txLoadImage ("img\\fon.bmp");
    HDC skver = txLoadImage ("img\\skver.bmp");



    ButtonText buttons [7];
	buttons[0] =  {{20, 10, 120, 50}, "Начать", RGB(255, 0, 0), RGB(0, 0, 0), RGB(255, 0, 0)};
    buttons[1] =  {{20, 60, 120, 100}, "Дома", RGB(255, 0, 0), RGB(0, 0, 0), RGB(255, 0, 0)};
    buttons[2] =  {{20, 110, 120, 150}, "Фонтан", RGB(255, 0, 0), RGB(0, 0, 0), RGB(255, 0, 0)};
    buttons[3] =  {{20, 160, 120, 200}, "Машина", RGB(255, 0, 0), RGB(0, 0, 0), RGB(255, 0, 0)};
    buttons[4] = {{20, 210, 120, 250}, "Госпиталь", RGB(255, 0, 0), RGB(0, 0, 0), RGB(255, 0, 0)};
    buttons[5] = {{20, 260, 120, 300}, "Снеговик", RGB(255, 0, 0), RGB(0, 0, 0), RGB(255, 0, 0)};
    buttons[6] = {{20, 310, 120, 350}, "Единорог", RGB(255, 0, 0), RGB(0, 0, 0), RGB(255, 0, 0)};

	while (!GetAsyncKeyState(VK_ESCAPE)) {
		txBegin();

		txSetFillColor(RGB(255, 255, 255));
		txClear();

        Win32::TransparentBlt (txDC(),150,0,700,700,fon,0,0, 123,124, TX_WHITE);
        Win32::TransparentBlt (txDC(),300,200,200,160,skver,0,0, 175,110, TX_WHITE);

        for (int  n_button = 0; n_button < 6; n_button++)
        {
          drawButton(buttons[n_button]);
        }

          if (txMouseX() > 20 and
              txMouseX() < 120 and
              txMouseY() > 60 and
              txMouseY() < 100 and
              txMouseButtons() &1
              )

        txBitBlt (txDC(), 700, 10, 100, 100, pic, 0, 0);

        if (txMouseX() > 20 and
              txMouseX() < 120 and
              txMouseY() > 60 and
              txMouseY() < 100 and
              txMouseButtons() &1
              )

		txBitBlt (txDC(), 700, 100, 100, 100, pik, 0, 0);

		if (txMouseX() > 20 and
              txMouseX() < 120 and
              txMouseY() > 60 and
              txMouseY() < 100 and
              txMouseButtons() &1
              )
		txBitBlt (txDC(), 700, 190, 100, 100, pil, 0, 0);

		if (txMouseX() > 20 and
              txMouseX() < 120 and
              txMouseY() > 60 and
              txMouseY() < 100 and
              txMouseButtons() &1
              )
		txBitBlt (txDC(), 700, 280, 100, 100, pit, 0, 0);

		if (txMouseX() > 20 and
              txMouseX() < 120 and
              txMouseY() > 60 and
              txMouseY() < 100 and
              txMouseButtons() &1
              )
		txBitBlt (txDC(), 700, 350, 100, 100, pin, 0, 0);

		if (txMouseX() > 20 and
              txMouseX() < 120 and
              txMouseY() > 60 and
              txMouseY() < 100 and
              txMouseButtons() &1
              )
		txBitBlt (txDC(), 700, 460, 100, 100, pim, 0, 0);

		txSleep(10);
	}

    txDeleteDC(pic);
    txDeleteDC(pik);
    txDeleteDC(pil);
    txDeleteDC(fon);
    txDeleteDC(skver);

	return 0;
}
