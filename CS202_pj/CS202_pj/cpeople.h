#pragma once
#include"Library.h"
class CPEOPLE
{
private:
	int mX, mY;
	int lives = 5;
	bool mState; //1 is alive, 0 is dead
public:
	CPEOPLE();
	void Up(int);
	void Left(int);
	void Right(int);
	void Down(int);
	int getLives();
	void reduceLive();
	//bool isImpact(const Enemy*&);
	//bool isImpact(const CANIMAL*&);
	//bool isFinish();
	bool isDead();
	//For arrayTesting
	Point currentPos();
	bool isCrash(Point Pos, ShapeSize ss);
};
