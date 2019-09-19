#include "lib/TXLib.h"

    bool knopka(int x, int y)
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

     bool focus(int x, int y)
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

int main()
{
	txCreateWindow(800, 600);

	while (true)
    {
        txSetFillColor(RGB(255, 255, 255));
        txClear();

        txSetFillColour(TX_RED);
        txRectangle (0,0,200,100);
        txDrawText  (0,0,200,100, "SDF");

        txSetFillColour(TX_BLACK);
        txSetColour(TX_PINK);
        txRectangle (400,0,600,100);
        txDrawText  (400,0,600,100, "Единорог");

        txSetFillColour(TX_BLUE);
        txRectangle (0,200,200,300);
        txDrawText  (0,200,200,300, "SOF");


       if (knopka(0,0))
        {
            txMessageBox("sdf","sdf");
        }

       if (knopka(0,200))
        {
            txMessageBox("sof","sof");
        }

        if (knopka(400,0))
        {
            txMessageBox("Единороги рулят","Единороги рулят");
        }

       if (focus(400,200))
        {
            txSetColor(TX_BLACK);
            txTextOut(500, 300,"Единорог");
        }

        txSleep(10);
    }

	return 0;
}
