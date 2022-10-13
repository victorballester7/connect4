#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double evaluateNumber();
char* base10to3(int i);
void preparation();
void printArray(int v[], int n);
int isSuperPrivileged(char* str, int i);
int isPrivileged(char* str, int i);
double sumString(char* str, int n, int m);
int search(char* str, int n, int m, char c);
double evaluateNumber(char* str);
// char* extractString(char* str, int n, int m);

int main() {
  preparation();
  //  int* v = evaluateNumber();
  //  printArray(v, 729);
  return 0;
}

int isSuperPrivileged(char* str, int i) {  // return 1 if the i-th component is more important than normal
  int len = strlen(str);
  if (i + 1 < len && i + 2 < len && str[i + 1] == '1' && str[i + 2] == '1') return 1;
  return 0;
}

int isPrivileged(char* str, int i) {  // return 1 if the i-th component is more important than normal
  int len = strlen(str);
  if (i == 2 || i == 4 || (i + 1 < len && str[i + 1] == '1') || (i - 1 >= 0 && str[i - 1] == '1')) return 1;
  return 0;
}

double sumString(char* str, int n, int m) {
  double zero = 0.02, incredibleOne = 5, goodOne = 0.2, one = 0.15;
  double value = 0;
  for (int i = n; i <= m; i++) {
    if (str[i] == '2') {
      value += 0;
    } else if (str[i] == '1' && isSuperPrivileged(str, i))
      value += incredibleOne;  // 4-in-a-row
    else if (str[i] == '1' && isPrivileged(str, i))
      value += goodOne;
    else
      value += (one - zero) * ((int)str[i] - 48) + zero;  // 48 is the '0' in ASCII.}
  }
  return value;
}

int search(char* str, int n, int m, char c) {  // returns the 1 if founded, 0 if not.
  for (int i = n; i <= m; i++) {
    if (str[i] == c) {
      return 1;
    }  // found it
  }
  return 0;  // not found
}

// char* extractString(char* str, int n, int m) {
//   char* newStr = malloc((m - n + 2) * sizeof(char));
//   for (int i = n; i <= m; i++) newStr[i - n] = str[i];
//   // str[m - n + 1] = '\0';  // end of the string
//   return newStr;
// }

double evaluateNumber(char* str) {
  // str = **2 1 ***
  if (str[2] == '2') {
    if (search(str, 3, 5, '2') == 1)
      return 0;  // this string is 'eliminating'
    else {
      return sumString(str, 3, 5);
    }
  }
  // str = *** 1 2**
  if (str[3] == '2') {
    if (search(str, 0, 2, '2') == 1)
      return 0;  // this string is 'eliminating'
    else
      return sumString(str, 0, 2);
  }
  // str = *2* 1 ***
  if (str[1] == '2') {
    if (search(str, 3, 4, '2') == 1)
      return 0;  // this string is 'eliminating'
    else
      return sumString(str, 2, 5);
  }
  // str = *** 1 *2*
  if (str[4] == '2') {
    if (search(str, 1, 2, '2') == 1)
      return 0;  // this string is 'eliminating'
    else
      return sumString(str, 0, 3);
  }
  // Once here, the 2's are in either one or both extremes of the array.
  return sumString(str, 0, 5);
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

void preparation() {
  char* s;
  // for (int i = 0; i < 729; i++) {
  //   s = base10to3(i);
  //   printf("%s %.4lf\n", s, evaluateNumber(s));
  // }
  for (int i = 0; i < 729; i++) {
    s = base10to3(i);
    printf("%g, ", evaluateNumber(s));
  }
  puts(" ");
}
