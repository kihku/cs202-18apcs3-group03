#include "clane.h"

Lane::Lane()
{
	srand(time(NULL));
	int topLeft = 2;
	Point pTra = {screenSize_H+2,topLeft+4}
	, pC = { 5, topLeft + 3 }, pT = { 5,pC.y + 4 };
	
	count = 0;
	stopCount = 0, stopCar = -1;
	
	
	traf=vector<Traffic*>(4, NULL);
	for (int i = 0; i < 4; ++i)
		traf[i]=new Traffic(pTra),pTra.y+=4;
	
	dir = rand() % 2;
	car = vector<Car*>(6, NULL);
	for (int i = 0; i < lev.getNumCar(); ++i)
		car[i]=new Car(pC,dir), pC.x += 15;
	truck = vector<Truck*>(6, NULL);
	dir = rand() % 2;

	for (int i = 0; i < lev.getNumTruck(); ++i)
		truck[i] = new Truck(pT, dir), pT.x += 20;

	pC = { 5, pT.y + 4 }, pT = { 5, pC.y + 4 };
	dir = rand() % 2;
	bird = vector<Bird*>(6, NULL);
	for (int i = 0; i < lev.getNumCar(); ++i)
		bird[i] = new Bird(pC, dir), pC.x += 15;
	dir = rand() % 2;
	dino = vector<Dinosaur*>(6, NULL);
	for (int i = 0; i < lev.getNumTruck(); ++i)
		dino[i] = new Dinosaur(pT, dir), pT.x += 20;

	
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

Lane::Lane(bool d, bool g, int s, int row)
{
	dir = d;// curLaneRow = row;
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

void Lane::updateLane() {
	count++;
	if (count %lev.getEzSpeed() == 0)
		if (stopCar != 0)
			for (int i = 0; i < lev.getNumCar(); i++)
				car[i]->moveEne(), car[i]->drawEne();

	if (count % lev.getEzSpeed() == 0)
		if (stopCar != 1)
			for (int i = 0; i < lev.getNumTruck(); i++)
				truck[i]->moveEne(), truck[i]->drawEne();

	if (count % lev.getEzSpeed() == 0)
		if (stopCar != 2)
			for (int i = 0; i < lev.getNumCar(); i++)
				bird[i]->moveEne(), bird[i]->drawEne();

	if (count % lev.getEzSpeed() == 0)
		if (stopCar != 3)
			for (int i = 0; i < lev.getNumTruck(); i++)
				dino[i]->moveEne(), dino[i]->drawEne();
	//	Tam dung xe 
	if (count == 2000000000)count = 0;
	stopCount++;
	if (stopCount == 500) stopCar = rand() % 3;
	if (stopCount == 3000) {
		stopCount = 0;
		stopCar = -1;
	}
	updateTraffic();
}


Level::Level()
{
	level = 5;

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

int Level::getEzSpeed()
{
	return ezSpeed[level-1];
}

int Level::getNumCar()
{
	return numCar[level-1];
}

int Level::getNumTruck()
{
	return numTruck[level-1];
}

int Level::getMaxSpeed()
{
	return maxSpd;
}

int Level::getMinSpeed()
{
	return minSpd;
}

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


