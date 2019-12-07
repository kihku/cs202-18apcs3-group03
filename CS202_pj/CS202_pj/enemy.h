#pragma once
#include"Library.h"

class Enemy {
	Point pos;
	bool dir;
protected:
	const int l = 4, r = 84 ;
public:

	Enemy(Point p, bool d) { pos = p, dir = d; }

	Point getPos() { return pos; }

	bool getDir() { return dir; }
	
	virtual ShapeSize getShapeSize()=0;	//return w,h of shape

	virtual int getType() = 0;

	void setPos(Point p) { pos = p; }

	virtual void moveEne() = 0;
	virtual void drawEne() = 0;
	//virtual char** getShape() = 0;
};

class Traffic {
	Point pos;
	bool greenLight;
	static int numTraffic;
public:
	Traffic(Point p);
	Traffic(const Traffic& src);
	void drawTrafficLight();
	void green();
	void red();
	void toggle(int i);

	~Traffic();

	bool isGreen();
};

		//   _____     3-9
		//  /| x |\ 
		// |_O___O_|
		// 123456789
class Car : public Enemy {
private:
	const char shape[3][9] = { {' ',' ','_','_','_','_','_',' ',' '},
	{' ','/','|',' ',' ',' ','|','\\',' ' },
	{'|','_','O','_','_','_','O','_','|' } };
const ShapeSize ss = {9,3};
public:
	Car(Point p,bool d);

	virtual ShapeSize getShapeSize();	//return w,h of shape
	
	virtual int getType();

	virtual void moveEne();

	virtual void drawEne();
	//void drawVeh() {
	//void Move();
	//void pause();
	//virtual char** getShape();		//return array of shape

};	

		//  _________   3-13
		// |///////|_\_ 
		// |_/O____O\__|
		//    _________   
		//  _/_|/x/////| 
		// |__/O____O\_|
		// 1234567890123

class Truck : public Enemy {
	char shape1[3][13] = { {' ','_','_','_','_','_','_','_','_','_',' ',' ',' '},
	{ '|','/','/','/','/','/','/','/','|','_','\\','_',' ' },
	{ '|','_','/','O','_','_','_','_','O','\\','_','_','|' } };
	char shape0[3][13] = { {' ',' ',' ','_','_','_','_','_','_','_','_','_',' '},
	{' ','_','/','_','|','/','/','/','/','/','/','/','|'},
	{'|','_','_','/','O','_','_','_','_','O','\\','_','|'} };

	const ShapeSize ss = { 13,3 };
public:
	Truck(Point p, bool d);

	virtual ShapeSize getShapeSize();	//return w,h of shape

	virtual int getType() ;

	virtual void moveEne();

	virtual void drawEne();
	//virtual char** getShape() ;		//return array of shape
};

	//   ▄▄▄▄▄▄	   		     ▄▄▄▄▄▄      
	//  ▀▀▄████►   		    ◄████▄▀▀     
	//	▀▀█████►   		    ◄█████▀▀   
	//	 ▀█████► █►		 ◄█ ◄█████▀     
	//	 ▄██████▀▀        ▀▀██████▄    
 	//  12345678901
class Dinosaur : public Enemy {
private:
	char shape1[5][11];
	char shape0[5][11];
	const ShapeSize ss = { 11,5 };
public:
	Dinosaur(Point p, bool d);

	  virtual ShapeSize getShapeSize();	//return w,h of shape

	  virtual int getType();

	  virtual void moveEne();

	  virtual void drawEne();
};

	//    ,,,       ,,,             
	//  (   .)>   <(.   )                
	//  /_<),)     (,(>_\                                  
	//  1234567
class Bird : public Enemy {
	const char shape1[3][7] = { {' ',' ',',',',',',',' ',' '},
	{'(',' ',' ',' ','.',')','>' },
	{ '/','_','<',')',',',')',' '} };
	const char shape0[3][7] = { {' ',' ',',',',',',',' ',' '},
	{ '<','(','.',' ',' ',' ',')' },
	{ ' ','(',',','(','>','_','\\'} };
	const ShapeSize ss = { 7,3 };
public:
	Bird(Point p, bool d) :Enemy(p, d) {};

	virtual ShapeSize getShapeSize();	//return w,h of shape

	virtual int getType();

	virtual void moveEne();

	virtual void drawEne();
};

/////////////////////////////////////LANE//////////////////////////


//CGame, drawgame, getvehicle,  start, updatePos, setting -> set so xe, toc do, level
//class VEHLANE {
//	Traffic* t;	//so den gthong
//	Enemy* v[9];		//so xe - 5 car 4 truck
//	int level;			//1-5
//
//	const int numCarLVL[5] = { 2,3,4,4,5 };
//	const int numTruckLVL[5] = { 2,2,3,4,4 };
//
//	const int speed[5] = { 150,100,100,50,30 };
//public:
//	VEHLANE(int l) {
//		level = l;								//tu 1->5
//		int distLane = 3, minDistCar = 6;		//distance btw 2 lane, min distance btw 2 car
//		//khoi tao den giao thong
//		Point pT1 = { 85 + 2,6 }, pT2 = { 85 + 2,10 }, pC = { 4 + 4,2 + 2 + 1 }, pTruck = {4+6,10};
//		t = new Traffic[2]{ pT1,pT2 };				//default 2 lan xe -> 2 den gthong
//		//khoi tao xe hoi
//		//int a = 0, b = 1;
//		//srand(time(NULL));
//		//int rPos = rand() % (b - a + 1) + a;	//tu a den b
//		for (int i = 0; i < numCarLVL[level - 1]; ++i)
//			v[i] = new Car(pC, 1), v[i]->drawVeh(),pC.x += 15;
//		for (int i = numCarLVL[level - 1]; i < MAXCAR; ++i)
//			v[i] = NULL;
//		for (int i = MAXCAR; i < MAXCAR+numTruckLVL[level-1]; ++i)
//			v[i] = new Truck(pTruck, 0), v[i]->drawVeh(), pTruck.x += 17;
//		for (int i = numTruckLVL[level-1]; i < MAXTRUCK; ++i)
//			v[i] = NULL;
//	}
//	void updatePosVehicle()
//	{
//		while (1)
//		{
//			if (t[0].isGreen())
//				for (int i = 0; i < numCarLVL[level - 1]; ++i)
//					v[i]->Move();
//			if (t[1].isGreen())
//				for (int i = MAXCAR; i < MAXCAR + numTruckLVL[level - 1]; ++i)
//					v[i]->Move();
//			Sleep(speed[level - 1]);
//			t[0].toggle(1); t[1].toggle(0);
//		}
//	}
//
//		~VEHLANE() { for (int i = 0; i < 9; ++i) delete v[i], v[i] = NULL; delete[] t; t = NULL; }
//};
//	//VEHLANE() {
	//
	//		/*int c1pos = 5; Point veh1 = { c1pos,c1pos };
	//		c = new Car[numVeh];
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
		//Enemy* getVehicle() { return c; }//Lấy danh sách các xe

		//Thực hiện cho Truck & Car di chuyển

//	gotoxy(pos.x - bk, pos.y - 1);
	//	cout << "  _____  ";
	//	gotoxy(pos.x - bk, pos.y);
	//	cout << " /|   |\\ ";
	//	gotoxy(pos.x - bk, pos.y + 1);
	//	cout << "|_O___O_|";
	//	//setPos(pos);

	//	/*int left=5, right = 100;
	//		for (int r = 0; r < 3; ++r)
	//			for (int c = 0; c < 9; ++c) {
	//				int y = pos.y + r, x = pos.x + c;
	//				if (left <= x && x <= right)
	//				{
	//					gotoxy(x, y), cout << shape[r][c];
	//				}
	//			}*/
	//}
/*void Move();
	void drawVeh() {
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
	void pause();*/