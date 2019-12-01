#include"Library.h"
//start x,y CDINAUSOR is (4,3)
/*//for testing purpose
void tructMove()
{
	CTRUCK truck;
	for (int i = 5; i < 100; ++i)
	{
		truck.Move(i, 10);
		Sleep(200);
	}
}*/
int main()
{
	CGAME game;
	game.drawGame();

	/*ShowConsoleCursor(false);
	char keyPressed;
	bool pause_game = false;
	CGAME game;
	game.drawGame();
	thread th1(tructMove);
	HANDLE th1_handle= th1.native_handle();
	while (1)
	{
		keyPressed = _getch();
		if (keyPressed == 0)
			keyPressed = _getch();
		if (keyPressed == 13 && pause_game == false)
		{
			game.pauseGame(th1_handle);
			pause_game = true;
		}
		else if (keyPressed == 13 && pause_game == true)
		{
			game.resumeGame(th1_handle);
			pause_game = false;
		}
		if (pause_game == false)
			game.updatePosPeople(keyPressed);
	}
	if (th1.joinable())
		th1.join();*/
	VEHLANE l(1);
	l.updatePosVehicle();
	
	return 0;
}