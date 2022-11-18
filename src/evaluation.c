#include "../include/evaluation.h"

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/connect4.h"
#include "../include/minimax.h"

extern char player_comp;
int new_dsq, new_one, new_goodOne = 39;
// int old_dsq = -40, old_zero = 4, old_one = 17, old_goodOne = 38;
// int old_dsq = -41, old_zero = 5, old_one = 16, old_goodOne = 39;
int old_dsq = -28, old_one = 8, old_goodOne = 39;
int v_new[730];
int v_old[730];

int main() {
  // As a start suppose goodOne <= 40.
  // int dsq = -10, zero = 2, one = 15, goodOne = 20;
  int dsq = -10, zero = 2, one = 16, goodOne = 80;
  preparation(dsq, one, goodOne);
  // char p1, p2;
  // for (new_goodOne = 39; new_goodOne > 15; new_goodOne--) {
  //   // printf("\nnew_goodOne: %i\n", new_goodOne);
  //   for (new_one = 10; new_one > 5; new_one--) {
  //     printf("new_one: %i\n", new_one);
  //     for (new_dsq = -42; new_dsq < 0; new_dsq++) {
  //       prepareVector(v_new, new_dsq, new_one, new_goodOne);
  //       prepareVector(v_old, old_dsq, old_one, old_goodOne);
  //       player_comp = '1';
  //       p1 = playGame(1);
  //       player_comp = '2';
  //       p2 = playGame(1);
  //       if (p1 == '2' && p2 == '2') {
  //         // printf("%i %i\n", new_one, new_goodOne);
  //         printf("Winner with paramters dsq = %i, one = %i, goodOne = %i: %c\n", new_dsq, new_one, new_goodOne, p1);
  //         old_dsq = new_dsq;
  //         old_one = new_one;
  //         old_goodOne = new_goodOne;
  //       }
  //     }
  //   }
  // }
  // return 0;
}

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

int evaluateNumber(char* str, int dsq, int one, int goodOne) {
  int incredibleOne = 10000;
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
    return goodOne + (count_goodOne - 1) * goodOne / 8;  // count_goodOne >=1
  } else if (count_one > 0) {
    return one + (count_one - 2) * one / 8;  // count_one >=2
  } else
    return count_zero - 2;  // count_zero >=2
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

void prepareVector(int v[], int dsq, int one, int goodOne) {
  char* s;
  for (int i = 0; i < 729; i++) {
    s = base10to3(i);
    v[i] = evaluateNumber(s, dsq, one, goodOne);
  }
  free(s);
  s = NULL;
}

void preparation(int dsq, int one, int goodOne) {
  char* s;
  // for (int i = 0; i < 729; i++) {
  //   s = exchangeOnesAndTwos(base10to3(i));
  //   printf("%s %d\n", s, evaluateNumber(s, dsq, one, goodOne));
  // }
  // char s[6] = "011000";
  // printf("%s %d\n", s, evaluateNumber(s, dsq, zero, one, goodOne));
  for (int i = 0; i < 729; i++) {
    s = exchangeOnesAndTwos(base10to3(i));
    printf("%d, ", evaluateNumber(s, dsq, one, goodOne));
  }
  puts(" ");
}
