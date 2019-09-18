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

void darwRoundedRectangle(int x, int y, int x2, int y2, int r) {
    txSetColour(RGB(0, 0, 0));
    txSetFillColour(RGB(0, 0, 0));

    Win32::RoundRect(txDC(), x, y, x2, y2, r, r);
}

void drawMenu() {
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

    for (int i = 0; i < COUNT_ITEM_MENU; i++) {

    }
}

int main() {
	txCreateWindow(WIGHT_WINDOW, HEIGHT_WINDOW);
	txSetFillColor(RGB(255, 255, 255));
	txClear();

	drawMenu();

	return 0;
}
