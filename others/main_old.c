#include "../include/connect4.h"
#include "../include/evaluation.h"
#include "../include/extra.h"
#include "../include/minimax.h"
#include "../include/setup.h"

int main() {
  // char **board = {
  //     {'0', '0', '0', '0', '0', '0'},
  //     {'0', '0', '0', '0', '0', '0'},
  //     {'0', '2', '0', '0', '0', '0'},
  //     {'0', '1', '2', '2', '0', '0'},
  //     {'0', '2', '1', '2', '0', '0'},
  //     {'2', '1', '1', '1', '2', '0'}};
  // // memset(board, '0', NCOLS * NROWS);
  // printBoard(board);
  // printf("%i,%i,%i,%i\n", consecutiveEast(board, 3, 2), consecutiveSouth(board, 3, 2), consecutiveSouthWest(board, 3, 2), consecutiveSouthEast(board, 3, 2));
  // sleep(1);  // 1 is in seconds
  // clean();
  // board[1][3] = '4';
  // printBoard(board);
  // drawBoard();
  // initscr(); /* Start curses mode 		*/
  // if (has_colors() == false) {
  //   endwin();
  //   printf("Your terminal does not support color\n");
  //   exit(1);
  // }
  // start_color(); /* Start color 			*/
  // init_pair(1, COLOR_RED, COLOR_BLACK);
  // init_pair(2, COLOR_YELLOW, COLOR_BLACK);
  // init_pair(3, COLOR_BLUE, COLOR_BLACK);

  // match == 0 --> player vs computer
  // match == 1 --> computer vs computer
  char i = playGame2();  // computer vs computer
                         // char i = playGame2(0);  // player vs computer
                         // printf("\n\nplayGame: %i\n\n", i);
  if (i == '0')
    printf("DRAW!\n");
  else if (i == '1')
    printf("SORRY! YOU'VE LOST!\n");
  else
    printf("CONGRATULATIONS! YOU'VE WON!\n");
  uploadFile(i);
  return 0;
}
