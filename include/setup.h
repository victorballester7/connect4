#ifndef __SETUP_H__
#define __SETUP_H__

// #define WINDOWS // uncomment this line to use it for windows.

#ifdef WINDOWS
#include <direct.h>
#define pwd _getcwd
#else
#include <unistd.h>  // also for sleep() function. In Windows use <windows.h>
#define pwd getcwd
#endif

char* fileNameCreation();
void uploadFile(char i);
int presentation();

#endif
