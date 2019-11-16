/*!
\file
\brief Главный файл программы

Данный файл содержит функцию `main` и содержит
	основную логику программы
*/
#include "lib/TXLib.h"
#include <string>
#include <vector>

#include "lib/File/ConfigApp.h"
#include "lib/WindowObject/ButtonText.h"
#include "lib/WindowObject/Image.h"
#include "lib/WindowObject/DragNDrop.h"
#include "lib/File/File.h"
#include "lib/utils/SelectFile.h"
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
	Image strelkiLeft  = loadImage({10,  400, 60, 40}, "img\\StrelkiLeft.bmp" );
	Image strelkiRight = loadImage({80,  400, 60, 40}, "img\\StrelkiRight.bmp");

	const int COUNT_BUTTON = 6;
    ButtonText buttons[COUNT_BUTTON];
	initButtonMenu(
		buttons, COUNT_BUTTON,
		20, 10,
		100, 40, 10,
		RGB(255, 0, 0), RGB(0, 0, 0), RGB(255, 0, 0)
	);

	buttons[0].text = "Дома";
	buttons[0].category = "Houses";
	buttons[1].text = "Декор";
	buttons[1].category = "Dekor";
	buttons[2].text = "Машина";
	buttons[2].category = "Car";
	buttons[3].text = "Сохранить";
	buttons[4].text = "Открыть";
	buttons[5].text = "Выход";

	vector<Image> objCity;

    string category;
	int speed = 3; ///< скорость  передвижения картинки
	int CAM_X = 0;
	const int COUNT_IMG = 12;
    Image img[COUNT_IMG];
	img[0] = loadImage({720,  30, 80, 80}, "img\\Houses\\Hospital.bmp");
    img[1] = loadImage({720, 140, 80, 80}, "img\\Houses\\LowBlueHome.bmp");
    img[2] = loadImage({720, 250, 80, 80}, "img\\Houses\\LowGreenHome.bmp");
    img[3] = loadImage({720, 350, 80, 100},"img\\Houses\\TallYellowHome.bmp");

    img[4]  = loadImage({720,  30, 40, 40},"img\\Dekor\\fontan.bmp");
    img[5]  = loadImage({740, 140, 30, 30},"img\\Dekor\\snowmen.bmp");
    img[6]  = loadImage({710, 250, 80, 50}, "img\\Dekor\\prud.bmp");
    img[7]  = loadImage({710, 360, 30, 50}, "img\\Dekor\\tree.bmp");
    img[8] = loadImage({710,470, 105, 25}, "img\\Dekor\\doroga1.bmp");
    img[9] = loadImage({710,570, 210, 50}, "img\\Dekor\\doroga2.bmp");

    img[10] = loadImage({770, 68, 30, 20}, "img\\Car\\car.bmp");
    img[11] = loadImage({770, 136, 30, 60}, "img\\Car\\car2.bmp");

	DragNDrop dndObject = {NULL, 0, 0};
    int nomer_kart = -1;
	string openNameFile = "";

	while (true) {
		txBegin();
		txSetFillColor(RGB(255, 255, 255));
		txClear();

		Win32::TransparentBlt(txDC(), CAM_X + 150,   0, 2500, 600, fon, 0, 0, 2500,600, TX_WHITE);
		Win32::TransparentBlt(txDC(), CAM_X - 2500 + 150,   0, 2500, 600, fon, 0, 0, 2500,600, TX_WHITE);

		drawImage(strelkiRight, 0);
		updateStatusImage(strelkiRight);
		drawImage(strelkiLeft, 0);
		updateStatusImage(strelkiLeft);
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
            drawImage(objCity[i], CAM_X);
			updateStatusImage(objCity[i], CAM_X);
        }

        //Drawing variants
        for(int i = 0; i < COUNT_IMG; i++)
        {
			updateStatusImage(img[i]);
            if (img[i].category == category)
            {
                drawImage(img[i], 0);
            }
        }

		//CAM move
		if (strelkiRight.clicked() && CAM_X < 2500 )
		{
            CAM_X -= 10;
        }
		else if (strelkiLeft.clicked())
        {
            CAM_X += 10;
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

		if (buttons[5].click() || GetAsyncKeyState(VK_ESCAPE))
		{
			int click_button = txMessageBox("Выйти?", "Подтверждение", MB_OKCANCEL);
			if (click_button == 1) {
				break;
			}
		}

		// Сохранение
		if (buttons[3].click()) {
			if (openNameFile == "") {
				openNameFile = selectFile(txWindow());
			}
			SaveGameInFile(openNameFile, objCity);
			txMessageBox("Сохранение завершено", "Завершено", MB_OK);
		}
		// Открытие
		if (buttons[4].click()) {
			string newNameFile = selectFile(txWindow());
			if (newNameFile != "") {
				openNameFile = newNameFile;
				objCity = readSaveFile(openNameFile, img, COUNT_IMG);
				txMessageBox("Чтение завершено", "Завершено", MB_OK);
			}
		}

		txEnd();
		txSleep(10);
	}
	txDeleteDC(strelkiRight.img);
	txDeleteDC(strelkiLeft.img);
	txDeleteDC(fon);
	txDeleteDC(skver);

	for (int i = 0; i < COUNT_IMG; i++)
	{
		txDeleteDC(img[i].img);
	}

	return 0;
}
