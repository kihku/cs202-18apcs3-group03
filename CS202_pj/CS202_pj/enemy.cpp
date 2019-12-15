#pragma once
#include"Library.h"
int Traffic::numTraffic = 0;
//int Car::numCar = 0;
Car::Car(Point p, bool d) :Enemy(p,d)
{
	
}

ShapeSize Car::getShapeSize()
{
	return ss;
}


int Car::getType()
{
	return 2;
}

void Car::moveEne()
{
	unique_lock<mutex> lk(CGame::mtx);
	Point pos = getPos();
	for (int i = 0; i < ss.h; ++i)
		for (int j = 0; j < ss.w; ++j)
		{
			gotoxy(pos.x + j, pos.y + i);
			if (screenSize_H_left + 1 <= pos.x + j && pos.x + j <= screenSize_H_right - 1)
				cout << ' ';
		}
	//if (getDir()) {
	//		setPos({ pos.x + 1, pos.y });
	//	if (getPos().x >= screenSize_H_right) setPos({ screenSize_H_left - ss.w, pos.y });	//l-1?
	//}
	//else {
	setPos({ pos.x - 1, pos.y });
	if (getPos().x +ss.w-1<=  screenSize_H_left) setPos({ screenSize_H_right, pos.y });
	//}
}


void Car::drawEne()
{
	unique_lock<mutex> lk(CGame::mtx);
	Point pos = getPos();

	for (int i = 0; i < ss.h; ++i)
		for (int j = 0; j < ss.w; ++j)
		{
			gotoxy(pos.x + j, pos.y + i);
			if (screenSize_H_left + 1 <= pos.x + j && pos.x + j <= screenSize_H_right - 1)
				cout << shape[i][j];
		}
}

Truck::Truck(Point p, bool d):Enemy(p,d) {}

ShapeSize Truck::getShapeSize()
{
	return ss;
}

int Truck::getType()
{
	return 3;
}

void Truck::moveEne()
{
	unique_lock<mutex> lk(CGame::mtx);
	Point pos = getPos();
	for (int i = 0; i < ss.h; ++i)
		for (int j = 0; j < ss.w; ++j)
		{
			gotoxy(pos.x + j, pos.y + i);
			if (screenSize_H_left + 1 <= pos.x + j && pos.x + j <= screenSize_H_right - 1)
				cout << ' ';
		}
	//if (getDir()) {
	setPos({ pos.x + 1, pos.y });
	if (getPos().x >= screenSize_H_right) setPos({ screenSize_H_left - ss.w, pos.y });
	//}
	//else {
	//	setPos({ pos.x - 1, pos.y });
	//	if (getPos().x >= screenSize_H_left) setPos({ screenSize_H_right - ss.w, pos.y });
	//}
}


void Truck::drawEne()
{
	unique_lock<mutex> lk(CGame::mtx);
	Point pos = getPos();

	for (int i = 0; i < ss.h; ++i)
		for (int j = 0; j < ss.w; ++j)
		{
			gotoxy(pos.x + j, pos.y + i);
			if (screenSize_H_left + 1 <= pos.x + j && pos.x + j <= screenSize_H_right - 1)
				cout << shape1[i][j];
		}
}

ShapeSize Bird::getShapeSize()
{
	return ss;
}

int Bird::getType()
{
	return 4;
}

void Bird::moveEne()
{
	unique_lock<mutex> lk(CGame::mtx);
	Point pos = getPos();
	for (int i = 0; i < ss.h; ++i)
		for (int j = 0; j < ss.w; ++j)
		{
			gotoxy(pos.x + j, pos.y + i);
			if (screenSize_H_left + 1 <= pos.x + j && pos.x + j <= screenSize_H_right - 1)
				cout << ' ';
		}
	//if (getDir()) {
	//		setPos({ pos.x + 1, pos.y });
	//	if (getPos().x >= screenSize_H_right) setPos({ screenSize_H_left - ss.w, pos.y });	//l-1?
	//}
	//else {
	setPos({ pos.x - 1, pos.y });
	if (getPos().x + ss.w - 1 <= screenSize_H_left) setPos({ screenSize_H_right, pos.y });
	//}
}


void Bird::drawEne()
{
	unique_lock<mutex> lk(CGame::mtx);
	Point pos = getPos();

	for (int i = 0; i < ss.h; ++i)
		for (int j = 0; j < ss.w; ++j)
		{
			gotoxy(pos.x + j, pos.y + i);
			if (screenSize_H_left + 1 <= pos.x + j && pos.x + j <= screenSize_H_right - 1)
				cout << shape0[i][j];
		}
}
Dinosaur::Dinosaur(Point p, bool d):Enemy(p, d) {
	};

ShapeSize Dinosaur::getShapeSize()
{
	return ss;
}

int Dinosaur::getType()
{
	return 5;
}

void Dinosaur::moveEne()
{
	unique_lock<mutex> lk(CGame::mtx);
	Point pos = getPos();
	for (int i = 0; i < ss.h; ++i)
		for (int j = 0; j < ss.w; ++j)
		{
			gotoxy(pos.x + j, pos.y + i);
			if (screenSize_H_left + 1 <= pos.x + j && pos.x + j <= screenSize_H_right - 1)
				printf(" ");
		}
	//if (!getDir()) {
	setPos({ pos.x + 1, pos.y });
	if (getPos().x >= screenSize_H_right) setPos({ screenSize_H_left - ss.w, pos.y });
	//	}
		////else {
		//	setPos({ pos.x - 1, pos.y });
		//	if (getPos().x >= screenSize_H_left) setPos({ screenSize_H_right - ss.w, pos.y });
		////}
}


void Dinosaur::drawEne()
{
	unique_lock<mutex> lk(CGame::mtx);
	Point pos = getPos();
	lk.unlock();
	for (int i = 0; i < ss.h; ++i)
		for (int j = 0; j < ss.w; ++j)
		{
			lk.lock();
			gotoxy(pos.x + j, pos.y + i);
			if (screenSize_H_left + 1 <= pos.x + j && pos.x + j <= screenSize_H_right - 1)
				printf("%c", shape1[i][j]);
			lk.unlock();
		}
}

Traffic::Traffic(Point p)
{
	++numTraffic;
	greenLight = true;
	pos = p;
}

Traffic::Traffic(const Traffic& src)
{
	++numTraffic; greenLight = src.greenLight; pos = src.pos;
}

void Traffic::drawTrafficLight()
{
	unique_lock<mutex> lk(CGame::mtx);
	gotoxy(pos.x, pos.y);
	if (greenLight) {
		cout << char(220);
	}
	else {
		cout << char(223);
	}
}

void Traffic::green()
{
	greenLight = true;
}

void Traffic::red()
{
	greenLight = false;
}

void Traffic::toggle(int i)
{
	greenLight = !greenLight;
}

Traffic::~Traffic()
{
	--numTraffic;
}

bool Traffic::isGreen()
{
	return greenLight;
}

char Car::shape[3][9] = { {' ',' ','_','_','_','_','_',' ',' '},
	{' ','/','|',' ',' ',' ','|','\\',' ' },
	{'|','_','O','_','_','_','O','_','|' } };
ShapeSize Car::ss = { 9,3 };

char Truck::shape1[3][13] = { {' ','_','_','_','_','_','_','_','_','_',' ',' ',' '},
	{ '|','/','/','/','/','/','/','/','|','_','\\','_',' ' },
	{ '|','_','/','O','_','_','_','_','O','\\','_','_','|' } }; 
ShapeSize Truck::ss = { 13,3 }; 

char Bird::shape0[3][7] = { {' ',' ',',',',',',',' ',' '},
	{ '<','(','.',' ',' ',' ',')' },
	{ ' ','(',',','(','>','_','\\'} };
ShapeSize Bird::ss = { 7,3 };

char Dinosaur::shape1[3][8] ={{'(','\\','(','\\',' ',' ',' ',' '}, 
{'(','-','x','-',')',' ',' ','  '  },
{'o','_','(','"',')','(','"',')'}};
ShapeSize Dinosaur::ss = { 8,3 };


//
//void Car::Move()
//{
//	int l = 3, r = 84;
//	unique_lock<mutex> lk(CGame::mtx);
//	if (dir) {
//		//di lo khung thi di lai
//		if (r <= pos.x+bk) {
//			gotoxy(pos.x - bk, pos.y - 1);
//			cout << "         ";
//			gotoxy(pos.x - bk, pos.y);
//			cout << "         ";
//			gotoxy(pos.x - bk, pos.y + 1);
//			cout << "         ";
//			pos.x = l+bk+1, drawVeh();
//		}
//		else {
//			gotoxy(pos.x - bk, pos.y - 1);
//			cout << " ";
//			gotoxy(pos.x - bk, pos.y);
//			cout << " ";
//			gotoxy(pos.x - bk, pos.y + 1);
//			cout << " ";
//			++pos.x, drawVeh();
//		}
//	}
//	else {
//		//di lo khung thi di lai
//		if (pos.x-bk <= l) {
//			gotoxy(pos.x-bk, pos.y - 1);
//			cout << "         ";
//			gotoxy(pos.x-bk, pos.y);
//			cout << "         ";
//			gotoxy(pos.x-bk, pos.y + 1);
//			cout << "         ";
//			pos.x = r-bk-1, drawVeh();
//		}
//		else {
//			gotoxy(pos.x + bk, pos.y - 1);
//			cout << " ";
//			gotoxy(pos.x + bk, pos.y);
//			cout << " ";
//			gotoxy(pos.x + bk, pos.y + 1);
//			cout << " ";
//			--pos.x, drawVeh();
//		}
//	}
//}
//void Car::pause()
//{
//	drawVeh();
//}
//void Truck::Move()
//{
//	int l = 4, r = 85;
//	unique_lock<mutex> lk(CGame::mtx);
//	if (dir) {
//		//di lo khung thi di lai
//		if (r <= pos.x + bk ) {
//			gotoxy(pos.x - bk, pos.y - 1);
//			cout << "             ";
//			gotoxy(pos.x - bk, pos.y);
//			cout << "             ";
//			gotoxy(pos.x - bk, pos.y + 1);
//			cout << "             ";
//			pos.x = l + bk+1, drawVeh();
//		}
//		else {
//			gotoxy(pos.x - bk, pos.y - 1);
//			cout << " ";
//			gotoxy(pos.x - bk, pos.y);
//			cout << " ";
//			gotoxy(pos.x - bk, pos.y + 1);
//			cout << " ";
//			++pos.x, drawVeh();
//		}
//	}
//	else {
//		//di lo khung thi di lai
//		if (pos.x - bk  <= l) {
//			gotoxy(pos.x - bk, pos.y - 1);
//			cout << "             ";
//			gotoxy(pos.x - bk, pos.y);
//			cout << "             ";
//			gotoxy(pos.x - bk, pos.y + 1);
//			cout << "             ";
//			pos.x = r - bk-1, drawVeh();
//		}
//		else {
//			gotoxy(pos.x + bk, pos.y - 1);
//			cout << " ";
//			gotoxy(pos.x + bk, pos.y);
//			cout << " ";
//			gotoxy(pos.x + bk, pos.y + 1);
//			cout << " ";
//			--pos.x, drawVeh();
//		}
//	}
//}
//
//void Truck::pause()
//{
//	drawVeh();
//}
/*for (int i = 0; i < 4; ++i) shape1[0][i] = ' ';
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
	shape0[1][7] = shape0[2][7] = shape0[3][7] = shape0[3][10] = char(175);*/
