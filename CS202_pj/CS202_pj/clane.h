#pragma once
#include"Library.h"
class Level
{
private:
	int level;
	bool mode;
	const int numCar[3] = { 2,3,3 };
	const int numTruck[3] = { 2,2,3 };

	const int distCar[3] = {50,30,20};
	const int distTruck[3] = {40,30,30};
	const int ezSpeed[3] = { 100,100,100 };
	const int harSpeed[3] = { 80,80,80 };
	const int maxLevel = 3;
	//int minSpd, maxSpd;
	//int maxEne, numEne;
	//int nRow;
	//  int nColumn;
public:
	Level();
	Level(int& level, int& mode) { this->level = level, this->mode = mode; };
	Level(const Level& l) { level = l.level, mode = l.mode; };
	Level& operator=(const Level& l) { level = l.level, mode = l.mode; return* this; }
	bool levelUp();
	int getMode() { return mode; };
	int getLevel();

	int getSpeed();
	int getNumCar();
	int getNumTruck();

	int getDistCar();
	int getDistTruck();
	void switchMode();
	static Level* createLevel(int mode);
};
//class EzLevel:public Level {
//	const int ezSpeed[3] = { 200,200,100 };
//public:
//	EzLevel() :Level() {};
//	virtual int getSpeed() { return ezSpeed[getLevel()-1]; }
//};
//class HarLevel :public Level {
//	const int harSpeed[3] = { 1000,40,30 };
//public:
//	HarLevel() :Level() {};
//	virtual int getSpeed() { return harSpeed[getLevel() - 1]; }
//};
//-------------------------------------------------------
class Lane {
	vector<Enemy*> car;
	vector<Enemy*> truck;
	vector<Enemy*> bird;
	vector<Enemy*> dino;
	vector<Traffic*>traf;
//	bool dir;		//0: left, 1: right
	Level lev;
	int count, stopCount;
	int stopCar;

	//int curLaneRow;
public:
	Lane();
	
	Lane(Level& lev);
	~Lane();
	void initLane();
	void updateTraffic();
	void drawLane(bool);
	void updateLane(bool);
	
	vector<Enemy*>getCar() { return car; }

	vector<Enemy*>getTruck() { return truck; }

	vector<Enemy*>getBird() { return bird; }

	vector<Enemy*>getDino() { return dino; }
	Level getLevel() { return lev; }
	bool levelUp();
	Point  getVehiclePoint();
	void updatePosEnemy(int t);
	
	//bool drawlane(bool);
	//void deleteOldEnemy(Point pos, ShapeSize s);
	//bool printNewEnemy(Point pos, char** shape, ShapeSize s);	//return if printable
	
};


//void initializeNewState() {
//		/*player.~cPlayer();
//		new(&player) cPlayer();
//		rowsData.~cRows();
//		new(&rowsData) cRows();*/
//
//		int padding[10];
//		for (int i = 0; i < 10; ++i) {
//			padding[i] = 0;
//			int speed = rand() % (level.getMinSpeed() - level.getMaxSpeed() + 1) + level.getMaxSpeed();
//			bool direction = rand() % 2;
//			bool greenLight = rand() % 2;
//			rowsData.pushRow(new cOneRow(speed, direction, greenLight, (i * 3) + 1));
//		}
//
//		Enemy* newEnemy;
//		Point pos;
//		int tryCount = 10000;
//		while (tryCount--) {
//			int rRow = (rand() % 9) + 1;
//			padding[rRow] += (rand() % 20) + 9;
//			pos = Point((rRow * 3) + 1, padding[rRow]);
//			newEnemy = level.randNewEnemy(pos);
//			if (!newEnemy) break;
//			if (!rowsData.pushEnemy(rRow, newEnemy)) {
//				level.decnumEne(1);
//				delete newEnemy;
//			};
//		}
//		Sleep(200);
//		rowsData.moveToNextState(0);
//	}
//	void cMap::randomNextState() {
//		srand(time(NULL));
//		//int t = rand(); // this will be get from global clock
//		Enemy* newEnemy;
//		Point pos;
//		int tryCount = 10000;
//		while (tryCount--) {
//			int rRow = (rand() % 9) + 1;
//			pos = Point((rRow * 3) + 1, 4);
//			newEnemy = level.randNewEnemy(pos);
//			if (!newEnemy) break;
//			if (!rowsData.pushEnemy(rRow, newEnemy)) {
//				level.decnumEne(1);
//				delete newEnemy;
//			};
//		}
//		++t;
//		int tmp = rowsData.moveToNextState(t);
//		level.decnumEne(tmp);
//		drawMap();
//	}
