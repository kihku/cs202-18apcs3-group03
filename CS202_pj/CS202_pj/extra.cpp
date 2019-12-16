#include"Library.h"
void ResizeConsole(int width, int height) {
	HWND console = GetConsoleWindow(); // lay thong tin hien tai cua console
	RECT edge;
	GetWindowRect(console, &edge);
	MoveWindow(console, edge.left, edge.top, width, height, TRUE); // chinh kich thuoc
}
void FixConsoleWindow() {
	HWND console = GetConsoleWindow();
	LONG style = GetWindowLong(console, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(console, GWL_STYLE, style);
	RECT rectScreen;
	GetWindowRect(console, &rectScreen);
	int ConsolePosX;
	int ConsolePosY;
	int Width = rectScreen.right - rectScreen.left;
	int Height = rectScreen.bottom - rectScreen.top;
	ConsolePosX = ((rectScreen.right - rectScreen.left) / 2 - Width / 2);
	ConsolePosY = ((rectScreen.bottom - rectScreen.top) / 2 - Height / 2);
	SetWindowPos(console, NULL, ConsolePosX, ConsolePosY, Width, Height, SWP_SHOWWINDOW || SWP_NOSIZE);
}
void gotoxy(int x, int y)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}

void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}
void SetColor(int ForgC)
{
	WORD wColor;

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	//We use csbi for the wAttributes word.
	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		//Mask out all but the background attribute, and add in the forgournd color
		wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
	return;
}
void TextColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
