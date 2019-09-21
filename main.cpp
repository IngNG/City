#include "lib/TXLib.h"

#define WIGHT_WINDOW 800
#define HEIGHT_WINDOW 600

#define WIGHT_ITEM_MENU 100
#define HEIGHT_ITEM_MENU 50
#define HEIGHT_SPASE 10
#define COUNT_ITEM_MENU 3
const char TEXT_MENU[COUNT_ITEM_MENU][255] = {
    "Hello World", "Hello", "World"
};

void darwRoundedRectangle(int x, int y, int x2, int y2, int r)
{
    txSetColour(RGB(0, 0, 0));
    txSetFillColour(RGB(0, 0, 0));

    Win32::RoundRect(txDC(), x, y, x2, y2, r, r);
}

void drawMenu()
{
    txSelectFont("Arial", 20);
    int x_center_window = WIGHT_WINDOW / 2;
    int y_center_window = HEIGHT_WINDOW / 2;

    txSetColour(RGB(0, 0, 0));
    txSetFillColour(RGB(0, 0, 0));

    int x_item = x_center_window - (WIGHT_ITEM_MENU / 2);
    //int y_item = y_center_window - (HEIGHT_ITEM_MENU * COUNT_ITEM_MENU + HEIGHT_SPASE * (COUNT_ITEM_MENU - 1)) / 2;
    int y_item = 100;

    int x2_item = x_item + WIGHT_ITEM_MENU;
    //int y2_item = y_center_window + HEIGHT_ITEM_MENU;
    int y2_item = y_item + HEIGHT_ITEM_MENU;

    for (int i = 0; i < COUNT_ITEM_MENU; i++)
    {

    }
}

bool isClickButton(int x, int y)
 {

    if (txMouseX() > x and
          txMouseX() < x + 200 and
          txMouseY() > y and
          txMouseY() < y + 100 and
          txMouseButtons() &1)
    {
        return true;
    }

    return false;
 }

 bool isHoverButton(int x, int y)
 {

    if (txMouseX() > x and
          txMouseX() < x + 200 and
          txMouseY() > y and
          txMouseY() < y + 100
        )
    {
        return true;
    }

    return false;
 }

int main() {
	txCreateWindow(WIGHT_WINDOW, HEIGHT_WINDOW);

	while (true)
    {
        txSetFillColor(RGB(255, 255, 255));
        txClear();
	      drawMenu();

        txSetFillColour(TX_RED);
        txRectangle (0,0,200,100);
        txDrawText  (0,0,200,100, "SDF");

        txSetFillColour(TX_BLACK);
        txSetColour(TX_PINK);
        txRectangle (400,0,600,100);
        txDrawText  (400,0,600,100, "fghfg");

        txSetFillColour(TX_BLUE);
        txRectangle (0,200,200,300);
        txDrawText  (0,200,200,300, "SOF");


        if (isClickButton(0,0))
        {
            txMessageBox("sdf","sdf");
        }

        if (isClickButton(0,200))
        {
            txMessageBox("sof","sof");
        }

        if (isClickButton(400,0))
        {
            txMessageBox("sdg","sdfs");
        }

        if (isClickButton(400,200))
        {
            txSetColor(TX_BLACK);
            txTextOut(500, 300,"fghfgh");
        }

        txSleep(10);
    }

	return 0;
}
