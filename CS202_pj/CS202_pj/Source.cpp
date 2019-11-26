#include"Library.h"
//start x,y CDINAUSOR is (4,3)

//for testing purpose
void tructMove()
{
	CTRUCK truck;
	for (int i = 5; i < 100; ++i)
	{
		truck.Move(i, 10);
		Sleep(200);
	}
}
int main()
{
	char control;
	ShowConsoleCursor(false);
	CGAME game;
	//thread th1(&CGAME::controlPeople, game);
	thread th1(tructMove);
	while (1)
	{
		control = _getch();
		if (control == 0)
			control = _getch();
		if (control == 27)
			game.pauseGame(th1);
	}
	if (th1.joinable())
		th1.join();
	return 0;
}