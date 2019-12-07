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
	Point pos = getPos();
	for (int i = 0; i < ss.h; ++i)
		for (int j = 0; j < ss.w; ++j)
		{
			gotoxy(pos.x + j, pos.y + i);
			if (l + 1 <= pos.x + j && pos.x + j <= r-1)
				cout << ' ';
		}
	if (getDir()) {
			setPos({ pos.x + 1, pos.y });
		if (getPos().x >= r) setPos({ l - ss.w, pos.y });	//l-1?
	}
	else {
		setPos({ pos.x - 1, pos.y });
		if (getPos().x + ss.w - 1 <= l) setPos({ r , pos.y });
	}
}


void Car::drawEne()
{
	Point pos = getPos();
	
		for (int i = 0; i < ss.h; ++i)
			for (int j = 0;j<ss.w;++j)
			{
				gotoxy(pos.x+j, pos.y + i);
				if(l+1<=pos.x+j&&pos.x+j<=r-1)
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


void Truck::drawEne()
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
