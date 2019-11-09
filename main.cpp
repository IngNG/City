/*!
\file
\brief Главный файл программы

Данный файл содержит функцию `main` и содержит
	основную логику программы
*/
#include "lib/TXLib.h"
#include <string>
#include <vector>

#include "ConfigRead/ConfigApp.h"
#include "WindowObject/ButtonText.h"
#include "WindowObject/Image.h"
#include "WindowObject/DragNDrop.h"
#include "SaveFile/WriteFile.h"
#include "SaveFile/ReadFile.h"
using namespace std;

/*!
Точка входа в приложение

\return Возращает 0 при завершении программы
*/
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

    string category;
	int    speed = 3; ///< скорость  передвижения картинки

	const int COUNT_IMG = 12;
    Image img[COUNT_IMG];
	img[0] = loadImage({720,  30, 80, 80}, "img\\Houses\\Hospital.bmp", "House");
    img[1] = loadImage({720, 140, 80, 80}, "img\\Houses\\LowBlueHome.bmp", "House");
    img[2] = loadImage({720, 250, 80, 80}, "img\\Houses\\LowGreenHome.bmp", "House");
    img[3] = loadImage({720, 350, 80, 100},"img\\Houses\\TallYellowHome.bmp", "House");

    img[4]  = loadImage({720,  30, 40, 40},"img\\Dekor\\fontan.bmp", "Dekor");
    img[5]  = loadImage({740, 140, 30, 30},"img\\Dekor\\snowmen.bmp", "Dekor");
    img[6]  = loadImage({710, 250, 80, 50}, "img\\Dekor\\prud.bmp", "Dekor");
    img[9]  = loadImage({710, 360, 30, 50}, "img\\Dekor\\tree.bmp", "Dekor");
    img[10] = loadImage({710,470, 105, 25}, "img\\Dekor\\doroga1.bmp", "Dekor");
    img[11] = loadImage({710,570, 210, 50}, "img\\Dekor\\doroga2.bmp", "Dekor");

    img[7] = loadImage({770, 68, 30, 20}, "img\\Car\\car.bmp", "Car");
    img[8] = loadImage({770, 136, 30, 60}, "img\\Car\\car2.bmp", "Car");

	DragNDrop dndObject = {NULL, 0, 0};

    int nomer_kart = -1;

	objCity = readSaveFile("save", img, COUNT_IMG);

	while (true) {
		txBegin();
		txSetFillColor(RGB(255, 255, 255));
		txClear();

        Win32::TransparentBlt(txDC(), 150,   0, 800, 600, fon,   0, 0, 123,124, TX_WHITE);

		moveDragNDropImg(dndObject);

		//Limits
		for (int i = 0; i < objCity.size(); i++)
		{
			if (objCity[i].area.x < 150)
			{
				objCity[i].area.x = 150;
			}
			else if (objCity[i].area.x + objCity[i].area.height > 800)
			{
				objCity[i].area.x = 800 - objCity[i].area.height;
			}

			if (objCity[i].area.y < 0)
			{
				objCity[i].area.y = 0;
			}
			else if (objCity[i].area.y + objCity[i].area.height > 600)
			{
				objCity[i].area.y = 600 - objCity[i].area.height;
			}
		}

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
				objCity.push_back(copyImage(img[i]));
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
			objCity[nomer_kart].area.x -= speed;
		}

		if (nomer_kart >= 0 && GetAsyncKeyState (VK_RIGHT))
		{
			objCity[nomer_kart].area.x += speed;
		}

		if (nomer_kart >= 0 && GetAsyncKeyState (VK_UP))
		{
			objCity[nomer_kart].area.y -= speed;
		}


		if (nomer_kart >= 0 && GetAsyncKeyState (VK_OEM_PLUS) &&   speed < 40)
		{
			speed = speed * 1.5;
		}
		else if (GetAsyncKeyState(VK_OEM_MINUS) && speed > 3)
		{
			speed = (speed * 67) / 100;
		}


		if (nomer_kart >= 0 && GetAsyncKeyState (VK_DOWN))
		{
			objCity[nomer_kart].area.y += speed;
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
				SaveGameInFile("save", objCity);
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
