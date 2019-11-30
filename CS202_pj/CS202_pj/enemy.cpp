#include"Library.h"
int CTRAFFIC::numTraffic = 0;
int CCAR::numCar = 0;
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

void CCAR::Move(int spd)
{

	//drawVeh({ y,x });
	int l = 5, r = 100;
	dir = !dir;
	if (dir) {
		for (int i = 0; i < 10000; ++i)
		{
			//di lo khung thi di lai
			if (r < pos.x) {
				gotoxy(pos.x , pos.y);
				cout << "         ";
				gotoxy(pos.x , pos.y + 1);
				cout << "         ";
				gotoxy(pos.x , pos.y + 2);
				cout << "         ";
				pos.x = 0, pos.y = 5, drawVeh({ pos.x,pos.y });
			}
			else {
				++pos.x, drawVeh({ pos.x,pos.y });
				gotoxy(pos.x - 1, pos.y);
				cout << " ";
				gotoxy(pos.x - 1, pos.y + 1);
				cout << " ";
				gotoxy(pos.x - 1, pos.y + 2);
				cout << " ";
				Sleep(spd);
			}
		}
	}
	else {
		for (int i = 0; i < 10000; ++i)
		{
			//di lo khung thi di lai
			if (pos.x < l) {
				gotoxy(pos.x, pos.y);
				cout << "         ";
				gotoxy(pos.x , pos.y + 1);
				cout << "         ";
				gotoxy(pos.x  , pos.y + 2);
				cout << "         ";
				pos.x = 85, pos.y = 5, drawVeh({ pos.x,pos.y });
			}
			else {
				gotoxy(pos.x + 7, pos.y);
				cout << " ";
				gotoxy(pos.x+7, pos.y + 1);
				cout << " ";
				gotoxy(pos.x +7, pos.y + 2);
				cout << " ";
				--pos.x, drawVeh({ pos.x,pos.y });
				
				Sleep(spd);
			}
		}
	}

}
void CCAR::pause()
{
	drawVeh(pos);
}
void CTRUCK::Move(int x, int y)
{
	//for (int i = 5; i < 100; ++i)
	//{
	//	truck.Move(i, 10);
	//	Sleep(200);
	//}
}

void CTRUCK::pause()
{
	drawVeh(pos);
}
