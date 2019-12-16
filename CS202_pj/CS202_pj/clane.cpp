#include "Library.h"

Lane::Lane()
{
	initLane();
}

Lane::~Lane()
{
	for (int i = 0; i < car.size(); ++i)
		delete car[i], bird[i], car[i] = NULL, bird[i] = NULL;
	for (int i = 0; i < truck.size(); ++i)
		delete truck[i], dino[i], truck[i] = NULL, dino[i] = NULL;
	for (int i = 0; i < traf.size(); ++i)
		delete traf[i], traf[i] = NULL;
}

void Lane::initLane()
{
	const int carNum = 6;
	/*int mode = 1;
	int numCar, numTruck, distCar, distTruck;
	if (!mode) {
		numCar = lev.getNumCar();
		numTruck = lev.getNumCar();
		distCar = lev.getDistCar();
		distTruck = lev.getDistTruck();
	}
	else {
		numCar = lev.getNumCar();
		numTruck = lev.getNumCar();
		distCar = lev.getDistCar();
		distTruck = lev.getDistTruck();
	}*/
	srand(time(NULL));
	int topLeft = 2;
	Point pTra = { screenSize_H_right + 2,topLeft + 4 }
	, pC = { 5, topLeft + 3 }, pT = { 5,pC.y + 4 };

	count = 0;
	stopCount = 0, stopCar = -1;

	traf = vector<Traffic*>(4, NULL);
	for (int i = 0; i < 4; ++i)
		traf[i] = new Traffic(pTra), pTra.y += 4;

	//dir = rand() % 2;
	car = vector<Enemy*>(carNum, NULL);
	for (int i = 0; i < carNum; ++i)

		car[i]=new Car(pC,0), pC.x += lev.getDistCar();
	truck = vector<Enemy*>(carNum, NULL);
	//dir = rand() % 2;

	for (int i = 0; i < carNum; ++i)
		truck[i] = new Truck(pT, 1), pT.x += lev.getDistTruck();

	pC = { 5, pT.y + 4 }, pT = { 5, pC.y + 4 };
	//dir = rand() % 2;
	bird = vector<Enemy*>(carNum, NULL);
	for (int i = 0; i < carNum; ++i)
		bird[i] = new Bird(pC, 0), pC.x += lev.getDistCar();
	//dir = rand() % 2;
	dino = vector<Enemy*>(carNum, NULL);
	for (int i = 0; i < carNum; ++i)
		dino[i] = new Dinosaur(pT, 1), pT.x += lev.getDistTruck();

}


void Lane::updateTraffic()
{		
	//traffic light
	for (int i = 0; i < 4; i++)
	{
		traf[i] ->green();
	}
	if (stopCar != -1) {
		traf[stopCar] ->red();
	}
	for (int i = 0; i < 4; i++)
	{
		traf[i]->drawTrafficLight();
	}

	//Sleep(5);
	//if ((!greenLight && (rand() % 8 == 0))
	//	|| (greenLight && (rand() % 15 == 0)) || (t == 0)) {
	//	toggleLight();
	//}
}

void Lane::drawLane(bool lvUp)
{ 
		for (int i = 0; i < lev.getNumCar(); ++i)
			car[i]->drawEne(lvUp), bird[i]->drawEne(lvUp);

		for (int i = 0; i < lev.getNumTruck(); ++i)
			truck[i]->drawEne(lvUp), dino[i]->drawEne(lvUp);
	
}

void Lane::updateLane(bool lvUp) {
	count++;
	if (count % lev.getSpeed() == 0)
	{
		if (stopCar != 0)
			for (int i = 0; i < lev.getNumCar(); i++)
				car[i]->moveEne(lvUp), car[i]->drawEne(lvUp);
		if (stopCar != 1)
			for (int i = 0; i < lev.getNumTruck(); i++)
				truck[i]->moveEne(lvUp), truck[i]->drawEne(lvUp);
		if (stopCar != 2)
			for (int i = 0; i < lev.getNumCar(); i++)
				bird[i]->moveEne(lvUp), bird[i]->drawEne(lvUp);
		if (stopCar != 3)
			for (int i = 0; i < lev.getNumTruck(); i++)
				dino[i]->moveEne(lvUp), dino[i]->drawEne(lvUp);
	}
	//	Tam dung xe 
	if (count == 2000000000)count = 0;
	stopCount++;
	if (stopCount == 100) stopCar = rand() % 4;
	if (stopCount == 2000) {
		stopCount = 0;
		stopCar = -1;
	}
	updateTraffic();
}

bool Lane::levelUp()
{
	if (lev.levelUp()) {
		for (int i = 0; i < car.size(); ++i)
			delete car[i], bird[i], car[i] = NULL, bird[i] = NULL;
		for (int i = 0; i < truck.size(); ++i)
			delete truck[i], dino[i], truck[i] = NULL, dino[i] = NULL;
		for (int i = 0; i < traf.size(); ++i)
			delete traf[i], traf[i] = NULL;
		initLane();
		return true;
	}
	return false;
}


Level::Level()
{
	level = 1;
	mode = 1;
	//maxSpd = diff - level*2, minSpd=diff-level;
}

bool Level::levelUp()
{
	if (level < maxLevel) {
		++level;
		
		return true;
	}
}

int Level::getLevel()
{
	return level;
}

int Level::getSpeed()
{
	if (mode)
		return ezSpeed[level - 1];
	else
		return harSpeed[level - 1];
}

int Level::getNumCar()
{
	return numCar[level-1];
}

int Level::getNumTruck()
{
	return numTruck[level-1];
}

int Level::getDistCar()
{
	return distCar[level-1];
}
int Level::getDistTruck()
{
	return distTruck[level - 1];
}
void Level::switchMode()
{
	mode = !mode;
}
//Level* Level::createLevel(int mode)
//{
//	if (mode)
//		return new EzLevel(); 
//	else
//		return new HarLevel();
//}
//int Level::getMaxSpeed()
//{
//	return maxSpd;
//}
//
//int Level::getMinSpeed()
//{
//	return minSpd;
//}

//Enemy* Level::getNewEnemy(Point p, int type)
//{
//	Enemy* ene = NULL;
//	if (2 <= type && type <= 5&&numEne!=maxEne) {
//		++numEne;
//
//		switch (type) {
//		case 2:
//			ene = new Car(p);
//			break;
//		/*case 3:
//			ene = new Truck(p);
//			break;*/
//		/*case 4:
//			ene = new Bird(p);
//			break;
//		case 5:
//			ene = new Dinosaur(p);
//			break;*/
//		}
//
//	}
//	return ene;
//}
//void Lane::deleteOldEnemy(Point pos, ShapeSize s)
//
//{
//	int l = 4, r = screenSize_H;
//	if (pos.y == 4) return;
//	if (pos.y > r) return;
//	for (int i = 0; i < s.h; ++i) {
//		for (int j = max(1, pos.y); j <= min(r, pos.y + s.w - 1); ++j) {
//			gotoxy(pos.y + j, pos.x + i);
//			cout << ' ';
//		}
//	}
//}
//
//bool Lane::printNewEnemy(Point pos, char** shape, ShapeSize s)
//{
//	int l = 4, r = screenSize_H;
//	//out of barrier
//	if (pos.y == l) return 0;
//	if (pos.y > r) return 0;
//	for (int i = 0; i < s.h; ++i) {
//		for (int j = max(1, pos.y); j <= min(r, pos.y + s.w - 1); ++j) {
//			gotoxy(pos.y + j, pos.x + i);
//			cout << shape[i][j - max(1, pos.y)];
//		}
//	}
//	return 1;
//}

//void Lane::updatePosEnemy(int t)
//{
//	//if (((t % speed) != 0) && t != 0) 
//		//return nDelete; //test
//
//	//if (redLight) return nDelete;
//
//	vector <Enemy*> newEnemy;
//	newEnemy.reserve(100);
//	for (int i = 0; i < (int)ene.size(); ++i) {
//		Enemy* curEne = ene[i];
//
//		//thong so can thay doi
//		int dy = -1;
//		if (dir) dy = 1;
//		deleteOldEnemy(curEne->getPos(), curEne->getShapeSize());
//		curEne->setPos({ 0, dy });
//		// Print Enemy
//		bool canPrint = printNewEnemy(curEne->getPos(), curEne->getShape(), curEne->getShapeSize());
//		/*if (!canPrint) {
//			curEne->goOutMap();
//			++nDelete;
//		}
//		if (curEnemy->isOutOfMap()) {
//			delete curEnemy;
//		}*/
//		if (!canPrint)delete curEne;
//		else {
//			newEnemy.push_back(curEne);
//		}
//	}
//	ene = newEnemy;
//	//return nDelete;
//}


