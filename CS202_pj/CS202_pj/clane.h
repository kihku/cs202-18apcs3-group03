#pragma once
#include"Library.h"
using namespace std;
class Level
{
private:
	int level;

	const int ezSpeed[5] = {200,200,100,100,20};
	
	const int harSpeed[5] = { 50,50,40,30,20 };
	
	const int numCar[5] = { 2,3,4,4,4 };
	const int numTruck[5] = { 2,2,3,4,4 };
	const int maxEne[4] = {6,5,5,5};
	
	const int maxLevel = 5;
	const int diff = 50;
	int minSpd, maxSpd;
	//int maxEne, numEne;
	//int nRow;
	//  int nColumn;
public:
	Level();
	
	bool levelUp();

	int getLevel();

	int getEzSpeed();

	int getNumCar();
	int getNumTruck();

	int getMaxSpeed();
	int getMinSpeed();

	Enemy* getNewEnemy(Point p, int type);
	// Level(int level, int numEne);

	//void decnumEne(int d);
	//Enemy* randNewEnemy(cPosition pos);
};
//-------------------------------------------------------
class Lane {

	vector<Car*> car;
	vector<Truck*> truck;
	vector<Bird*> bird;
	vector<Dinosaur*> dino;
	vector<Traffic*>traf;
	bool dir;		//0: left, 1: right
	Level lev;
	int count, stopCount;
	int stopCar;
	//int curLaneRow;
public:
	Lane();
	~Lane();
	Lane(bool d, bool g, int s, int c);
	void updateTraffic();
	
	void updateLane();
	
	Point  getVehiclePoint();
	void updatePosEnemy(int t);
	
	bool drawEne();
	void deleteOldEnemy(Point pos, ShapeSize s);
	bool printNewEnemy(Point pos, char** shape, ShapeSize s);	//return if printable
	
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
