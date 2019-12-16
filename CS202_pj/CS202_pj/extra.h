#pragma once
#include"Library.h"

class constVar {
public:
	static bool isMute;
	static bool isHard;
};
void gotoxy(int x, int y);
void ShowConsoleCursor(bool showFlag);
void SetColor(int ForgC);
void TextColor(int color);