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
void CGAME::drawGame()
{
	const int delta = 3;
	for (int i= 4; i < screenSize_H; ++i)
	{
		gotoxy(i, 1);
		cout << char(196);
	}
	gotoxy(screenSize_H, 1);
	cout << char(191);
	for (int i = 2; i < screenSize_V+delta; ++i)
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
}
CGAME::~CGAME()
{

}
CPEOPLE CGAME::getPeople()
{
	CPEOPLE peo;
	return peo;
}
CVEHICLE* CGAME::getVehicle()
{
	CVEHICLE* car = new CCAR;
	return car;
}
CANIMAL* CGAME::getAnimal()
{
	CANIMAL* anim = new CBIRD;
	return anim;
}
void CGAME::resetGame()
{

}
void CGAME::exitGame(HANDLE t)
{
	//IS_RUNNING = false;
	system("cls");
	//t->join();
}
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
void CGAME::updatePosVehicle()
{

}
void CGAME::updatePosAnimal()
{

}