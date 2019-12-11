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
	fout << axt->getPos().x << endl;
	fout << axt->getPos().y << endl;
		//save car
	fout << axh->getPos().x << endl;
	fout << axh->getPos().y << endl;
		//save dinosaur
	fout << axh->getPos().x << endl;
	fout << axh->getPos().y << endl;
		//save bird
	fout << ac->getPos().x << endl;
	fout << ac->getPos().y << endl;


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
	system("Color B0");
	const int delta = 3;
	const int scoreBoard_H = 25;
	const int scoreBoard_V = 5;
	for (int i = screenSize_H_left; i < screenSize_H_right; ++i)
	{
		gotoxy(i, 1);
		cout << char(196);
	}
	gotoxy(screenSize_H_right, 1);
	cout << char(191);
	for (int i = screenSize_V_top-1; i < screenSize_V_bot + delta; ++i)
	{
		gotoxy(screenSize_H_right, i);
		cout << char(179);
	}
	gotoxy(screenSize_H_right, screenSize_V_bot + delta);
	cout << char(217);
	for (int i = 4; i < screenSize_H_right; ++i)
	{
		gotoxy(i, screenSize_V_bot + delta);
		cout << char(196);
	}
	gotoxy(3, screenSize_V_bot + delta);
	cout << char(192);
	for (int i = 2; i < screenSize_V_bot + delta; ++i)
	{
		gotoxy(3, i);
		cout << char(179);
	}
	gotoxy(3, 1);
	cout << char(218);
	//SCORE BOARD
	gotoxy(screenSize_H_right + 4, 7);
	cout << char(218);
	for (int i = screenSize_H_right + 5; i < screenSize_H_right + 5 + scoreBoard_H; ++i)
	{
		gotoxy(i, 7);
		cout << char(196);
	}
	gotoxy(screenSize_H_right + 5 + scoreBoard_H, 7);
	cout << char(191);
	for (int i = 8; i < scoreBoard_V + 15; ++i)
	{
		gotoxy(scoreBoard_H + screenSize_H_right + 5, i);
		cout << char(179);
	}
	for (int i = 8; i < scoreBoard_V + 15; ++i)
	{
		gotoxy(screenSize_H_right + 4, i);
		cout << char(179);
	}
	gotoxy(screenSize_H_right + 4, scoreBoard_V + 15);
	cout << char(192);
	for (int i = screenSize_H_right + 5; i < screenSize_H_right + 5 + scoreBoard_H; ++i)
	{
		gotoxy(i, scoreBoard_V + 15);
		cout << char(196);
	}
	gotoxy(screenSize_H_right + 5 + scoreBoard_H, scoreBoard_V + 15);
	cout << char(217);
	//Score Board menu
	gotoxy(screenSize_H_right + 12, screenSize_V_top + 5);
	cout << "S T A T U S";
	gotoxy(screenSize_H_right + 6, screenSize_V_top + 8);
	cout << "L E V E L";
	gotoxy(screenSize_H_right + 6, screenSize_V_top + 11);
	cout << "L I V E S";
	gotoxy(screenSize_H_right + 10, screenSize_V_top + 13);
	for (int i = 0; i < cn.getLives()*5; ++i)
		cout << char(222);
	gotoxy(screenSize_H_right+4, screenSize_V_top + 18);
	cout << "Press WASD to MOVE";
	gotoxy(screenSize_H_right + 10, screenSize_V_top + 19);
	cout << "Esc to EXIT";
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