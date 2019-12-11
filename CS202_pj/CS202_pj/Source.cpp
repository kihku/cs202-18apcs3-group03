#include"Library.h"
//start x,y CDINAUSOR is (4,3)
//for testing purpose

mutex CGame::mtx;

void vehicleMove()
{
	Lane l;
	while (true) {
		l.updateLane();
	}
}
int main()
{
	ShowConsoleCursor(false);
	//SetColor(14);
	char keyPressed;
	bool pause_game = false;
	CGame game;
	game.menu();
	//game.drawGame();
	thread th1(vehicleMove);
	HANDLE th1_handle= th1.native_handle();
	game.exportMap("map.txt");
	Point peopos = game.peoplePos();
	//peopos.display();
	while (1)
	{
		
		keyPressed = _getch();
		if (keyPressed == 0)
			keyPressed = _getch();
		if (pause_game == false)
		{
			game.updatePosPeople(keyPressed);
		}
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
		if (keyPressed == 'c' || keyPressed == 'C')
		{
			string save;
			game.pauseGame(th1_handle);

			cout << "Enter filename: ";
			cin >> save;
			
			ofstream fout;
			fout.open(save + ".txt");
			game.saveGame(fout);
			pause_game = true;
		}
		
	}
	if (th1.joinable())
		th1.join();
	
	return 0;
}