#include"Library.h"
CGame::CGame() :lane(level)
{
	//settingMenu();
	menu();
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
void CGame::updatePosPeople(char keyPressed)
{
	unique_lock<mutex> lk(CGame::mtx);
	const int step_horizontal = 2;
	const int step_vertical = 2;
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
	//Collide();
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
	vector<Enemy*> ene, tmp;
	tmp = lane.getCar();
	ene.insert(ene.end(), tmp.begin(), tmp.end());
	tmp.clear();
	tmp = lane.getTruck();
	ene.insert(ene.end(), tmp.begin(), tmp.end());
	tmp.clear();
	tmp = lane.getBird();
	ene.insert(ene.end(), tmp.begin(), tmp.end());
	tmp.clear();
	tmp = lane.getDino();
	ene.insert(ene.end(), tmp.begin(), tmp.end());
	tmp.clear();
	return ene;
}
/*Enemy* CGame::getVehicle()
{

	//Enemy* car = new Car;
//	return car;
}*/

void CGame::resetGame()
{
	system("cls");
	SCREEN_COLOR;
	//lane.~Lane();
	drawGame();
	//Lane();
}
void CGame::exitGame()
{
	//IS_RUNNING = false;
	system("cls");
	CGame();
	//t->join();
}
//void exitGame(HANDLE); 
void CGame::gamePlay()
{
	SCREEN_COLOR;
	int keyPressed;
	bool isPause = false;
	//return init lives for people
	cn.resetLives();
	cn.backToCheckPoint();
	drawGame();
	
	thread th1(&CGame::updatePosVehicle, this);
	HANDLE th1_handle = th1.native_handle();
	while (1)
	{
		//level up
		if (cn.isFinish())
		{
			//pauseGame(th1_handle);
			nextlevel(th1_handle);
		}
		//gameover
		if (cn.getLives() <= 0)
		{
			SuspendThread(th1_handle);
			system("cls");
			gameOver();
		}
		keyPressed = _getch();
		if (keyPressed == 0)
			keyPressed = _getch();

		if (keyPressed == 13 && isPause == false)
		{
			unique_lock<mutex>lk(CGame::mtx);
			gotoxy(screenSize_H_right + 14, screenSize_V_top - 1);
			cout << "P A U S E";
			lk.unlock();
			pauseGame(th1_handle);
			isPause = true;
			pauseMenu(th1_handle, isPause);
		}
		else if (keyPressed == 'c' || keyPressed == 'C')
		{
			string save;
			pauseGame(th1_handle);

			//cout << "Enter filename: ";
			//cin >> save;

			ofstream fout;
			fout.open("test.txt");
			saveGame(fout);
		}
		else if(isPause==false)
		{
			updatePosPeople(keyPressed);
			Collide();
		}
		
	}
	if (th1.joinable())
		th1.join();
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
	SCREEN_COLOR;
	//erase menu
	gotoxy(screenSize_H_right + 14, screenSize_V_top - 1);
	cout << "         ";
	gotoxy(screenSize_H_right + 15, screenSize_V_top +1);
	cout << "      "; 
	gotoxy(screenSize_H_right + 15, screenSize_V_top + 2);
	cout << "        ";
	gotoxy(screenSize_H_right + 15, screenSize_V_top + 3);
	cout << "    ";
	ResumeThread(t);

}
//void pauseGame(HANDLE);
//void resumeGame(HANDLE); 
void CGame::updatePosVehicle()
{
	while (true)
	//Collide();
		lane.updateLane(level);
}
void CGame::updatePosAnimal()
{

}
void CGame::drawGame()
{
	system("cls");
	//SCREEN_COLOR;
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
	cout << "L E V E L " << level.getLevel();
	gotoxy(screenSize_H_right + 6, screenSize_V_top + 11);
	cout << "L I V E S";
	gotoxy(screenSize_H_right + 10, screenSize_V_top + 13);
	for (int i = 0; i < cn.getLives()*3; ++i)
		cout << char(222);
	gotoxy(screenSize_H_right+4, screenSize_V_top + 18);
	cout << "Press WASD to MOVE";
	gotoxy(screenSize_H_right + 10, screenSize_V_top + 19);
	cout << "Esc to EXIT";
	//draw people
	Point pos = cn.currentPos();
	gotoxy(pos.x, pos.y);
	cout << char(219) << char(219) << char(219);
	gotoxy(pos.x, pos.y + 1);
	cout << " " << char(219) << "   ";
	lane.drawLane(level);
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
	const char* tenmuc[] = { "N E W  G A M E","L O A D  G A M E","S E T T I N G S","Q U I T" };
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
			gamePlay();
			//START GAME
		}
		else if ((ch == ENTER) && (stt == 1))
		{
			
			break; //LOAD GAME
		}
		else if ((ch == ENTER) && (stt == 2))
		{
			settingMenu();
			break;//SETTINGS
		}
		else if ((ch == ENTER) && (stt == 3))
		{
			exit(0);
			break;//exit
		}

	}
}
void CGame::pauseMenu(HANDLE handle, bool& isPause)
{
	//unique_lock<mutex>lk(CGame::mtx);
	int ki;
	int menu_x = screenSize_H_right + 15, menu_y = screenSize_V_top;
	const int SL = 3;
	//system("cls");

	const char* tenmuc[] = { "Resume","Restart","Exit" };
	for (ki = 1; ki < SL; ki++)
	{
		gotoxy(menu_x, ki + 1 + menu_y);
		PAUSE_SCREEN_CO;
		_cprintf(tenmuc[ki]);
	}
	gotoxy(menu_x, 1 + menu_y);
	PAUSE_BUTTON_CO;
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
				gotoxy(menu_x, 1 + menu_y);
				PAUSE_SCREEN_CO;
				_cprintf(tenmuc[0]);
				gotoxy(menu_x, SL + menu_y);
				PAUSE_BUTTON_CO;
				_cprintf(tenmuc[stt]);
			}
			else
			{
				gotoxy(menu_x, stt + 2 + menu_y);
				PAUSE_SCREEN_CO;
				_cprintf(tenmuc[stt + 1]);
				gotoxy(menu_x, stt + 1 + menu_y);
				PAUSE_BUTTON_CO;
				_cprintf(tenmuc[stt]);
			}
		}
		else if (ch == KEY_DOWN)
		{
			stt++;
			if (stt > SL - 1)
			{
				gotoxy(menu_x, SL + menu_y);
				PAUSE_SCREEN_CO;
				_cprintf(tenmuc[SL - 1]);
				stt = 0;
				gotoxy(menu_x, 1 + menu_y);
				PAUSE_BUTTON_CO;
				_cprintf(tenmuc[stt]);
			}
			else
			{
				gotoxy(menu_x, stt + menu_y);
				PAUSE_SCREEN_CO;
				_cprintf(tenmuc[stt - 1]);
				gotoxy(menu_x, stt + 1 + menu_y);
				PAUSE_BUTTON_CO;
				_cprintf(tenmuc[stt]);
			}
		}
		else if ((ch == ENTER) && (stt == 0))
		{
			resumeGame(handle);
			isPause = false;
			//lk.unlock();
			break; //resume
		}
		else if ((ch == ENTER) && (stt == 1))
		{

			resetGame();
			
			ResumeThread(handle);
			isPause = false;
			cn.eraseCorpse();
			cn.backToCheckPoint();
			break;//restart

		}
		else if ((ch == ENTER) && (stt == 2))
		{
			exitGame();
			break;//exit
		}
	}
}
void CPEOPLE::reduceLive()
{
	if (lives > 0)
	{
		lives -= 1;
		unique_lock<mutex> lk(CGame::mtx);
		gotoxy(screenSize_H_right + 10, screenSize_V_top + 13);
		cout << "               ";
		gotoxy(screenSize_H_right + 10, screenSize_V_top + 13);
		for (int i = 0; i < lives * 3; ++i)
			cout << char(222);
	}
}
//bool CGame::isCrash(Point pos) {
//		if (abs(cn.mX - pos.x) <=5 && abs(mY - pos.y) <= 5) {
//			return true;
//		}
//		return false;
//	}
//vector <Enemy*> enemyList = rowsData.listEnemy(); //enemyList = 0 
void CGame::Collide() {
	for (int i = 0; i < (int)getVehicle().size(); ++i) {
		//drawEnemies(enemyList[i]);
		if (getVehicle()[i])
		{
			if (cn.isCrash(getVehicle()[i]->getPos(), getVehicle()[i]->getShapeSize()) == true) {
				//if (!constantVar::isMute) enemyList[i]->sound();
				//cn.killPlayer();
				//gotoxy(20, 20);
				cn.reduceLive();
				cn.eraseCorpse();
				cn.backToCheckPoint();
			
				//Destroy thread enemy;
				//bombEffect();
			}
		}
	}
}
void CGame::gameOver() {
	char choice;
	bombEffect();
	gotoxy(20, 4);
	cout << "P L A Y  A G A I N? (y/n)";
	cin >> choice;
	if (choice == 'y')
	{
		exitGame();
	}
}
void CGame:: nextlevel(HANDLE handle) {
	
	level.levelUp();
	resetGame();
	
	cn.eraseCorpse();
	cn.backToCheckPoint();
}
void CGame::bombEffect()
{
	/*string line;
	ifstream in("Explode.txt");
	in >> line;
	
	while (getline(in, line))
	{
		cout << line;
		
	}
	in.close();*/
	const int baseX = 10, baseY = 10;
	gotoxy(baseX, baseY);
	cout << R"(                                               ____                       )" << "\n";
	gotoxy(baseX, baseY + 1);
	cout << R"(                                           __,-~~/~    `---.                  )" << "\n";
	gotoxy(baseX, baseY + 2);
	cout << R"(                                         _/_,---(      ,    )                 )" << "\n";
	gotoxy(baseX, baseY + 3);
	cout << R"(                                     __ /        <    /   )  \___             )" << "\n";
	gotoxy(baseX, baseY + 4);
	cout << R"(                      - ------===;;;'====------------------===;;;===----- -  -)" << "\n";
	gotoxy(baseX, baseY + 5);
	cout << R"(                                      \/  ~"~"~"~"~"~\~"~)~" / )" << "\n";
	gotoxy(baseX, baseY + 6);
	cout << R"(                                        (_ (   \  (     >    \)               )" << "\n";
	gotoxy(baseX, baseY + 7);
	cout << R"(                                         \_( _ <         >_>'                 )" << "\n";
	gotoxy(baseX, baseY + 8);
	cout << R"(                                            ~ `-i' ::>|--"                    )" << "\n";
	gotoxy(baseX, baseY + 9);
	cout << R"(                                                I;|.|.|                       )" << "\n";
	gotoxy(baseX, baseY + 10);
	cout << R"(                                               <|i::|i|`.                     )" << "\n";
	gotoxy(baseX, baseY + 11);
	cout << R"(                                              (` ^'"`-' ")                    )";

}
void CGame::settingMenu()
{
	const int menu_x = 40, menu_y = 12;
	int ch, index_x = 0, index_y = 0, sl = 4;
	const char* tenmuc[] = { "E A S Y","H A R D","O N","O F F","B A C K" };
	system("cls");
	SCREEN_COLOR;
	gotoxy(menu_x, menu_y);
	cout << "M O D E";
	gotoxy(menu_x, menu_y+2);
	cout << "S O U N D";
	gotoxy(menu_x + 17, menu_y);
	cout << "E A S Y   H A R D";
	gotoxy(menu_x+17, menu_y + 2);
	cout << "O N       O F F";
	gotoxy(menu_x + 17, menu_y + 4);
	cout << "B A C K";
	//in dam luc khoi tao
	gotoxy(menu_x + 17, menu_y);
	SETTING_BUT_CO;
	cout << tenmuc[0];
	while (1)
	{
		ch = _getch();
		if (ch == 0)
			ch = _getch();
		if (ch == KEY_UP)
		{
			index_y--;
			if (index_y < 0)
			{
				index_y = 4;
				gotoxy(menu_x+17,  menu_y);
				SCREEN_COLOR;
				_cprintf(tenmuc[0]);
				gotoxy(menu_x+17, sl + menu_y);
				SETTING_BUT_CO;
				_cprintf(tenmuc[index_x + index_y]);
			}
			else
			{
				gotoxy(menu_x+17, index_y  + menu_y);
				SCREEN_COLOR;
				_cprintf(tenmuc[index_y + 1]);
				gotoxy(menu_x+17, index_y + menu_y);
				SETTING_BUT_CO;
				_cprintf(tenmuc[index_y + index_x]);
			}
		}
		
	}



	gotoxy(50, 20);
	system("pause");
	
}