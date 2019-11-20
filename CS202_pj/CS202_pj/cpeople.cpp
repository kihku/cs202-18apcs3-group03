#include"Library.h"
CPEOPLE::CPEOPLE()
{
	mState = 1;
	mX = screenSize_H / 2;
	mY = screenSize_V;
	//print People
	gotoxy(mX, mY);
	cout << char(219);
}
void CPEOPLE::Up(int n)
{
	mY -= n;
	if (mY < 0)
		mY = 0;
}
void CPEOPLE::Down(int n)
{
	mY += n;
	if (mY > screenSize_V)
		mY = screenSize_V;
}
void CPEOPLE::Left(int n)
{
	mX -= n;
	if (mX < 0)
		mX = 0;
}
void CPEOPLE::Right(int n)
{
	mX += n;
}
bool CPEOPLE::isDead()
{
	if (mState == 0)
		return 1;
	else
		return 0;
}