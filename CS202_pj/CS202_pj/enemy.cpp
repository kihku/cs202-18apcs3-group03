#pragma once
#include"Library.h"
int Traffic::numTraffic = 0;
//int Car::numCar = 0;
void CDINAUSOR::Move(int x, int y)
{
	const int height = 3;
	const int width = 4;
	for (int i = y; i < y + height; ++i)
	{
		for (int j = x; j < x + width; ++j)
		{
			if (i == y && j == x + 3 || i == y && j == x + 2)
			{
				continue;
			}
			gotoxy(j, i);
			cout << char(219);
			if (i == y + height - 1 && j == x + width - 1)
			{
				for (int k = 0; k < width / 4; ++k) //lam tron len xuong?
				{
					gotoxy(j + 1, i);
					cout << char(219);
				}
			}
		}
		x -= 2;
	}
	for (int j = x - width; j < x; ++j)
	{
		gotoxy(j, y);
		cout << "      ";
		gotoxy(j, y + 1);
		cout << "    ";
		gotoxy(j, y + 2);
		cout << "  ";
	}
}


Car::Car(Point p) :Enemy(p)
{
	
}

Car::~Car()
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
	int width = 144;
	int t = width * 3 / 4 - 1 - 12;
	Point pos = getPos();
	int l = 3, r = screenSize_H-1;
	if (pos.x > r)setPos({ l, pos.y });
	for (int i = 0; i < ss.h; ++i)
		for (int j = pos.x; j <= min(r,pos.x + ss.w - 1); ++j) {
			gotoxy(pos.x + j-pos.x, pos.y + i);
			cout << ' ';
		}
	setPos({ getPos().x+1, getPos().y});
}

void Car::drawEne()
{
	Point pos = getPos();
	int l = 3, r = screenSize_H-1;
	
	for (int i = 0; i < ss.h; ++i)
		for (int j = pos.x; j <= min(r, pos.x + ss.w - 1); ++j)
		{
			gotoxy(getPos().x + j -pos.x, getPos().y + i);
			cout << shape[i][j-pos.x];
		}
	/*Point pos = getPos();
	if (pos.x == 4) return;
	if (pos.x > r) return;
	for (int i = 0; i < ss.h; ++i) 
		for (int j = max(1, pos.x); j <= min(r, pos.x + ss.w - 1); ++j) {
			gotoxy(pos.x + j, pos.y + i);
			cout << ' ';
		}
	if (getPos().x + ss.w <= l | getPos().x > r)return;
	for (int i = 0; i < ss.h; ++i)
		for (int j = max(l + 1, getPos().x); j <= min(r, getPos().x + ss.w - 1); ++j)
		{
			gotoxy(getPos().x +j, getPos().y+i );
			cout << shape[i][j - max(1, getPos().x)];
		}
	return;*/
}

Truck::Truck(Point p):Enemy(p) {
	char t[3][13] = { {' ','_','_','_','_','_','_','_','_','_',' ',' ',' '},
	{ '|','/','/','/','/','/','/','/','|','_','\\','_',' ' },
	{ '|','_','/','O','_','_','_','_','O','\\','_','_','|' } };
	shape = new char* [3];
	for (int i = 0; i < 3; ++i)
		shape[i] = new char[13];

	for (int i = 0; i < 3; ++i)
		shape[i] = t[i];
}

Truck::~Truck()
{
	for (int i = 0; i < 3; ++i)
		delete[] shape[i];
	delete[] shape, shape = NULL;
}

ShapeSize Truck::getShapeSize()
{
	return { 13,3 };
}

char** Truck::getShape()
{
	return shape;
}

int Truck::getType()
{
	return 3;
}

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
<<<<<<< HEAD

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
	Point pos = getPos();
	for (int i = 0; i < ss.h; ++i)
		for (int j = 0; j < ss.w; ++j)
		{
			gotoxy(pos.x + j, pos.y + i);
			if (l + 1 <= pos.x + j && pos.x + j <= r - 1)
				cout << ' ';
		}
	if (getDir()) {
		setPos({ pos.x + 1, pos.y });
		if (getPos().x >= r) setPos({ l - ss.w, pos.y });
	}
	else {
		setPos({ pos.x - 1, pos.y });
		if (getPos().x + ss.w - 1 <= l) setPos({ r , pos.y });
	}
}


void Bird::drawEne()
{
	Point pos = getPos();

	for (int i = 0; i < ss.h; ++i)
		for (int j = 0; j < ss.w; ++j)
		{
			gotoxy(pos.x + j, pos.y + i);
			if (l + 1 <= pos.x + j && pos.x + j <= r - 1)
				getDir() ? cout << shape1[i][j] : cout << shape0[i][j];
		}
}

Dinosaur::Dinosaur(Point p, bool d):Enemy(p, d) {
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
	Point pos = getPos();
	for (int i = 0; i < ss.h; ++i)
		for (int j = 0; j < ss.w; ++j)
		{
			gotoxy(pos.x + j, pos.y + i);
			if (l + 1 <= pos.x + j && pos.x + j <= r - 1)
				cout << ' ';
		}
	if (getDir()) {
		setPos({ pos.x + 1, pos.y });
		if (getPos().x >= r) setPos({ l - ss.w, pos.y });
	}
	else {
		setPos({ pos.x - 1, pos.y });
		if (getPos().x + ss.w - 1 <= l) setPos({ r , pos.y });
	}
}


void Dinosaur::drawEne()
{
	Point pos = getPos();

	for (int i = 0; i < ss.h; ++i)
		for (int j = 0; j < ss.w; ++j)
		{
			gotoxy(pos.x + j, pos.y + i);
			if (l + 1 <= pos.x + j && pos.x + j <= r - 1)
				getDir() ? cout << shape1[i][j] : cout << shape0[i][j];
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
	gotoxy(pos.x, pos.y); (greenLight) ? cout << char(220) : cout << char(223);
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
=======
>>>>>>> parent of 5536fa9... Update all obstacle {direction, random, level}, fix barrier, dinosaur will be redrawed shiet
