#include"Library.h"
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
vector<Enemy*> CGame::getVehicle()
{
	//example to get enemy position 
	vector<Enemy*> ene(2 * lane.getCar().size() + 2 * lane.getTruck().size(), NULL);
	ene.insert(ene.end(), lane.getCar().begin(), lane.getCar().end());
	ene.insert(ene.end(), lane.getTruck().begin(), lane.getTruck().end());
	ene.insert(ene.end(), lane.getBird().begin(), lane.getBird().end());
	ene.insert(ene.end(), lane.getDino().begin(), lane.getDino().end());
	return ene;
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
	drawGame();
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
	fout << getVehicle()[0]->getPos().x << endl;
	fout << getVehicle()[0]->getPos().y << endl;
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
	while(true)
	lane.updateLane();
}
void CGame::updatePosAnimal()
{

}
void CGame::drawGame()
{
	system("cls");
	SCREEN_COLOR;
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
void CGame::menu()
{

	//MAIN MENU
	SCREEN_COLOR;
	int ki;
	const int SL = 4;
	system("cls");
	const char* tenmuc[] = { "N E W  G A M E","L O A D  G A M E","S E T T I N G S","M Y P R O F I L E" };
	for (ki = 1; ki < SL; ki++)
	{
		gotoxy(52, ki + 1 + 10);
		SCREEN_COLOR;
		_cprintf(tenmuc[ki]);
	}
	gotoxy(52, 1 + 10);
	SCREEN_COLOR;
	BUTTON_COLOR;
	_cprintf(tenmuc[0]);
	char ch;
	int stt = 0;
	while (1)
	{
		ch = _getch();
		if (ch == 0)
			ch = _getch();
		if (ch == KEY_UP)
		{
			stt--;
			if (stt < 0)
			{
				stt = SL - 1;
				gotoxy(52, 1 + 10);
				SCREEN_COLOR;
				_cprintf(tenmuc[0]);
				gotoxy(52, SL + 10);
				BUTTON_COLOR;
				_cprintf(tenmuc[stt]);
			}
			else
			{

				gotoxy(52, stt + 2 + 10);
				SCREEN_COLOR;
				_cprintf(tenmuc[stt + 1]);
				gotoxy(52, stt + 1 + 10);
				BUTTON_COLOR;
				_cprintf(tenmuc[stt]);
			}
		}
		else if (ch == KEY_DOWN)
		{
			stt++;
			if (stt > SL - 1)
			{
				gotoxy(52, SL + 10);
				SCREEN_COLOR;
				_cprintf(tenmuc[SL - 1]);
				stt = 0;
				gotoxy(52, 1 + 10);
				BUTTON_COLOR;
				_cprintf(tenmuc[stt]);
			}
			else
			{
				gotoxy(52, stt + 10);
				SCREEN_COLOR;
				_cprintf(tenmuc[stt - 1]);
				gotoxy(52, stt + 1 + 10);
				BUTTON_COLOR;
				_cprintf(tenmuc[stt]);
			}
		}
		else if ((ch == ENTER) && (stt == 0))
		{
			startGame();
			break; //START GAME
		}
		else if ((ch == ENTER) && (stt == 1))
		{
			
			break; //LOAD GAME
		}
		else if ((ch == ENTER) && (stt == 2))
		{
			
			break;//SETTINGS
		}
		else if ((ch == ENTER) && (stt == 3))
		{
			
			
			break;//MY PROFILE
		}

	}
}
//vector <Enemy*> enemyList = rowsData.listEnemy(); //enemyList = 0 
void CGame::Collide() {
	for (int i = 0; i < (int)getVehicle().size(); ++i) {
	 	//drawEnemies(enemyList[i]);
		if (cn.isCrash(getVehicle()[i]->getPos())== true) {
			//if (!constantVar::isMute) enemyList[i]->sound();
			//cn.killPlayer();
			gotoxy(30, 30);
			cout<<" CRASH";
			system("cls");
		}
	}
}

void CGame::setting()
{

}