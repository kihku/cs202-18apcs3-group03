#pragma once
#include"Library.h"

void ResizeConsole(int width, int height);
void  FixConsoleWindow();
void gotoxy(int x, int y);
void ShowConsoleCursor(bool showFlag);
void SetColor(int ForgC);
void TextColor(int color);