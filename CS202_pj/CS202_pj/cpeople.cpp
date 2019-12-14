#include"Library.h"
CPEOPLE::CPEOPLE()
{
	mState = 1;
	mX = delta_screenSize_H / 2;
	mY = delta_screenSize_V+3;
	//print People
}
void CPEOPLE::Up(int n)
{
	mY -= n;
	if (mY < screenSize_V_top-1)
		mY = screenSize_V_top-1;
	gotoxy(mX, mY);
	cout << char(219) << char(219) << char(219);
	gotoxy(mX, mY + 1);
	cout << " " << char(219) << "   ";
	gotoxy(mX, mY + 2);
	cout << "    ";
}
void CPEOPLE::Down(int n)
{
	mY += n;
	if (mY > screenSize_V_bot)
		mY = screenSize_V_bot;
	gotoxy(mX, mY);
	cout << char(219) << char(219) << char(219);
	gotoxy(mX, mY + 1);
	cout << " " << char(219) << "   ";
	gotoxy(mX, mY -1);
	cout << "    ";
}
void CPEOPLE::Left(int n)
{
	mX -= n;
	if (mX < screenSize_H_left+2)
		mX = screenSize_H_left+2;
	gotoxy(mX, mY);
	cout << char(219) << char(219) << char(219) << "  ";
	gotoxy(mX, mY + 1);
	cout << " " << char(219) << "   ";

}
void CPEOPLE::Right(int n)
{
	mX += n;
	if (mX > screenSize_H_right-5)
		mX = screenSize_H_right-5;
	gotoxy(mX-2, mY);
	cout << "  " << char(219) << char(219) << char(219);
	gotoxy(mX-2, mY + 1);
	cout << "   " << char(219);
	
}
bool CPEOPLE::isDead()
{
	if (lives>0)
		return false;
	else
		return true;
}
Point CPEOPLE::currentPos()
{
	Point peoPos;
	peoPos.x = mX;
	peoPos.y = mY;
	return peoPos;
}
int CPEOPLE::getLives()
{
	return lives;
}
bool CPEOPLE::isCrash(Point pos) {
	if (abs(mX - pos.x) <=3 && abs(mY - pos.y) <= 3) {
		return true;
	}
	return false;
}