#include "lib/TXLib.h"
#include <string>
#include <vector>

#include "ConfigRead/ConfigApp.h"
#include "WindowObject/ButtonText.h"
#include "WindowObject/Image.h"
#include "WindowObject/DragNDrop.h"
using namespace std;

int main()
{
	ConfigApp config = readConfigFile("config.txt");

	txCreateWindow(
		atoi(getValueSetting(config, "wight").c_str()),
        atoi(getValueSetting(config, "height").c_str())
	);
	txDisableAutoPause();

	HDC fon   = txLoadImage("img\\fon.bmp");
	HDC skver = txLoadImage("img\\skver.bmp");

	const int COUNT_BUTTON = 5;
    ButtonText buttons[COUNT_BUTTON];
	buttons[0] = {{20, 10,  100, 40}, "Начать",    RGB(255, 0, 0), RGB(0, 0, 0), RGB(255, 0, 0), true, ""};
    buttons[1] = {{20, 60,  100, 40}, "Дома",      RGB(255, 0, 0), RGB(0, 0, 0), RGB(255, 0, 0), true, "House"};
    buttons[2] = {{20, 110, 100, 40}, "Декор",     RGB(255, 0, 0), RGB(0, 0, 0), RGB(255, 0, 0), true, "Dekor"};
    buttons[3] = {{20, 160, 100, 40}, "Машина",    RGB(255, 0, 0), RGB(0, 0, 0), RGB(255, 0, 0), true, "Car"};
    buttons[4] = {{20, 210, 100, 40}, "Выход",     RGB(255, 0, 0), RGB(0, 0, 0), RGB(255, 0, 0), true, ""};

	vector<Image> objCity;

    EventArea event;
    string category;

	const int COUNT_IMG = 12;
    Image img[COUNT_IMG];
    img[0] = {{720,  30, 80, 80},  79, 58, txLoadImage("img\\Houses\\Hospital.bmp"),       true, "House"};
    img[1] = {{720, 140, 80, 80},  66, 58, txLoadImage("img\\Houses\\LowBlueHome.bmp"),    true, "House"};
    img[2] = {{720, 250, 80, 80},  66, 58, txLoadImage("img\\Houses\\LowGreenHome.bmp"),   true, "House"};
    img[3] = {{720, 350, 80, 100}, 66, 99, txLoadImage("img\\Houses\\TallYellowHome.bmp"), true, "House"};

    img[4]  = {{720,  30, 40, 40}, 36, 26, txLoadImage("img\\Dekor\\fontan.bmp"),  true, "Dekor"};
    img[5]  = {{740, 140, 30, 30}, 11, 13, txLoadImage("img\\Dekor\\snowmen.bmp"), true, "Dekor"};
    img[6]  = {{710, 250, 80, 50}, 71, 34, txLoadImage("img\\Dekor\\prud.bmp"),    true, "Dekor"};
    img[9]  = {{710, 360, 30, 50}, 10, 23, txLoadImage("img\\Dekor\\tree.bmp"),    true, "Dekor"};
    img[10] = {{710,470, 105, 25}, 17, 5,  txLoadImage("img\\Dekor\\doroga1.bmp"), true, "Dekor"};
    img[11] = {{710,570, 210, 50}, 34, 15, txLoadImage("img\\Dekor\\doroga2.bmp"), true, "Dekor"};

    img[7] = {{770, 250, 30, 20}, 17, 9,  txLoadImage("img\\Car\\car.bmp"),  true, "Car"};
    img[8] = {{770, 350, 30, 20}, 16, 10, txLoadImage("img\\Car\\car2.bmp"), true, "Car"};

	DragNDrop dndObject = {NULL, 0, 0};

    int nomer_kart = -1;

	while (true) {
		txBegin();
		txSetFillColor(RGB(255, 255, 255));
		txClear();

        Win32::TransparentBlt(txDC(), 150,   0, 700, 700, fon,   0, 0, 123,124, TX_WHITE);

		moveDragNDropImg(dndObject);

        //Buttons
        for (int i = 0; i < COUNT_BUTTON; i++)
        {
            drawButton(buttons[i]);
			updateStatusButton(buttons[i]);
        }

        //Drawing pictures
        for (int i = 0; i < objCity.size(); i++)
		{
            drawImage(objCity[i]);
			updateStatusImage(objCity[i]);
        }

        //Drawing variants
        for(int i = 0; i < COUNT_IMG; i++)
        {
			updateStatusImage(img[i]);
            if (img[i].category == category)
            {
                drawImage(img[i]);
            }
        }

        //Choosing variants
		for (int i = 0; i < COUNT_IMG; i++) {
			if (img[i].downClick() && img[i].category == category)
			{
				objCity.push_back({
					img[i].area,
					img[i].widht,
					img[i].height,
					img[i].img,
					true,
					""
				});
				dndObject = setDragNDrop(&objCity.back());
			}
		}

		for (int i = 0; i < objCity.size(); i++)
		{
			if (objCity[i].click())
			{
				nomer_kart = i;
			}
		}

		if (nomer_kart >= 0 && GetAsyncKeyState (VK_LEFT))
		{
			objCity[nomer_kart].area.x -= 3;
		}

		if (nomer_kart >= 0 && GetAsyncKeyState (VK_RIGHT))
		{
			objCity[nomer_kart].area.x += 3;
		}

		if (nomer_kart >= 0 && GetAsyncKeyState (VK_UP))
		{
			objCity[nomer_kart].area.y -= 3;
		}

		if (nomer_kart >= 0 && GetAsyncKeyState (VK_DOWN))
		{
			objCity[nomer_kart].area.y += 3;
		}

		if (nomer_kart >=0 && GetAsyncKeyState (VK_DELETE))
		{
			objCity[nomer_kart] = objCity[objCity.size() - 1] ;
			objCity.pop_back();
			nomer_kart = -1;
		}

        //Category choosing
        for(int i = 0; i < COUNT_BUTTON - 1; i++)
        {
            if (buttons[i].click())
            {
                category = buttons[i].category;
            }
        }

		if (buttons[4].click() || GetAsyncKeyState(VK_ESCAPE))
		{
			int click_button = txMessageBox("Выйти?", "Подтверждение", MB_OKCANCEL);
			if (click_button == 1) {
				break;
			}
		}

		txEnd();
		txSleep(10);
	}

	txDeleteDC(fon);
	txDeleteDC(skver);

	for (int i = 0; i < COUNT_IMG; i++)
	{
		txDeleteDC(img[i].img);
	}

	return 0;
}
