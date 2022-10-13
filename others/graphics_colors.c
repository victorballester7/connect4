#include "graphics_colors.h"

//#include <conio.h> //only for windows
#include <graphics.h>  //needed libgraph installed
#include <stdio.h>

#include "connect4.h"

void drawBoard() {
  int gr = DETECT, gm;
  int row, col, x = 50, y = 50, flag = 0;
  initgraph(&gr, &gm, "");
  printf("\t*********** CHESS BOARD **************\n");
  for (row = 0; row < 8; row++) {
    for (col = 1; col <= 8; col++) {
      if (flag == 0) {
        setcolor(YELLOW);
        // setfillstyle(SOLID_LINE, BLACK);
        rectangle(x, y, x + 50, y + 50);
        floodfill(x + 1, y + 1, YELLOW);
        flag = 1;
      } else {
        setcolor(YELLOW);
        // setfillstyle(SOLID_LINE, WHITE);
        rectangle(x, y, x + 50, y + 50);
        floodfill(x + 1, y + 1, YELLOW);
        flag = 0;
      }
      x = x + 50;
    }
    if (flag == 0)
      flag = 1;
    else
      flag = 0;
    // delay(100);
    x = 50;
    y = 50 + y;
  }
  getch();
  closegraph();
}
