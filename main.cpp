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

    HDC pic = txLoadImage("img\\Houses\\Hospital.bmp");
    HDC pik = txLoadImage("img\\Houses\\LowBlueHome.bmp");
    HDC pil = txLoadImage("img\\Houses\\LowGreenHome.bmp");
    HDC pie = txLoadImage("img\\Houses\\TallYellowHome.bmp");
    HDC pit = txLoadImage("img\\Houses\\LowYellowHome.bmp");
    HDC pin = txLoadImage("img\\Houses\\TallBlueHome.bmp");
    HDC pim = txLoadImage("img\\Houses\\TallGreenHome.bmp");
    HDC pir = txLoadImage("img\\fontan.bmp");
    HDC snowmen = txLoadImage("img\\snowmen.bmp");

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


    Image kar[10];
    kar[0] = {{300, 10, 400, 100}, 79,58,txLoadImage("img\\Houses\\Hospital.bmp")};
    kar[1] = {{300, 120, 400, 190}, 66,58,pik};
    kar[2] = {{300, 210, 400, 300}, 66,58,pil};
    kar[3] = {{300, 320, 400, 450}, 66,99,pie};

    bool  visible = false;
    bool  visible2 = false;
    bool  visible3 = false;
    bool  visible4 = false;
    EventArea event;

    Image img[10];

    img[0] = {{720,  30, 800, 110}, 79,58,pic};
    img[1] = {{720, 140, 800, 220}, 66,58,pik};
    img[2] = {{720, 250, 800, 330}, 66,58,pil};
    img[3] = {{720, 350, 800, 450}, 66,99,pie};
    img[4] = {{720,  30, 800, 110}, 36,26,txLoadImage ("img\\fontan.bmp")};
    img[5] = {{720, 140, 800, 220}, 11,13,snowmen};


	while (!GetAsyncKeyState(VK_ESCAPE)) {
		txBegin();

		txSetFillColor(RGB(255, 255, 255));
		txClear();

        Win32::TransparentBlt (txDC(),150,0,700,700,fon,0,0, 123,124, TX_WHITE);
        Win32::TransparentBlt (txDC(),300,200,200,160,skver,0,0, 175,110, TX_WHITE);

        for (int n_button = 0; n_button < 6; n_button++)
        {
            drawButton(buttons[n_button]);
        }


        event = getEventArea(img[0].area);
        if (event.mouseButtonUpLeft)
        {
            visible = !visible;
            txSleep(200);
        }

        if (visible)
        {
            drawImage(kar[0]);
        }


        event = getEventArea(img[1].area);
        if (event.mouseButtonUpLeft)
        {
            visible2 = !visible2;
            txSleep(200);
        }


        if (visible2)
        {
            drawImage(kar[1]);
        }

        event = getEventArea(img[2].area);
        if (event.mouseButtonUpLeft)
        {
            visible3 = !visible3;
            txSleep(200);
        }


        if (visible3)
        {
            drawImage(kar[2]);
        }

         event = getEventArea(img[3].area);
        if (event.mouseButtonUpLeft)
        {
            visible4 = !visible4;
            txSleep(200);
        }


        if (visible4)
        {
            drawImage(kar[3]);
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

        for(int n_img = 0;n_img < 4;n_img++)
        {
            //drawImage(img[n_img]);
        }

        if(visible11)
        {
            drawImage(img[0]);
            drawImage(img[1]);
            drawImage(img[2]);
            drawImage(img[3]);
        }
        if(visible12)
        {
            drawImage(img[4]);
        }
        if(visible13)
        {
            drawImage(img[5]);
        }

		txSleep(10);
	}

    txDeleteDC(pic);
    txDeleteDC(pik);
    txDeleteDC(pil);
    txDeleteDC(pie);
    txDeleteDC(fon);
    txDeleteDC(pir);
    txDeleteDC(skver);

	return 0;
}
