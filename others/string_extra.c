#include <stdio.h>
#include <string.h>

int search(char str[], char c) {
  for (int i = 0; i < strlen(str); i++)
    if (str[i] == 'c') return i;
  return -1;
}
