#pragma once
#include"Library.h"
using namespace std;
class CPEOPLE
{
private:
	int mX, mY;
	bool mState; //1 is alive, 0 is dead
public:
	CPEOPLE();
	void Up(int);
	void Left(int);
	void Right(int);
	void Down(int);
	//bool isImpact(const CVEHICLE*&);
	//bool isImpact(const CANIMAL*&);
	//bool isFinish();
	bool isDead();
	//For arrayTesting
	Point currentPos();
};
