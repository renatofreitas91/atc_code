
#pragma once

#define DIM 1000
#include <stdio.h>
#include <iostream>
#include <tchar.h>
#include <stdlib.h>
#include <windows.h>


bool isContained(char to_find[DIM], char string[DIM]);
bool verifyNumber(char number);
bool isEqual(char to_find[DIM], char string[DIM]);
bool verifyLetter(char letter);
void ShowConsoleCursor(bool bShow);
void cls();
void currentSettings();
void GetWindowPos(int *x, int *y, int *maxX, int *maxY);
void MouseMove(int x, int y);
void mode(int option);
void getATCPath();
void setFontSize(int x, int y);
void changecursor();
void restorecursor();
void numSystemsController(int state);
void siPrefixController(int state);
void actualTimeController(int state);
void verboseResolutionController(int state);
void atcEnvironment();
void atcFolders();
void atcCalculations();
void atcTime();
void atcHandlingPC();
void sendToATC(char command[100]);
void colors();
void window();
void GetScale();
void window();
void sleepRF();
int verticalConversion(int Y);
int horizontalConversion(int X);
boolean IsPreviousToWindowsVista();

