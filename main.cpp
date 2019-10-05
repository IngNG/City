#include "lib/TXLib.h"
#include <string>

#include "ConfigRead/ConfigApp.h"
#include "WindowObject/ButtonText.h"
#include "WindowObject/Image.h"
using namespace std;

int main()
{
	ConfigApp config = readConfigFile("config.txt");
	bool visible11 = false;
	bool visible12 = false;
	bool visible13 = false;

	txCreateWindow(atoi(getValueSetting(config, "wight").c_str()), atoi(getValueSetting(config, "height").c_str()));
	txDisableAutoPause();

	HDC fon	  =	txLoadImage("img\\fon.bmp");
	HDC skver = txLoadImage("img\\skver.bmp");

	const int COUNT_BUTTON = 7;
    ButtonText buttons[COUNT_BUTTON];
	buttons[0] = {{20, 10, 120, 50}, "������", RGB(255, 0, 0), RGB(0, 0, 0), RGB(255, 0, 0), true};
    buttons[1] = {{20, 60, 120, 100}, "����", RGB(255, 0, 0), RGB(0, 0, 0), RGB(255, 0, 0), true};
    buttons[2] = {{20, 110, 120, 150}, "������", RGB(255, 0, 0), RGB(0, 0, 0), RGB(255, 0, 0), true};
    buttons[3] = {{20, 160, 120, 200}, "������", RGB(255, 0, 0), RGB(0, 0, 0), RGB(255, 0, 0), true};
    buttons[4] = {{20, 210, 120, 250}, "���������", RGB(255, 0, 0), RGB(0, 0, 0), RGB(255, 0, 0), true};
    buttons[5] = {{20, 260, 120, 300}, "��������", RGB(255, 0, 0), RGB(0, 0, 0), RGB(255, 0, 0), true};
    buttons[6] = {{20, 310, 120, 350}, "��������", RGB(255, 0, 0), RGB(0, 0, 0), RGB(255, 0, 0), true};

	const int COUNT_CAR = 4;
    Image car[COUNT_CAR];
    car[0] = {{300, 10, 400, 100}, 79, 58, txLoadImage("img\\Houses\\Hospital.bmp"), false};
    car[1] = {{300, 120, 400, 190}, 66, 58, txLoadImage("img\\Houses\\LowBlueHome.bmp"), false};
    car[2] = {{300, 210, 400, 300}, 66, 58, txLoadImage("img\\Houses\\LowGreenHome.bmp"), false};
    car[3] = {{300, 320, 400, 450}, 66, 99, txLoadImage("img\\Houses\\TallYellowHome.bmp"), false};

    bool visible = false;
    bool visible2 = false;
    bool visible3 = false;
    bool visible4 = false;

    EventArea event;

	const int COUNT_IMG = 6;
    Image img[COUNT_IMG];
    img[0] = {{720,  30, 800, 110}, 79, 58, txLoadImage("img\\Houses\\Hospital.bmp"), true};
    img[1] = {{720, 140, 800, 220}, 66, 58, txLoadImage("img\\Houses\\LowBlueHome.bmp"), true};
    img[2] = {{720, 250, 800, 330}, 66, 58, txLoadImage("img\\Houses\\LowGreenHome.bmp"), true};
    img[3] = {{720, 350, 800, 450}, 66, 99, txLoadImage("img\\Houses\\TallYellowHome.bmp"), true};
    img[4] = {{720,  30, 800, 110}, 36, 26, txLoadImage("img\\fontan.bmp"), true};
    img[5] = {{720, 140, 800, 220}, 11, 13, txLoadImage("img\\snowmen.bmp"), true};

	while (!GetAsyncKeyState(VK_ESCAPE)) {
		txBegin();

		txSetFillColor(RGB(255, 255, 255));
		txClear();

        Win32::TransparentBlt(txDC(), 150, 0, 700, 700, fon,0,0, 123,124, TX_WHITE);
        Win32::TransparentBlt(txDC(), 300, 200, 200, 160, skver, 0, 0, 175, 110, TX_WHITE);

        for (int n_button = 0; n_button < 6; n_button++)
        {
            drawButton(buttons[n_button]);
        }

        event = getEventArea(img[0].area);
        if (event.mouseButtonUpLeft && img[0].visible)
        {
            car[0].visible = !car[0].visible;
            txSleep(200);
        }


        event = getEventArea(img[1].area);
        if (event.mouseButtonUpLeft && img[1].visible)
        {
            car[1].visible = !car[1].visible;
            txSleep(200);
        }


        event = getEventArea(img[2].area);
        if (event.mouseButtonUpLeft && img[2].visible)
        {
            car[2].visible = !car[2].visible;
            txSleep(200);
        }


        event = getEventArea(img[3].area);
        if (event.mouseButtonUpLeft && img[3].visible)
        {
            car[3].visible = !car[3].visible;
            txSleep(200);
        }


	for (int i = 0; i < COUNT_CAR; i++) {
		drawImage(car[i]);
	}


		if (txMouseX() > 20 and
			txMouseX() < 120 and
			txMouseY() > 60 and
			txMouseY() < 100 and
			txMouseButtons() &1
		)
		{
			 visible11 = true;
			 visible12 = false;
			 visible13 = false;
			 txSleep(200);
		}

        if (txMouseX() > 20 and
			txMouseX() < 110 and
			txMouseY() > 120 and
			txMouseY() < 150 and
			txMouseButtons() &1
        )
        {
			visible11 = false;
			visible12 = true;
			visible13 = false;
			txSleep(200);
        }

        if (txMouseX() > 20 and
            txMouseX() < 260 and
            txMouseY() > 260 and
            txMouseY() < 300 and
            txMouseButtons() &1
        )
        {
			visible11 = false;
			visible12 = false;
			visible13 = true;
			txSleep(200);
        }

        //for(int n_img = 0;n_img < 4;n_img++)
        //{
            //drawImage(img[n_img]);
        //}

        for (int i = 0; i < 7; i++)
        {
			img[i].visible = false;
        }

        if (visible11)
        {
			img[0].visible = true;
			img[1].visible = true;
			img[2].visible = true;
			img[3].visible = true;
        }

        if (visible12)
        {
			img[4].visible = true;
        }
        if (visible13)
        {
			img[5].visible = true;
        }


        for (int i = 0; i < 7; i++)
        {
            drawImage(img[i]);
        }

		txSleep(10);
	}

	txDeleteDC(fon);
	txDeleteDC(skver);

	for (int i = 0; i < COUNT_CAR; i++) {
		txDeleteDC(car[i].img);
	}

	for (int i = 0; i < COUNT_IMG; i++) {
		txDeleteDC(img[i].img);
	}

	return 0;
}
