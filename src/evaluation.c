#include "../include/evaluation.h"

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/connect4.h"
#include "../include/minimax.h"

extern char player_comp;
int new_dsq, new_zero, new_one, new_goodOne = 80;
// int old_dsq = -40, old_zero = 4, old_one = 17, old_goodOne = 38;
// int old_dsq = -41, old_zero = 5, old_one = 16, old_goodOne = 39;
int old_dsq = -11, old_zero = 1, old_one = 40, old_goodOne = 80;
// int old_dsq = -42, old_one = 40, old_goodOne = 80;

int v_new[730];
int v_old[730];

int main() {
  // As a start suppose goodOne <= 40.
  // int dsq = -20, zero = 0, one = 30, goodOne = 80;
  preparation(DSQ_VALUE, ZERO_VALUE, ONE_VALUE, GOODONE_VALUE);
  // char board[NROWS][NCOLS];
  // memset(board, '0', NCOLS * NROWS);
  // // int s;
  // for (int i = 35; i >= 30; i--) {
  //   old_one = i;
  //   for (int j = 0; j <= 0; j++) {
  //     old_zero = j;
  //     for (int k = -25; k < -13; k++) {
  //       old_dsq = k;
  //       prepareVector(v_old, old_dsq, old_zero, old_one, old_goodOne);
  //       computerPlay(board);
  //       // if (s != NCOLS / 2) continue;
  //       computer_iteration2(old_dsq, old_zero, old_one, old_goodOne);
  //       printf("(i, j, k)=(%i, %i, %i) finished\n", i, j, k);
  //     }
  //   }
  // }
  // printf("200200 = %i\n", evaluateNumber("200200", -18, 0, 28, 80));
  // printf("200222 = %i\n", evaluateNumber("200222", -18, 0, 28, 80));
  // printf("000222 = %i\n", evaluateNumber("000222", -18, 0, 28, 80));
  // prepareVector(v_new, -15, 0, 26, 80);
  // prepareVector(v_old, -18, 0, 28, 80);
  // printf("PARTIDA 1: ....................\n");
  // player_comp = '1';
  // playGame2(1);  // if you use this, remember to uncomment function in envaluateString();
  // printf("PARTIDA 2: ....................\n");
  // player_comp = '2';
  // playGame2(1);
  // printf("fem el bo ara:\n");
  // computer_iteration2(-18, 0, 28, 80);
  // computer_iteration(-20, 0, 11, 80);
  // computer_iteration(-19, 2, 11, 80);
  return 0;
}

// void computer_iteration2(int old_dsq, int old_zero, int old_one, int old_goodOne) {
//   char p1, p2;
//   int new_one_MIN = 12, new_one_MAX = 30;
//   int new_zero_MIN = 0, new_zero_MAX = 3;
//   int new_dsq_MIN = -20, new_dsq_MAX = -9;
//   int wins_MAX = (new_one_MAX - new_one_MIN) * (new_zero_MAX - new_zero_MIN) * (new_dsq_MAX - new_dsq_MIN);
//   for (int i = new_one_MAX; i > new_one_MIN; i--) {
//     new_one = i;
//     for (int j = new_zero_MIN; j < new_zero_MAX; j++) {
//       new_zero = j;
//       for (new_dsq = new_dsq_MIN; new_dsq < new_dsq_MAX; new_dsq++) {
//         if (wins_MAX < 350) {
//           return;
//         }
//         prepareVector(v_new, new_dsq, new_zero, new_one, new_goodOne);
//         prepareVector(v_old, old_dsq, old_zero, old_one, old_goodOne);
//         // printf("PARTIDA 1: ....................\n");
//         player_comp = '2';
//         p2 = playGame2(1);
//         if (p2 == '2') {
//           wins_MAX--;
//           continue;
//         }
//         player_comp = '1';
//         p1 = playGame2(1);  // if you use this, remember to uncomment function in envaluateString();
//         if (p1 == '2') {
//           wins_MAX--;
//           continue;
//         }
//       }
//     }
//   }
//   printf("old_dsq = %i, old_zero = %i, old_one = %i, old_goodOne = %i\nNumber of wins: %i\n--------------------------\n", old_dsq, old_zero, old_one, old_goodOne, wins_MAX);
//   return;
// }

// int computer_iteration(int old_dsq, int old_zero, int old_one, int old_goodOne) {
//   char p1, p2;
//   int count = 0, countloss = 0, countwin = 0;
//   int new_one_MIN = 12, new_one_MAX = 30;
//   int new_zero_MIN = 0, new_zero_MAX = 3;
//   int new_dsq_MIN = -20, new_dsq_MAX = -9;
//   int wins_MAX = (new_one_MAX - new_one_MIN) * (new_zero_MAX - new_zero_MIN) * (new_dsq_MAX - new_dsq_MIN);
//   for (int i = new_one_MAX; i > new_one_MIN; i--) {
//     new_one = i;
//     // printf("new_one: %i\n", new_one);
//     for (int j = new_zero_MIN; j < new_zero_MAX; j++) {
//       new_zero = j;
//       for (new_dsq = new_dsq_MIN; new_dsq < new_dsq_MAX; new_dsq++) {
//         if (wins_MAX < 600) {
//           return 0;
//         }
//         // if (wins_MAX < 1446) return 0;
//         prepareVector(v_new, new_dsq, new_zero, new_one, new_goodOne);
//         prepareVector(v_old, old_dsq, old_zero, old_one, old_goodOne);
//         // printf("PARTIDA 1: ....................\n");
//         player_comp = '2';
//         p2 = playGame2(1);
//         if (p2 == '2') {
//           wins_MAX--;
//           continue;
//         }
//         player_comp = '1';
//         p1 = playGame2(1);  // if you use this, remember to uncomment function in envaluateString();
//         // printf("PARTIDA 2: ....................\n");
//         if (p1 == '2') {
//           wins_MAX--;
//           continue;
//         }
//         // if ((p1 == '1' && p2 == '2') || (p1 == '2' && p2 == '1')) {
//         //   count++;
//         //   // // printf("%i %i\n", new_one, new_goodOne);
//         //   // printf("Winner with paramters dsq = %i, one = %i, goodOne = %i: %c\n", new_dsq, new_one, new_goodOne, p1);
//         //   // // old_dsq = new_dsq;
//         //   // // old_one = new_one;
//         //   // // old_goodOne = new_goodOne;
//         // } else if (p1 == '2' && p2 == '2') {
//         //   printf("Lost against paramters dsq = %i, zero = %i, one = %i, goodOne = %i.\n", new_dsq, new_zero, new_one, new_goodOne);
//         //   countloss++;
//         // } else {
//         //   // printf("%i %i\n", new_one, new_goodOne);
//         //   // old_dsq = new_dsq;
//         //   // old_one = new_one;
//         //   // old_goodOne = new_goodOne;
//         //   countwin++;
//         // }
//         // printf("--------------------\n-------------------\n--------------------\n");
//       }
//     }
//   }
//   // printf("old_dsq = %i, old_zero = %i, old_one = %i, old_goodOne = %i\nNumber of draws: %i, Losses: %i, Wins: %i, Difference (wins - losses): %i,\n--------------------------\n", old_dsq, old_zero, old_one, old_goodOne, count, countloss, countwin, countwin - countloss);
//   printf("old_dsq = %i, old_zero = %i, old_one = %i, old_goodOne = %i\nNumber of wins: %i\n--------------------------\n", old_dsq, old_zero, old_one, old_goodOne, wins_MAX);

//   // prepareVector(v_new, -27, 1, 20, 80);
//   // prepareVector(v_old, old_dsq, old_zero, old_one, old_goodOne);
//   // printf("PARTIDA 1: ....................\n");
//   // player_comp = '1';
//   // p1 = playGame2(1);  // if you use this, remember to uncomment function in envaluateString();
//   // printf("PARTIDA 2: ....................\n");
//   // player_comp = '2';
//   // p2 = playGame2(1);
//   return 0;
// }

// int isSuperPrivileged(char* str, int i) {  // return 1 if the i-th component is more important than normal
//   int len = strlen(str);
//   if (i + 1 < len && i + 2 < len && str[i + 1] == '1' && str[i + 2] == '1') return 1;
//   return 0;
// }

// int isPrivileged(char* str, int i) {  // return 1 if the i-th component is more important than normal
//   int len = strlen(str);
//   if (i == 2 || i == 4 || (i + 1 < len && str[i + 1] == '1') || (i - 1 >= 0 && str[i - 1] == '1')) return 1;
//   return 0;
// }

// int sumString(char* str, int n, int m, int zero, int one, int goodOne) {
//   // incredibleOne = three consecutive 1s ==> 4-in-a-row (remember we are omiting the centrar character, which is a 1).
//   // goodOne = two consecutive 1s.
//   // one = one isolated 1.
//   // zero = one 0.
//   int incredibleOne = 10000;
//   // int zero = 2, incredibleOne = 10000, goodOne = 20, one = 15;  // incredibleOne is 10000 (i.e. sufficiently large) to avoid having problems when adding values in the heuristicFunction.

//   // Note: We will pass always a string with length greater than or equal to 3.
//   int value = 0;
//   for (int i = n; i <= m; i++) {
//     if (str[i] == '2') {
//       value += 0;
//     } else if (m - i >= 2 && str[i] == '1' && str[i + 1] == '1' && str[i + 2] == '1') {
//       // free(str);
//       // str = NULL;
//       return incredibleOne;  // 4-in-a-row
//     } else if (m - i >= 1 && str[i] == '1' && str[i + 1] == '1') {
//       value += goodOne;
//       i++;
//     } else
//       value += (one - zero) * ((int)str[i] - 48) + zero;  // 48 is the '0' in ASCII.}
//   }
//   // free(str);
//   // str = NULL;
//   return value;
// }

// int search(char* str, int n, int m, char c) {  // returns the 1 if founded, 0 if not.
//   for (int i = n; i <= m; i++) {
//     if (str[i] == c) {
//       return 1;
//     }  // found it
//   }
//   return 0;  // not found
// }

// char* extractString(char* str, int n, int m) {
//   char* newStr = malloc((m - n + 2) * sizeof(char));
//   for (int i = n; i <= m; i++) newStr[i - n] = str[i];
//   // str[m - n + 1] = '\0';  // end of the string
//   return newStr;
// }

int countString(char* str, int n, int m) {
  int count1 = 0;
  for (int i = n; i <= m; i++) {
    if (str[i] == '2') return -1;
    if (str[i] == '1') count1++;
  }
  return count1;
}

int evaluateNumber(char* str, int dsq, int zero, int one, int goodOne) {
  int incredibleOne = INF;
  int aux, count_dsq = 0, count_goodOne = 0, count_one = 0, count_zero = 0;  // least possible value
  for (int i = 0; i < 4; i++) {
    aux = countString(str, i, i + 2);
    if (aux == -1) {
      count_dsq++;
      continue;
    } else if (aux == 3)
      return incredibleOne;
  }
  if (count_dsq == 4) return dsq;
  // From here there is at least one 0.
  //-------------------------------
  aux = -1;
  for (int i = 0; i < 6; i++) {
    if (str[i] == '0') {
      if (i == 0) {
        aux = countString(str, 0, 2);
      } else if (i == 1) {
        aux = countString(str, 0, 2);
        aux = MAX(aux, countString(str, 1, 3));
      } else if (i == 2 || i == 3) {
        aux = countString(str, i - 2, i);
        aux = MAX(aux, countString(str, i - 1, i + 1));
        aux = MAX(aux, countString(str, i, i + 2));
      } else if (i == 4) {
        aux = countString(str, 2, 4);
        aux = MAX(aux, countString(str, 3, 5));
      } else if (i == 5) {
        aux = countString(str, 3, 5);
      }
    } else
      continue;
    if (aux == 0) {
      count_zero++;
    } else if (aux == 1) {
      count_one++;
    } else if (aux == 2) {
      count_goodOne++;
    }
  }
  if (count_dsq == 4) return dsq;
  if (count_goodOne > 0) {
    return goodOne + (count_goodOne - 1) * goodOne;  // 1 <= count_goodOne <= 2
  } else if (count_one > 0) {
    return one + (count_one - 2) * one;  // 2 <= count_one <= 4
  } else
    return zero + (count_zero - 3) * zero;  // 3 <= count_zero <= 6
}

void printArray(int v[], int n) {
  for (int i = 0; i < n; i++)
    printf("%i - %d\n", i, v[i]);
}

char* base10to3(int i) {  // i<243
  int j = 5, x;
  char* v = malloc(7 * sizeof(char));
  memset(v, '0', 6);
  if (i == 0) return v;
  while (i != 1 && i != 2) {
    x = i % 3;
    v[j] = x + 48;  // 48 = '0' in ASCII
    j--;
    i = (i - x) / 3;
  }
  if (i == 1)
    v[j] = '1';
  else
    v[j] = '2';
  return v;
}

void prepareVector(int v[], int dsq, int zero, int one, int goodOne) {
  char* s;
  for (int i = 0; i < 729; i++) {
    s = base10to3(i);
    v[i] = evaluateNumber(s, dsq, zero, one, goodOne);
  }
  free(s);
  s = NULL;
}

void preparation(int dsq, int zero, int one, int goodOne) {
  char* s;
  // for (int i = 0; i < 729; i++) {
  //   s = exchangeOnesAndTwos(base10to3(i));
  //   printf("%s %d\n", s, evaluateNumber(s, dsq, zero, one, goodOne));
  // }
  // char s[6] = "011000";
  // printf("%s %d\n", s, evaluateNumber(s, dsq, zero, one, goodOne));
  printf("Normal one:\n");
  for (int i = 0; i < 729; i++) {
    s = base10to3(i);
    printf("%d, ", evaluateNumber(s, dsq, zero, one, goodOne));
  }
  printf("\n\nExchanged one:\n");
  for (int i = 0; i < 729; i++) {
    s = exchangeOnesAndTwos(base10to3(i));
    printf("%d, ", evaluateNumber(s, dsq, zero, one, goodOne));
  }
  puts(" ");
}
