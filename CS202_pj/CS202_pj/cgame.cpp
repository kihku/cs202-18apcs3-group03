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
void CGame::updatePosPeople(char keyPressed,bool lvUp)
{
	unique_lock<mutex> lk(CGame::mtx);
	const int step_horizontal = 2;

	const int step_vertical = 2;
	if (keyPressed == 'd')
	{
		/*if (!isMute)
			PlaySound(TEXT("move.wav"), NULL, SND_ASYNC);*/
		cn.Right(step_horizontal);
	}
	else if (keyPressed == 'a')
	{
		/*if (!isMute)
			PlaySound(TEXT("move.wav"), NULL, SND_ASYNC);*/
		cn.Left(step_horizontal);
	}
	else if (keyPressed == 'w')
	{
		/*if (!isMute)
			PlaySound(TEXT("move.wav"), NULL, SND_ASYNC);*/
		cn.Up(step_vertical);
	}
	else if (keyPressed == 's')
	{
		/*if (!isMute)
			PlaySound(TEXT("move.wav"), NULL, SND_ASYNC);*/
		cn.Down(step_vertical);
	}
	isIncreaseLive();
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

void CGame::resetGame(bool nextLevel)
{
	if (nextLevel == false)
	{
		system("cls");
		SCREEN_COLOR;
	}
	//lane.~Lane();
	drawGame(nextLevel);
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
	bool nextLevel = false;
	//return init lives for people
	cn.resetLives();
	cn.backToCheckPoint();
	drawGame(nextLevel);
	
	thread th1(&CGame::updatePosVehicle, this, nextLevel);
	HANDLE th1_handle = th1.native_handle();
	while (1)
	{
		//level up
		if (cn.isFinish())
		{
			//win
			if (lane.getLevel().getLevel()==3)
			{
				pauseGame(th1_handle);
				system("cls");
				gotoxy(20, 20);
				cout << "You WIN"; //kiem cai gi do
				system("pause");
				menu();
			}
			nextLevel = true;
			//pauseGame(th1_handle);
			lane.levelUp();
			nextlevel(th1_handle, nextLevel);
			nextLevel = false;
			
		}
		//gameover
		if (cn.getLives() <= 0)
		{
			SuspendThread(th1_handle);
			system("cls");
			gameOver(th1_handle);
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
			pauseMenu(th1_handle, isPause,nextLevel);
		}
		else if (keyPressed == 'c' || keyPressed == 'C')
		{
			string save;
			pauseGame(th1_handle);
			cout << "Enter filename: ";
			cin >> save;


			saveGame(save);
			ResumeThread(th1_handle);
		}
		else if(isPause==false)
		{
			updatePosPeople(keyPressed, nextLevel);
		}
		
	}
	if (th1.joinable())
		th1.join();
}
void CGame::loadGame(string load)
{
	ifstream fin;
	fin.open(load + ".dat", ios::out | ios::binary);
	level.~Level();
	int lv, mode;
	fin >> lv >> mode;
	new(&level) Level(lv,mode);
	new(&lane) Lane(level);
	int peopleX, peopleY, live;
	fin >> peopleX;
	fin >> peopleY;
	fin >> live;
	new(&cn) CPEOPLE(peopleX, peopleY, live);

}
void CGame::saveGame(string save)
{
	ofstream fout;
	fout.open(save + ".dat", ios::out | ios::binary);

	//SAVE LEVEL
	fout << lane.getLevel().getLevel() << endl;
	//SAVE MODE
	fout << lane.getLevel().getMode() << endl;
	//SAVE PEOPLE
	fout << cn.currentPos().x << endl;
	fout << cn.currentPos().y << endl;
	fout << cn.getLives() << endl;
	//SAVE ENEMY
	vector<Enemy*>v;
	v = getVehicle();
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i] != NULL)
		{
			fout << v[i]->getType() << endl;
			fout << v[i]->getPos().x << endl;
			fout << v[i]->getPos().y << endl;
		}
	}
	fout.close();


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
void CGame::updatePosVehicle(bool nextLevel)
{
	while (true)
	{
		if (nextLevel == true)
			break;
		Collide();
		lane.updateLane(nextLevel);
	}

}
void CGame::updatePosAnimal()
{

}
void CGame::drawGame(bool nextLevel)
{
	PlaySound(TEXT("smw_bonus_game_end.wav"), NULL, SND_ASYNC);
	unique_lock<mutex>lk(CGame::mtx);
	lk.unlock();
	if (nextLevel == true)
		lk.lock(); 
	system("cls");
	if (!isMute)
		PlaySound(TEXT("zelda_13.wav"), NULL, SND_ASYNC);
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
	gotoxy(screenSize_H_right + 14, screenSize_V_top + 5);
	if (!lane.getLevel().getMode())
		cout << "E A S Y";
	else
		cout << "H A R D";
	gotoxy(screenSize_H_right + 6, screenSize_V_top + 8);
	cout << "L E V E L  " << lane.getLevel().getLevel();
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
	lane.drawLane(nextLevel);
	printHeart();
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
string CGame::getFileContents(std::ifstream& File)
{
	std::string Lines = "";        //All lines

	if (File)                      //Check if everything is good
	{
		while (File.good())
		{
			std::string TempLine;                  //Temp line
			std::getline(File, TempLine);        //Get temp line
			TempLine += "\n";                      //Add newline character

			Lines += TempLine;                     //Add newline
		}
		return Lines;
	}
	else                           //Return error
	{
		return "ERROR File does not exist.";
	}
}
void CGame::titleMenu() {
	//Ascii art

	ifstream Reader("CrossyRoad.txt");             //Open file
	string Art = getFileContents(Reader);       //Get file
	gotoxy(0,0);
	cout << Art << std::endl;               //Print it to the screen
	Reader.close();                           //Close file
	///
	SCREEN_COLOR;
	/*int ki;
	const int SL = 4;
	const char* tenmuc[] = { "P H A M  T R A N  H I E N  D U N G","N G U Y E N  T R A N  M I N H  K H U E","V O  M I N H  N H A N","N G U Y E N  T H I  B I C H  V A N" };
	for (ki = 1; ki < SL; ki++)
	{
		gotoxy(32, ki + 1 + 10);
		SCREEN_COLOR;
		_cprintf(tenmuc[ki]);
	}
	gotoxy(32, 1 + 10);
	SCREEN_COLOR;
	BUTTON_COLOR;
	_cprintf(tenmuc[0]);*/
	//
	/*srand(time(0));
	int x = 0;
	for (int i = 0; i < 100; i++) {
		int r = rand() % 500;
		x++;
		cout << "\r" << x << "% completed." << flush;
		if (i < 43) {
			Sleep(r / 6);
		}
		else if (i > 43 && i < 74) {
			Sleep(r / 8);
		}
		else if (i < 98) {
			Sleep(r / 5);
		}
		else if (i > 97 && i != 99) {
			Sleep(1000);
		}
	}*/
	///
	/*do
	{
		cout << '\n' << "Press a key to continue...";
	} while (cin.get() != '\n');*/
}
void CGame::menu()
{
	system("cls");
	if (!isMute)
		PlaySound(TEXT("jingleBell.wav"), NULL, SND_ASYNC);
	//MAIN MENU
	titleMenu();
	///
	//dino
	drawDino(92, 12, 0);
	drawDino(20, 12, 1);
	drawDino(7, 19, 0);
	drawDino(105, 19, 1);
	drawDino(50, 21, 1);
	drawDino(62, 21, 0);
	gotoxy(59, 18);
	cout << " " << char(220) << " " << char(220);
	gotoxy(59, 19);
	cout << char(219) << char(219) << char(219) << char(219) << char(219);
	gotoxy(59, 20);
	cout << " " << char(223) << char(219) << char(223);
	SCREEN_COLOR;
	int ki;
	const int SL = 4;
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
			loadmenu();
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
void CGame::pauseMenu(HANDLE handle, bool& isPause, bool nextlv)
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

			resetGame(nextlv);
			
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

//bool CGame::isCrash(Point pos) {
//		if (abs(cn.mX - pos.x) <=5 && abs(mY - pos.y) <= 5) {
//			return true;
//		}
//		return false;
//	}
//vector <Enemy*> enemyList = rowsData.listEnemy(); //enemyList = 0 
void CGame::Collide() {
	vector<Enemy*>ene = getVehicle();
	for (int i = 0; i < ene.size(); ++i) {
		//drawEnemies(enemyList[i]);
		if (ene[i])
		{
			if (cn.isCrash(ene[i]->getPos(), ene[i]->getShapeSize()) == true) {
				//if (!constantVar::!isMute) enemyList[i]->sound();
				//cn.killPlayer();
				//gotoxy(20, 20);
				if (!isMute)
					ene[i]->sound();
				cn.reduceLive();
				cn.eraseCorpse();
				cn.backToCheckPoint();
			
				//Destroy thread enemy;
				//bombEffect();
			}
		}
	}
}
void CGame::gameOver(HANDLE th1) {
	char choice;
	bombEffect();
	PlaySound(TEXT("smw_game_over.wav"), NULL, SND_ASYNC);
	gotoxy(20, 4);
	cout << "P L A Y  A G A I N? (y/n)";
	cin >> choice;
	if (choice == 'n'||choice=='N')
	{
		exitGame();
	}
	else if (choice == 'y' || choice == 'Y')
	{
		resetGame(0);
		cn.resetLives();
		//for (int i = 0; i < cn.getLives() * 3; ++i)
			//cout << char(222);
		cn.eraseCorpse();
		cn.backToCheckPoint();
		ResumeThread(th1);
	}
}

void CGame:: nextlevel(HANDLE handle,bool nextLevel) {
	
	resetGame(nextLevel);
	if (!isMute)
	{
		PlaySound(TEXT("smw_power-up.wav"), NULL, SND_ASYNC);
		//PlaySound(TEXT("zelda_13.wav"), NULL, SND_ASYNC);
	}
	cn.eraseCorpse();
	cn.backToCheckPoint();
}
void CGame::bombEffect()
{
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
	//index_x: 0 1
	//index_y: 0 1 2			0 0     0 1      1 0    1 1    0 3
	const char* tenmuc[3][2] = { {" E A S Y ", " H A R D " },{" O N ", " O F F "}, {" B A C K ",""} };
	system("cls");
	SCREEN_COLOR;
	gotoxy(menu_x, menu_y);
	cout << "M O D E";
	gotoxy(menu_x, menu_y + 2);
	cout << "S O U N D";
	gotoxy(menu_x + 17, menu_y);
	cout << "E A S Y   H A R D";
	gotoxy(menu_x + 17, menu_y + 2);
	cout << "O N       O F F";
	gotoxy(menu_x + 17, menu_y + 4);
	cout << "B A C K";

	//in dam luc khoi tao
	int dist_x = 5 + 5, dist_y = 2;
	gotoxy(menu_x + 17, menu_y);
	SETTING_BUT_CO;
	cout << tenmuc[0][0];
	gotoxy(menu_x + 17, menu_y + dist_y);
	SETTING_BUT_CO;
	cout << tenmuc[1][0];
	int chosen1[2] = { 0,0 }, chosen2[2] = {1,0};
	while (1)
	{
		gotoxy(menu_x + 17+chosen1[1]*dist_x, menu_y+chosen1[0]*dist_y);
		SETTING_BUT_CO;
		cout << tenmuc[chosen1[0]][chosen1[1]];
		gotoxy(menu_x + 17+chosen2[1]*dist_x, menu_y + chosen2[0]*dist_y);
		SETTING_BUT_CO;
		cout << tenmuc[chosen2[0]][chosen2[1]];

		ch = _getch();
		if (ch == 0)
			ch = _getch();
		if (ch == KEY_UP)
		{
			index_y--;
			//gap bien tren
			if (index_y < 0)
			{
				(!index_x) ? index_y = 2 : index_y = 1;
				gotoxy(menu_x + 17 + index_x * dist_x, menu_y);
				SCREEN_COLOR;
				_cprintf(tenmuc[0][index_x]);
				gotoxy(menu_x + 17 + index_x * dist_x, index_y * dist_y + menu_y);
				SETTING_BUT_CO;
				_cprintf(tenmuc[index_y][index_x]);
			}
			else
			{
				//xoa duoi
				gotoxy(menu_x + 17 + index_x * dist_x, (index_y + 1) * dist_y + menu_y);
				SCREEN_COLOR;
				_cprintf(tenmuc[index_y + 1][index_x]);
				//in hien tai
				gotoxy(menu_x + 17 + index_x * dist_x, index_y * dist_y + menu_y);
				SETTING_BUT_CO;
				_cprintf(tenmuc[index_y][index_x]);
			}
		}
		else if (ch == KEY_DOWN)
		{
			index_y++;
			int bienDuoi;
			(!index_x) ? bienDuoi = 2 : bienDuoi = 1;
			if (index_y > bienDuoi)
			{
				//xoa tren
				gotoxy(menu_x + 17 + index_x * dist_x, (index_y - 1) * dist_y + menu_y);
				SCREEN_COLOR;
				_cprintf(tenmuc[index_y - 1][index_x]);
				index_y = 0;
				gotoxy(menu_x + 17 + index_x * dist_x, index_y * dist_y + menu_y);
				SETTING_BUT_CO;
				_cprintf(tenmuc[index_y][index_x]);
			}
			else
			{
				//xoa tren
				gotoxy(menu_x + 17 + index_x * dist_x, (index_y - 1) * dist_y + menu_y);
				SCREEN_COLOR;
				_cprintf(tenmuc[index_y - 1][index_x]);
				//in hien tai
				gotoxy(menu_x + 17 + index_x * dist_x, index_y * dist_y + menu_y);
				SETTING_BUT_CO;
				_cprintf(tenmuc[index_y][index_x]);
			}
		}
		else if (ch == KEY_LEFT)
		{
			if (index_y != 2)index_x--;
			//bien trai
			if (index_x < 0)
			{
				//xoa trai
				gotoxy(menu_x + 17, index_y * dist_y + menu_y);
				SCREEN_COLOR;
				_cprintf(tenmuc[index_y][0]);
				index_x = 1;
				gotoxy(menu_x + 17 + index_x * dist_x, index_y * dist_y + menu_y);
				SETTING_BUT_CO;
				_cprintf(tenmuc[index_y][index_x]);
			}
			else
			{
				//xoa phai
				gotoxy(menu_x + 17 + (index_x + 1) * dist_x, (index_y)*dist_y + menu_y);
				SCREEN_COLOR;
				_cprintf(tenmuc[index_y][index_x + 1]);
				//in hien tai
				gotoxy(menu_x + 17 + index_x * dist_x, index_y * dist_y + menu_y);
				SETTING_BUT_CO;
				_cprintf(tenmuc[index_y][index_x]);
			}
		}
		else if (ch == KEY_RIGHT)
		{
			if (index_y != 2)index_x++;
			//bien phai
			if (index_x > 1)
			{
				//xoa phai
				gotoxy(menu_x + 17 + dist_x, index_y * dist_y + menu_y);
				SCREEN_COLOR;
				_cprintf(tenmuc[index_y][1]);
				index_x = 0;
				gotoxy(menu_x + 17 + index_x * dist_x, index_y * dist_y + menu_y);
				SETTING_BUT_CO;
				_cprintf(tenmuc[index_y][index_x]);
			}
			else
			{
				//xoa trai
				gotoxy(menu_x + 17, (index_y)*dist_y + menu_y);
				SCREEN_COLOR;
				_cprintf(tenmuc[index_y][0]);
				//in hien tai
				gotoxy(menu_x + 17 + index_x * dist_x, index_y * dist_y + menu_y);
				SETTING_BUT_CO;
				_cprintf(tenmuc[index_y][index_x]);
			}
		}

		//chinh mode
		else if ((ch == ENTER) && !index_y)
		{

			if (!index_x) {
				if (lane.getLevel().getMode())
					lane.switchMode();
			}
			//hard
			else {
				if (!lane.getLevel().getMode())
					lane.switchMode();
			}
			chosen1[0] =  index_y,chosen1[1]=index_x ;
		}
		else if ((ch == ENTER) && index_y == 1)
		{
			//on
			if (!index_x)
			{
			}
			//off
			else {
			}
			chosen2[0] = index_y, chosen2[1] = index_x;
		}
		//back
		else if ((ch == ENTER) && index_y == 2)
		{
			menu();
		}

	}

}



void CGame::loadmenu()
{
	system("cls");
	string load;
	cout << "Enter filname:";
	cin >> load;
	loadGame(load);
	SCREEN_COLOR;
	int keyPressed;
	bool isPause = true;
	bool nextLevel = false;
	drawGame(nextLevel);
	Sleep(3000);
	isPause = false;
	thread th1(&CGame::updatePosVehicle, this, nextLevel);
	HANDLE th1_handle = th1.native_handle();
	
	while (1)
	{
		//level up
		if (cn.isFinish())
		{
			nextLevel = true;
			//pauseGame(th1_handle);
			lane.levelUp();
			nextlevel(th1_handle, nextLevel);
			nextLevel = false;

		}
		//gameover
		if (cn.getLives() <= 0)
		{
			SuspendThread(th1_handle);
			system("cls");
			gameOver(th1_handle);
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
			pauseMenu(th1_handle, isPause, nextLevel);
		}
		else if (keyPressed == 'c' || keyPressed == 'C')
		{
			string save;
			pauseGame(th1_handle);
			cout << "Enter filename: ";
			cin >> save;

			saveGame(save);
			resumeGame(th1_handle);
			isPause = false;

		}
		else if (isPause == false)
		{
			//Collide();
			updatePosPeople(keyPressed, nextLevel);
			//Collide();
		}

	}
	if (th1.joinable())
		th1.join();
}

void CGame::drawDino(int x, int y, bool dir)
{
	char shape0[5][11], shape1[5][11];
	for (int i = 0; i < 4; ++i) shape1[0][i] = ' ';
	for (int i = 4; i < 10; ++i) shape1[0][i] = char(220);
	shape1[0][10] = ' ';
	for (int i = 0; i < 3; ++i) shape1[1][i] = shape1[2][i] = ' ';
	for (int i = 4; i < 9; ++i) shape1[1][i] = shape1[2][i] = shape1[3][i] = shape1[4][i] = char(219);
	shape1[1][8] = char(220);
	for (int i = 9; i < 11; ++i) shape1[1][i] = shape1[2][i] = char(223);
	shape1[3][1] = shape1[4][3] = char(219);
	shape1[3][9] = char(223), shape1[4][9] = char(220);
	for (int i = 1; i < 3; ++i) shape1[4][i] = char(223);
	shape1[3][2] = shape1[3][10] = shape1[4][10] = shape1[4][0] = ' ';
	shape1[1][3] = shape1[2][3] = shape1[3][0] = shape1[3][3] = char(174);

	for (int i = 7; i < 11; ++i) shape0[0][i] = ' ';
	for (int i = 1; i < 7; ++i) shape0[0][i] = char(220);
	shape0[0][0] = ' ';
	for (int i = 8; i < 11; ++i) shape0[1][i] = shape0[2][i] = ' ';
	for (int i = 2; i < 7; ++i) shape0[1][i] = shape0[2][i] = shape0[3][i] = shape0[4][i] = char(219);
	shape0[1][2] = char(220);
	for (int i = 0; i < 2; ++i) shape0[1][i] = shape0[2][i] = char(223);
	shape0[3][9] = shape0[4][7] = char(219);
	shape0[3][1] = char(223), shape0[4][1] = char(220);
	for (int i = 8; i < 10; ++i) shape0[4][i] = char(223);
	shape0[3][0] = shape0[3][8] = shape0[4][10] = shape0[4][0] = ' ';
	shape0[1][7] = shape0[2][7] = shape0[3][7] = shape0[3][10] = char(175);
	Point pos = { x,y };
	for (int i = 0; i < 5; ++i)
		for (int j = 0; j <11; ++j)
		{
			gotoxy(pos.x + j, pos.y + i);
				(dir)?printf("%c", shape1[i][j]): printf("%c", shape0[i][j]);
		}	
}
int CGame::randHeart() {
	int min = 10, max =50;
	int range = max - min + 1;
	int num = rand() % range + min;
	posHeart = num;
	return num;
}
void CGame::printHeart() {
	char a;
	a = 240;
	gotoxy(randHeart(), 12);
	cout << a;
}
void CGame::isIncreaseLive() {
	if (cn.isEatHeart(posHeart)) {
		if (!isMute)
			PlaySound(TEXT("Earn Points.wav"), NULL, SND_ASYNC);
		increaseLive();
	}
}
void CGame::increaseLive() {
	if (cn.getLives() < 5)
	{
		cn.plusLive();
		gotoxy(screenSize_H_right + 10, screenSize_V_top + 13);
		cout << "               ";
		gotoxy(screenSize_H_right + 10, screenSize_V_top + 13);
		for (int i = 0; i < cn.getLives() * 3; ++i)
			cout << char(222);
	}
}