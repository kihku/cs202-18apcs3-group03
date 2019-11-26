#include"Library.h"
//start x,y CDINAUSOR is (4,3)

void truckMoving()
{
	CTRUCK truck;
	for (int i = 5; i < 100; ++i)
	{
		truck.Move(i, 10);
		Sleep(200);
	}
}
//for testing purpose
int main()
{
	ShowConsoleCursor(false);
	CGAME game;
	thread th1(&CGAME::controlPeople, game);
	thread th2(truckMoving);
	if (th1.joinable())
		th1.join();
	return 0;
}