#include"Library.h"
void CGAME::updatePosPeople(char keyPressed)
{
	const int step_horizontal = 2;
	const int step_vertical = 1;
	if (keyPressed == 'd')
	{
		cn.Right(step_horizontal);
	}
	else if (keyPressed == 'a')
	{
		cn.Left(step_horizontal);
	}
	else if (keyPressed == 'w')
	{
		cn.Up(step_vertical);
	}
	else if (keyPressed == 's')
	{
		cn.Down(step_vertical);
	}
}
CGAME::CGAME()
{
	
}
CGAME::~CGAME()
{

}
CPEOPLE CGAME::getPeople()
{
	CPEOPLE peo;
	return peo;
}
/*CVEHICLE* CGAME::getVehicle()
{

	//CVEHICLE* car = new CCAR;
//	return car;
}*/
CANIMAL* CGAME::getAnimal()
{
	CANIMAL* anim = new CBIRD;
	return anim;
}
void CGAME::resetGame()
{

}
void CGAME::exitGame(HANDLE)
{
	//IS_RUNNING = false;
	system("cls");
	//t->join();
}
//void exitGame(HANDLE); 
void CGAME::startGame()
{

}
void CGAME::loadGame(istream)
{

}
void CGAME::saveGame(istream)
{

}
void CGAME::pauseGame(HANDLE t)
{
	SuspendThread(t);
}
void CGAME::resumeGame(HANDLE t)
{
	ResumeThread(t);
}
//void pauseGame(HANDLE);
//void resumeGame(HANDLE); 
void CGAME::updatePosVehicle()
{

}
void CGAME::updatePosAnimal()
{

}
void CGAME::drawGame()
{
	const int delta = 3;
	const int scoreBoard_H = 25;
	const int scoreBoard_V = 5;
	for (int i = 4; i < screenSize_H; ++i)
	{
		gotoxy(i, 1);
		cout << char(196);
	}
	gotoxy(screenSize_H, 1);
	cout << char(191);
	for (int i = 2; i < screenSize_V + delta; ++i)
	{
		gotoxy(screenSize_H, i);
		cout << char(179);
	}
	gotoxy(screenSize_H, screenSize_V + delta);
	cout << char(217);
	for (int i = 4; i < screenSize_H; ++i)
	{
		gotoxy(i, screenSize_V + delta);
		cout << char(196);
	}
	gotoxy(3, screenSize_V + delta);
	cout << char(192);
	for (int i = 2; i < screenSize_V + delta; ++i)
	{
		gotoxy(3, i);
		cout << char(179);
	}
	gotoxy(3, 1);
	cout << char(218);
	//SCORE BOARD
	gotoxy(screenSize_H + 4, 7);
	cout << char(218);
	for (int i = screenSize_H + 5; i < screenSize_H + 5 + scoreBoard_H; ++i)
	{
		gotoxy(i, 7);
		cout << char(196);
	}
	gotoxy(screenSize_H + 5 + scoreBoard_H, 7);
	cout << char(191);
	for (int i = 8; i < scoreBoard_V + 15; ++i)
	{
		gotoxy(scoreBoard_H + screenSize_H + 5, i);
		cout << char(179);
	}
	for (int i = 8; i < scoreBoard_V + 15; ++i)
	{
		gotoxy(screenSize_H + 4, i);
		cout << char(179);
	}
	gotoxy(screenSize_H + 4, scoreBoard_V + 15);
	cout << char(192);
	for (int i = screenSize_H + 5; i < screenSize_H + 5 + scoreBoard_H; ++i)
	{
		gotoxy(i, scoreBoard_V + 15);
		cout << char(196);
	}
	gotoxy(screenSize_H + 5 + scoreBoard_H, scoreBoard_V + 15);
	cout << char(217);
}