#include"cgame.h"
void CGame::updatePosPeople(char keyPressed)
{
	unique_lock<mutex> lk(CGame::mtx);
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
CGame::CGame()
{
	for (int i = 0; i < 24; ++i)
	{
		for (int j = 0; j < 85; ++j)
		{
			map[j][i] = 0;
		}
	}
	//init people pos 
	//people Pos: 42 24
	map[42][22] = 1;
	map[43][22] = 1;
	map[44][22] = 1;
	map[43][23] = 1;
	//mX = screenSize_H / 2;
	//mY = screenSize_V;
}
CGame::~CGame()
{

}
CPEOPLE CGame::getPeople()
{
	CPEOPLE peo;
	return peo;
}
/*Enemy* CGame::getVehicle()
{

	//Enemy* car = new Car;
//	return car;
}*/

void CGame::resetGame()
{

}
void CGame::exitGame(HANDLE)
{
	//IS_RUNNING = false;
	system("cls");
	//t->join();
}
//void exitGame(HANDLE); 
void CGame::startGame()
{

}
void CGame::loadGame(istream)
{

}
void CGame::saveGame(ofstream &fout)
{
	//SAVE PEOPLE
	fout << cn.currentPos().x << endl;
	fout << cn.currentPos().y << endl;
	//SAVE ENEMY
		//save truck 
	/*fout << lane. << endl;*/
	//fout << axt->getPos().y << endl;
	//	//save car
	//fout << axh->getPos().x << endl;
	//fout << axh->getPos().y << endl;
	//	//save dinosaur
	//fout << axh->getPos().x << endl;
	//fout << axh->getPos().y << endl;
	//	//save bird
	//fout << ac->getPos().x << endl;
	//fout << ac->getPos().y << endl;


}
void CGame::pauseGame(HANDLE t)
{
	SuspendThread(t);
}
void CGame::resumeGame(HANDLE t)
{
	ResumeThread(t);
}
//void pauseGame(HANDLE);
//void resumeGame(HANDLE); 
void CGame::updatePosVehicle()
{
	
}
void CGame::updatePosAnimal()
{

}
void CGame::drawGame()
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
bool CGame::exportMap(const char* path)
{
	ofstream file;
	file.open(path);
	if (!file.is_open())
	{
		return false;
	}
	for (int i = 0; i < 24; ++i)
	{
		for (int j = 0; j < 85; ++j)
		{
			file << map[j][i]<<" ";
		}
		file << "\n";
	}
}
Point CGame::peoplePos()
{
	return cn.currentPos();
}