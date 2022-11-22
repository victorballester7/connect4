
#define _GNU_SOURCE
#include "../include/connect4.h"
// #include "../include/evaluation.h"
#include "../include/minimax.h"
#include "../include/setup.h"

extern int colorPlayer, colorComputer;

int supportsColors();
int main() {
  setlocale(LC_ALL, "");
  initscr();  // start ncurses mode.
  clear();    // clear screen.
  noecho();   // Don't echo() while doing getch().
  cbreak();   // Line buffering disabled. pass on everything.
  char filenameLogo[30] = "resources/logo1.txt";

  // position of the top left corner of the window
  int startRow = (30 - HEIGHT) / 2;
  int startCol = (80 - WIDTH) / 2;

  if (!supportsColors()) return 0;

  mvprintw(0, 0, "Use arrow keys to go up and down. Press enter to select a choice.");  // printf in the abstract window
  refresh();                                                                            // Print it on to the real screen
  printLogo(filenameLogo, startCol + WIDTH / 2);
  WINDOW* menuWin = createWindow(HEIGHT, WIDTH, startRow, startCol);
  int choice;
  while ((choice = movementMenu(menuWin, printMenu)) != 4) {  // Exit
    switch (choice) {
      case 1:                                                                                 // Play the game
        mvprintw(1, 0, "Use arrow keys to go up and down. Press enter to select a choice.");  // printf in the abstract window
        break;
      case 2:  // Statistics
        movementMenu(menuWin, printStats);
        break;
      case 3:  // Settings
        colorPlayer = movementMenu(menuWin, printSettingsP1);
        colorComputer = movementMenu(menuWin, printSettingsP2);
        break;
      default:  // Exit
        break;
    }
  }
  clrtoeol();  // erase the current line to the right of the cursor, inclusive, to the end of the current line.
  refresh();
  // sleep(5);
  endwin();
  return 0;
}
