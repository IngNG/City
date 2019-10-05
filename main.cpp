#include "lib/TXLib.h"
#include <string>

#include "ConfigRead/ConfigApp.h"
#include "WindowObject/ButtonText.h"
#include "WindowObject/Image.h"
#include "WindowObject/DragNDrop.h"
using namespace std;

int main()
{
	ConfigApp config = readConfigFile("config.txt");
	bool visible11 = false;
	bool visible12 = false;
	bool visible13 = false;

	txCreateWindow(atoi(getValueSetting(config, "wight").c_str()), atoi(getValueSetting(config, "height").c_str()));
	txDisableAutoPause();

	HDC fon   = txLoadImage("img\\fon.bmp");
	HDC skver = txLoadImage("img\\skver.bmp");

	const int COUNT_BUTTON = 7;
    ButtonText buttons[COUNT_BUTTON];
	buttons[0] = {{20, 10, 100, 40}, "Начать", RGB(255, 0, 0), RGB(0, 0, 0), RGB(255, 0, 0), true};
    buttons[1] = {{20, 60, 100, 40}, "Дома", RGB(255, 0, 0), RGB(0, 0, 0), RGB(255, 0, 0), true};
    buttons[2] = {{20, 110, 100, 40}, "Фонтан", RGB(255, 0, 0), RGB(0, 0, 0), RGB(255, 0, 0), true};
    buttons[3] = {{20, 160, 100, 40}, "Машина", RGB(255, 0, 0), RGB(0, 0, 0), RGB(255, 0, 0), true};
    buttons[4] = {{20, 210, 100, 40}, "Госпиталь", RGB(255, 0, 0), RGB(0, 0, 0), RGB(255, 0, 0), true};
    buttons[5] = {{20, 260, 100, 40}, "Снеговик", RGB(255, 0, 0), RGB(0, 0, 0), RGB(255, 0, 0), true};
    buttons[6] = {{20, 310, 100, 40}, "Единорог", RGB(255, 0, 0), RGB(0, 0, 0), RGB(255, 0, 0), true};

	const int COUNT_CAR = 4;
    Image car[COUNT_CAR];
    car[0] = {{300, 10, 100, 90}, 79, 58, txLoadImage("img\\Houses\\Hospital.bmp"), true};
    car[1] = {{300, 120, 100, 70}, 66, 58, txLoadImage("img\\Houses\\LowBlueHome.bmp"), true};
    car[2] = {{300, 210, 100, 90}, 66, 58, txLoadImage("img\\Houses\\LowGreenHome.bmp"), true};
    car[3] = {{300, 320, 100, 130}, 66, 99, txLoadImage("img\\Houses\\TallYellowHome.bmp"), true};

    bool visible = false;
    bool visible2 = false;
    bool visible3 = false;
    bool visible4 = false;

    EventArea event;

	const int COUNT_IMG = 6;
    Image img[COUNT_IMG];
    img[0] = {{720,  30, 80, 80}, 79, 58, txLoadImage("img\\Houses\\Hospital.bmp"), true};
    img[1] = {{720, 140, 80, 80}, 66, 58, txLoadImage("img\\Houses\\LowBlueHome.bmp"), true};
    img[2] = {{720, 250, 80, 80}, 66, 58, txLoadImage("img\\Houses\\LowGreenHome.bmp"), true};
    img[3] = {{720, 350, 80, 100}, 66, 99, txLoadImage("img\\Houses\\TallYellowHome.bmp"), true};
    img[4] = {{720,  30, 80, 80}, 36, 26, txLoadImage("img\\fontan.bmp"), true};
    img[5] = {{720, 140, 80, 80}, 11, 13, txLoadImage("img\\snowmen.bmp"), true};

	DragNDrop dndImage = {NULL, 0, 0};

	while (!GetAsyncKeyState(VK_ESCAPE)) {
		txBegin();
		txSetFillColor(RGB(255, 255, 255));
		txClear();

		moveDragNDropImg(dndImage);

        Win32::TransparentBlt(txDC(), 150, 0, 700, 700, fon,0,0, 123,124, TX_WHITE);
        Win32::TransparentBlt(txDC(), 300, 200, 200, 160, skver, 0, 0, 175, 110, TX_WHITE);

        for (int n_button = 0; n_button < 6; n_button++)
        {
            drawButton(buttons[n_button]);
        }

		if (dndImage.img == NULL) {
			for (int i = 0; i < COUNT_CAR; i++) {
				event = getEventArea(car[i].area);
				if (event.mouseButtonDownLeft) {
					setDragNDrop(dndImage, &car[i]);
				}
			}
		}
		else {
			event = getEventArea(dndImage.img->area);
			if (event.mouseButtonUpLeft) {
				dndImage.img = NULL;
			}
		}

        event = getEventArea(img[0].area);
        if (event.mouseButtonUpLeft)
        {
            visible = !visible;
            txSleep(200);
        }

        if (visible)
        {
            drawImage(car[0]);
        }

        event = getEventArea(img[1].area);
        if (event.mouseButtonUpLeft)
        {
            visible2 = !visible2;
            txSleep(200);
        }

        if (visible2)
        {
            drawImage(car[1]);
        }

        event = getEventArea(img[2].area);
        if (event.mouseButtonUpLeft)
        {
            visible3 = !visible3;
            txSleep(200);
        }

        if (visible3)
        {
            drawImage(car[2]);
        }

        event = getEventArea(img[3].area);
        if (event.mouseButtonUpLeft)
        {
            visible4 = !visible4;
            txSleep(200);
        }

        if (visible4)
        {
            drawImage(car[3]);
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

        if (visible11)
        {
            drawImage(img[0]);
            drawImage(img[1]);
            drawImage(img[2]);
            drawImage(img[3]);
        }

        if (visible12)
        {
            drawImage(img[4]);
        }
        if (visible13)
        {
            drawImage(img[5]);
        }

		txEnd();
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
