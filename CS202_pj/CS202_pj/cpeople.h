#pragma once
#include"Library.h"
class CPEOPLE
{
private:
	int mX, mY;
	int lives;
	bool mState; //1 is alive, 0 is dead
public:
	CPEOPLE();
	CPEOPLE(int x, int y, int live);
	~CPEOPLE() { mX = 0; mY = 0; lives = 0; mState = 0; };
	void Up(int);
	void Left(int);
	void Right(int);
	void Down(int);
	int getLives();
	void resetLives(int liveMode);
	void reduceLive();
	void backToCheckPoint();
	void eraseCorpse();
	bool isFinish();
	//bool isFinish();
	bool isDead();
	//For arrayTesting
	Point currentPos();
	bool isCrash(Point Pos, ShapeSize ss);
	bool isEatHeart(int X);
	void plusLive();
};
