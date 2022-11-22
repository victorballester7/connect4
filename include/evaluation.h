#ifndef __EVALUATION_H__
#define __EVALUATION_H__

char* base10to3(int i);
void preparation(int dsq, int zero, int one, int goodOne);
void printArray(int v[], int n);
// int isSuperPrivileged(char* str, int i);
// int isPrivileged(char* str, int i);
// int sumString(char* str, int n, int m, int one, int goodOne);
// int search(char* str, int n, int m, char c);
int evaluateNumber(char* str, int dsq, int zero, int one, int goodOne);
int countString(char* str, int n, int m);
int computer_iteration(int old_dsq, int old_zero, int old_one, int old_goodOne);
void computer_iteration2(int old_dsq, int old_zero, int old_one, int old_goodOne);
void prepareVector(int v[], int dsq, int zero, int one, int goodOne);
// char* extractString(char* str, int n, int m);

#endif
