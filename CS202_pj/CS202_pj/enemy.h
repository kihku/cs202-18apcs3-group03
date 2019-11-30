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
public:
	CTRAFFIC(Point p) { ++numTraffic; greenLight = true; pos = p;gotoxy(pos.x, pos.y);  drawTrafficLight(); }
	CTRAFFIC(const CTRAFFIC& src) {
		++numTraffic; greenLight = src.greenLight; pos = src.pos;
		gotoxy(pos.x, pos.y); drawTrafficLight();
	}
	void drawTrafficLight() { (greenLight) ? cout << char(220) : cout << char(223); }
	void green() {
		greenLight = true;
		gotoxy(pos.x, pos.y); drawTrafficLight();
	}
	void isRed() {
		int a = 0, b = 300;
		srand(time(NULL));
		int rRed = rand() % (b - a + 1) + a;	//tu a den b

		greenLight = false; gotoxy(pos.x, pos.y); drawTrafficLight();
		Sleep(rRed);
	}
	
	~CTRAFFIC() { --numTraffic; }

	bool isGreen() { return greenLight; }
};
class CVEHICLE
{
private:

protected:
	Point pos;
	void setPos(Point p) { pos=p; };
public:
	CVEHICLE() {  }
	virtual void Move(int) = 0;
	virtual void drawVeh(Point pos) = 0;
	virtual void pause()=0;
};

class CCAR : public CVEHICLE {
private:
	bool dir;			//0: left, 1: right
	static int numCar;	//max=5

	const char shape[3][9] = { ' ',' ','_','_','_','_',' ',' ',' ',
		' ','/','|',' ',' ','|','\\','_',' ',
		'|','_','_','O','_','_','O','_','|' };
public:
	void Move(int spd);
	void pause();

	void drawVeh(Point pos){
	//   _____     3-9
	//  /|   |\ 
	// |_O___O_|
		this->pos = pos;
		gotoxy(pos.x, pos.y);
		cout << "  _____  ";
		gotoxy(pos.x, pos.y + 1);
		cout << " /|   |\\ ";
		gotoxy(pos.x, pos.y + 2);
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
class CTRUCK: public CVEHICLE {
	bool dir;
public:
	void Move(int, int);
	void drawVeh(Point pos) {
	//  _________   3-13
	// |///////|_\_ 
	// |_/O____O\__|
	//    _________   
	//  _/_|///////| 
	// |__/O____O\_|
		if (dir) {
			gotoxy(pos.x, pos.y);
			cout << " _________   ";
			gotoxy(pos.x, pos.y + 1);
			cout << "|///////|_\\_ ";
			gotoxy(pos.x, pos.y + 2);
			cout << "|_/O____O\\__|";
		}
		else {
			gotoxy(pos.x, pos.y);
			cout << "   _________ ";
			gotoxy(pos.x, pos.y + 1);
			cout << " _/_|///////|";
			gotoxy(pos.x, pos.y + 2);
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
	int level;

	const int numCarLVL[5] = { 2,3,4,4,5 };
	const int speed[5] = { 150,100,100,50,30 };
public:
	VEHLANE(int l) {
		level = l;								//tu 1->5
		int distLane = 3, minDistCar = 6;		//distance btw 2 lane, min distance btw 2 car
		//khoi tao den giao thong
		Point pT1 = { 85 + 2,2 + 3 + 2 }, pT2 = { 85 + 2,2 + 3 + 3 + 2 + 2 };
		t = new CTRAFFIC[2]{ pT1,pT2 };				//default 2 lan xe -> 2 den gthong
		//khoi tao xe hoi
		for (int i = 0; i < numCarLVL[l - 1]; ++i)
			v[i] = new CCAR();
		for (int i = numCarLVL[l - 1]; i < MAXCAR; ++i)
			v[i] = NULL;

		Point pos = { 5,5 };
		int a = 0, b = 1;
		srand(time(NULL));
		int rPos = rand() % (b - a + 1) + a;	//tu a den b

		for (int i = 0; i < numCarLVL[l - 1]; ++i)
			v[i]->drawVeh({ pos.x + rPos + i * 6,6 });
	}
	void updatePosVehicle()
	{
		while (t[0].isGreen())
			for (int i = 0; i < numCarLVL[level-1]; ++i)
				v[i]->Move(speed[level]);

		for (int i = numCarLVL[level - 1]; i < MAXCAR; ++i)
			v[i]->pause();
	}

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

	~VEHLANE() { for (int i = 0; i < 8;++i) delete v[i], v[i]=NULL; delete[] t; t = NULL; }
};

