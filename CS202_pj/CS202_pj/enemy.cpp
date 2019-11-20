#include"Library.h"
void CDINAUSOR::Move(int x, int y)
{
	const int height = 3;
	const int width = 4;
	for (int i = y; i < y+height; ++i)
	{
		for (int j = x; j < x+width; ++j)
		{
			if (i == y && j == x+3||i==y&&j==x+2)
			{
				continue;
			}
			gotoxy(j, i);
			cout << char(219);
			if (i==y+height-1 &&j == x + width - 1)
			{
				for (int k = 0; k < width / 4; ++k) //lam tron len xuong?
				{
					gotoxy(j + 1, i);
					cout << char(219);
				}
			}
		}
		x-=2;
	}
	for (int j = x-width; j < x; ++j)
	{
		gotoxy(j, y);
		cout << "      ";
		gotoxy(j , y + 1);
		cout << "    ";
		gotoxy(j, y + 2);
		cout << "  ";
	}
}
void CCAR::Move(int x, int y)
{
	//    _____
	//   /    |_\_
	// |__O___O___|
	gotoxy(x, y);
	cout << "    _____";
	gotoxy(x, y + 1);
	cout << "   /    |_\_";
	gotoxy(x, y + 2);
	cout << " |__O___O___|";
}
void CTRUCK::Move(int x, int y)
{
	//  _________
	// |///////|_\_
	// |_/O____O\__|
	gotoxy(x, y);
	cout << "  ________";
	gotoxy(x, y + 1);
	cout << " |//////|_\\_";
	gotoxy(x, y + 2);
	cout << " |_/O____O\__|";
}