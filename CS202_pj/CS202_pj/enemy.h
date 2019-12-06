#pragma once
#include"Library.h"

const int MAXLEVEL = 5;
const int MAXCAR = 5;
const int MAXTRUCK = 4;
const int MAXSPEED = 100;		//1s

class CTRAFFIC {
	bool greenLight;
	static int numTraffic;
	Point pos;
	const int prob[2] = {75,75};
public:
	CTRAFFIC(Point p) { ++numTraffic; greenLight = true; pos = p; gotoxy(pos.x, pos.y);  drawTrafficLight(); }
	CTRAFFIC(const CTRAFFIC& src) {
		++numTraffic; greenLight = src.greenLight; pos = src.pos;
		gotoxy(pos.x, pos.y); drawTrafficLight();
	}
	void drawTrafficLight() { (greenLight) ? cout << char(220) : cout << char(223); }
	void green() {
		greenLight = true;
		gotoxy(pos.x, pos.y), drawTrafficLight();
	}
	void red() {
		int a = 0, b = 400;
		srand(time(NULL));
		int rRedTime = rand() % (b - a + 1) + a;	//tu a den b

		greenLight = false; gotoxy(pos.x, pos.y), drawTrafficLight();
		//Sleep(500);
	}
	void toggle(int i) {
		srand(time(NULL));
		greenLight = (rand() % 100) < prob[i];
		if (!greenLight)red(); else green();
	}

	~CTRAFFIC() { --numTraffic; }

	bool isGreen() { return greenLight; }
};
class CVEHICLE
{
private:

protected:
	Point pos;
	void setPos(Point p) { pos = p; };
public:
	CVEHICLE(Point p) { pos = p; }
	virtual void Move() = 0;
	virtual void drawVeh() = 0;
	virtual void pause() = 0;
};

class CCAR : public CVEHICLE {
private:
	bool dir;			//0: left, 1: right
	//int spd;
	static int numCar;	//max=5
	const int bk = 4;
	const char shape[3][9] =
	
	{ ' ',' ','_','_','_','_',' ',' ',' ',
		' ','/','|',' ',' ','|','\\','_',' ',
		'|','_','_','O','_','_','O','_','|' };
public:
	CCAR(Point p, bool d) :CVEHICLE(p) {
		dir = d;
	}
	void Move();
	void pause();

	void drawVeh() {
		//   _____     3-9
		//  /| x |\ 
		// |_O___O_|
		// 123456789
		gotoxy(pos.x - bk, pos.y - 1);
		cout << "  _____  ";
		gotoxy(pos.x - bk, pos.y);
		cout << " /|   |\\ ";
		gotoxy(pos.x - bk, pos.y + 1);
		cout << "|_O___O_|";
		//setPos(pos);

		/*int left=5, right = 100;
			for (int r = 0; r < 3; ++r)
				for (int c = 0; c < 9; ++c) {
					int y = pos.y + r, x = pos.x + c;
					if (left <= x && x <= right)
					{
						gotoxy(x, y), cout << shape[r][c];
					}
				}*/
	}
};
class CTRUCK : public CVEHICLE {
	bool dir;
	const int bk = 6;
public:
	CTRUCK(Point p, bool d) :CVEHICLE(p) {
		dir = d;
	}void Move();
	void drawVeh() {
		//  _________   3-13
		// |///////|_\_ 
		// |_/O____O\__|
		//    _________   
		//  _/_|/x/////| 
		// |__/O____O\_|
		// 1234567890123
		if (dir) {
			gotoxy(pos.x-bk, pos.y-1);
			cout << " _________   ";
			gotoxy(pos.x-bk, pos.y );
			cout << "|///////|_\\_ ";
			gotoxy(pos.x-bk, pos.y +1);
			cout << "|_/O____O\\__|";
		}
		else {
			gotoxy(pos.x-bk, pos.y-1);
			cout << "   _________ ";
			gotoxy(pos.x-bk, pos.y);
			cout << " _/_|///////|";
			gotoxy(pos.x-bk, pos.y + 1);
			cout << "|__/O____O\\_|";
		}

	}
	void pause();

};
//----------------CANIMAL-----------------
class CANIMAL {
	int mX, mY;
public:
	//virtual void Move(int, int);
	//virtual void Tell() = 0;
};
class CDINAUSOR : public CANIMAL {
private:
public:
	void Move(int, int);
};

class CBIRD : public CANIMAL {
};

//cgame, drawgame, getvehicle,  start, updatePos, setting -> set so xe, toc do, level
class VEHLANE {
	CTRAFFIC* t;	//so den gthong
	CVEHICLE* v[9];		//so xe - 5 car 4 truck
	int level;			//1-5

	const int numCarLVL[5] = { 2,3,4,4,5 };
	const int numTruckLVL[5] = { 2,2,3,4,4 };

	const int speed[5] = { 150,100,100,50,30 };
public:
	VEHLANE(int l) {
		level = l;								//tu 1->5
		int distLane = 3, minDistCar = 6;		//distance btw 2 lane, min distance btw 2 car
		//khoi tao den giao thong
		Point pT1 = { 85 + 2,6 }, pT2 = { 85 + 2,10 }, pC = { 4 + 4,2 + 2 + 1 }, pTruck = {4+6,10};
		t = new CTRAFFIC[2]{ pT1,pT2 };				//default 2 lan xe -> 2 den gthong
		//khoi tao xe hoi
		//int a = 0, b = 1;
		//srand(time(NULL));
		//int rPos = rand() % (b - a + 1) + a;	//tu a den b
		for (int i = 0; i < numCarLVL[level - 1]; ++i)
			v[i] = new CCAR(pC, 1), v[i]->drawVeh(),pC.x += 15;
		for (int i = numCarLVL[level - 1]; i < MAXCAR; ++i)
			v[i] = NULL;
		for (int i = MAXCAR; i < MAXCAR+numTruckLVL[level-1]; ++i)
			v[i] = new CTRUCK(pTruck, 0), v[i]->drawVeh(), pTruck.x += 17;
		for (int i = numTruckLVL[level-1]; i < MAXTRUCK; ++i)
			v[i] = NULL;
	}
	void updatePosVehicle()
	{
		while (1)
		{
			if (t[0].isGreen())
				for (int i = 0; i < numCarLVL[level - 1]; ++i)
					v[i]->Move();
			if (t[1].isGreen())
				for (int i = MAXCAR; i < MAXCAR + numTruckLVL[level - 1]; ++i)
					v[i]->Move();
			Sleep(speed[level - 1]);
			t[0].toggle(1); t[1].toggle(0);
		}
	}

		~VEHLANE() { for (int i = 0; i < 9; ++i) delete v[i], v[i] = NULL; delete[] t; t = NULL; }
};
//	//VEHLANE() {
	//
	//		/*int c1pos = 5; Point veh1 = { c1pos,c1pos };
	//		c = new CCAR[numVeh];
	//		for (int r = 0; r < numVeh; ++r)
	//		{
	//			switch (numVeh) {
	//			case 2:
	//				c[r].drawVeh(veh1);
	//				veh1.x += 20;
	//				break;
	//				/*
	//							case 3:
	//								c[r]->drawVeh({}), break;
	//							case 4:
	//								c[r]->drawVeh({}), break;
	//							case 5:
	//								c[r]->drawVeh({}), break;
	//							case 6:
	//								c[r]->drawVeh({}), break;
	//					*/
	//			}
	//			/*}
	//			veh1.x=c1pos, veh1.y += 6;
	//			for (int r = 0; r < numVeh; ++r)
	//			{
	//				switch (numVeh) {
	//				case 2:
	//					c[r].drawVeh(veh1);
	//					veh1.x += 20;
	//					break;
	//
	//								case 3:
	//									c[r]->drawVeh({}), break;
	//								case 4:
	//									c[r]->drawVeh({}), break;
	//								case 5:
	//									c[r]->drawVeh({}), break;
	//								case 6:
	//									c[r]->drawVeh({}), break;
	//					
	//		}
	////	}
	//	*/
		//CVEHICLE* getVehicle() { return c; }//Lấy danh sách các xe

		//Thực hiện cho CTRUCK & CCAR di chuyển

