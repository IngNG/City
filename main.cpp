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

	txCreateWindow(atoi(getValueSetting(config, "wight").c_str()),
                   atoi(getValueSetting(config, "height").c_str()));
	txDisableAutoPause();

	HDC fon   = txLoadImage("img\\fon.bmp");
	HDC skver = txLoadImage("img\\skver.bmp");

	const int COUNT_BUTTON = 7;
    ButtonText buttons[COUNT_BUTTON];
	buttons[0] = {{20, 10, 100, 40}, "Начать", RGB(255, 0, 0), RGB(0, 0, 0), RGB(255, 0, 0), true};
    buttons[1] = {{20, 60, 100, 40}, "Дома", RGB(255, 0, 0), RGB(0, 0, 0), RGB(255, 0, 0), true};
    buttons[2] = {{20, 110, 100, 40}, "Декор", RGB(255, 0, 0), RGB(0, 0, 0), RGB(255, 0, 0), true};
    buttons[3] = {{20, 160, 100, 40}, "Машина", RGB(255, 0, 0), RGB(0, 0, 0), RGB(255, 0, 0), true};
    buttons[4] = {{20, 210, 100, 40}, "Госпиталь", RGB(255, 0, 0), RGB(0, 0, 0), RGB(255, 0, 0), true};
    buttons[5] = {{20, 260, 100, 40}, "Снеговик", RGB(255, 0, 0), RGB(0, 0, 0), RGB(255, 0, 0), true};
    buttons[6] = {{20, 310, 100, 40}, "Единорог", RGB(255, 0, 0), RGB(0, 0, 0), RGB(255, 0, 0), true};

	const int COUNT_CAR = 4;
    Image car[COUNT_CAR];
    car[0] = {{300, 10, 100, 90}, 79, 58, txLoadImage("img\\Houses\\Hospital.bmp"), false};
    car[1] = {{300, 120, 100, 70}, 66, 58, txLoadImage("img\\Houses\\LowBlueHome.bmp"), false};
    car[2] = {{300, 210, 100, 90}, 66, 58, txLoadImage("img\\Houses\\LowGreenHome.bmp"), false};
    car[3] = {{300, 320, 100, 130}, 66, 99, txLoadImage("img\\Houses\\TallYellowHome.bmp"), false};

    EventArea event;
    string category;

	const int COUNT_IMG = 8;
    Image img[COUNT_IMG];
    img[0] = {{720,  30, 80, 80}, 79, 58, txLoadImage("img\\Houses\\Hospital.bmp"), true, "House"};
    img[1] = {{720, 140, 80, 80}, 66, 58, txLoadImage("img\\Houses\\LowBlueHome.bmp"), true, "House"};
    img[2] = {{720, 250, 80, 80}, 66, 58, txLoadImage("img\\Houses\\LowGreenHome.bmp"), true, "House"};
    img[3] = {{720, 350, 80, 100}, 66, 99, txLoadImage("img\\Houses\\TallYellowHome.bmp"), true, "House"};

    img[4] = {{720,  30, 80, 80}, 36, 26, txLoadImage("img\\Dekor\\fontan.bmp"), true, "Dekor"};
    img[5] = {{770, 140, 80, 80}, 11, 13, txLoadImage("img\\Dekor\\snowmen.bmp"), true, "Dekor"};

    img[6] = {{770, 250, 30, 20}, 17, 9, txLoadImage("img\\Car\\car.bmp"), true, "Car"};
    img[7] = {{770, 350, 30, 20}, 16, 10, txLoadImage("img\\Car\\car2.bmp"), true, "Car"};
	
	DragNDrop dndImage = {NULL, 0, 0};

	while (!GetAsyncKeyState(VK_ESCAPE)) {
		txBegin();
		txSetFillColor(RGB(255, 255, 255));
		txClear();

        Win32::TransparentBlt(txDC(), 150,   0, 700, 700, fon,   0, 0, 123,124, TX_WHITE);
        Win32::TransparentBlt(txDC(), 300, 200, 200, 160, skver, 0, 0, 175, 110, TX_WHITE);

        //Buttons
        for (int n_button = 0; n_button < 6; n_button++)
        {
            drawButton(buttons[n_button]);
        }

        //Drawing pictures
        for (int i = 0; i < COUNT_CAR; i++) {
            drawImage(car[i]);
        }

        //Drawing variants
        for(int n = 0;n < COUNT_IMG;n++)
        {
            if (img[n].category == category)
            {
                drawImage(img[n]);
            }
        }


        //Choosing variants
        event = getEventArea(img[0].area);
        if (event.mouseButtonUpLeft && img[0].category == category)
        {
            car[0].visible = !car[0].visible;
            txSleep(200);
        }

        event = getEventArea(img[1].area);
        if (event.mouseButtonUpLeft && img[1].category == category)
        {
            car[1].visible = !car[1].visible;
            txSleep(200);
        }

        event = getEventArea(img[2].area);
        if (event.mouseButtonUpLeft && img[2].category == category)
        {
            car[2].visible = !car[2].visible;
            txSleep(200);
        }

        event = getEventArea(img[3].area);
        if (event.mouseButtonUpLeft && img[3].category == category)
        {
            car[3].visible = !car[3].visible;
            txSleep(200);
        }


        //Category choosing
        event = getEventArea(buttons[1].area);
        if (event.mouseButtonUpLeft)
        {
            category = "House";
        }

        event = getEventArea(buttons[2].area);
        if (event.mouseButtonUpLeft)
        {
            category = "Dekor";
        }

        event = getEventArea(buttons[3].area);
        if (event.mouseButtonUpLeft)
        {
            category = "Car";
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
