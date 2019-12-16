#pragma once
#include"Library.h"

class CGame {
	CPEOPLE cn;
	int map[85][24];
	bool mode;	//0: easy, 1: hard
	Level level;
	Lane lane;
	string date;//for save load purpose
	bool isMute = false;
	static CGame* instance;
	CGame();
	~CGame(); // Hủy tài nguyên đã cấp phát
public:
	static mutex mtx;
	static CGame* getInstance() {
		if (!instance)
			instance = new CGame;
		return instance;
	}
	//CGame(); //Chuẩn bị dữ liệu cho tất cả các đối tượng
	void drawGame(bool); //Thực hiện vẽ trò chơi ra màn hình sau khi có dữ liệu
	
	vector<Enemy*> getVehicle();//Lấy danh sách các xe

	//CANIMAL* getAnimal(); //Lấy danh sách các thú
	void resetGame(bool); // Thực hiện thiết lập lại toàn bộ dữ liệu như lúc đầu
	void exitGame(); // Thực hiện thoát Thread
	void gamePlay(); // Thực hiện bắt đầu vào trò chơi
	void loadGame(string load); // Thực hiện tải lại trò chơi đã lưu
	void saveGame(string save); // Thực hiện lưu lại dữ liệu trò chơi
	void pauseGame(HANDLE); // Tạm dừng Thread
	void resumeGame(HANDLE); //Quay lai Thread
	void updatePosPeople(char,bool); //Thực hiện điều khiển di chuyển của CPEOPLE
	void updatePosVehicle(bool); //Thực hiện cho Truck & Car di chuyển
	void updatePosAnimal();//Thực hiện cho CDINAUSOR & CBird di chuyển
	//MENU
	void titleMenu();
	string getFileContents(std::ifstream& File);
	void menu();
	void pauseMenu(HANDLE, bool&,bool);
	void settingMenu();
	//For arrayTesting
	bool exportMap(const char* a);
	Point peoplePos();
	void Collide();
	void gameOver(HANDLE);
	void nextlevel(HANDLE,bool);
	void bombEffect();
	
	//LOADGAMEMENU
	void loadmenu();
	vector<string> getAllFilename(const string& name);
	string getdate() { return date; };
	//DRAW DINO
	void drawDino(int, int, bool);

	//eat Live
	int randHeart();
	void printHeart();
	void isIncreaseLive();
	void increaseLive();
	//animation
	void printAnimation();

};
