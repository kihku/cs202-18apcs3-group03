#include"Library.h"
CPEOPLE::CPEOPLE()
{
	mState = 1;
	mX = screenSize_H / 2;
	mY = screenSize_V;
	//print People
	gotoxy(mX, mY);
	cout << char(219) << char(219) << char(219);
	gotoxy(mX, mY + 1);
	cout << " "<< char(219) << "   ";
}
void CPEOPLE::Up(int n)
{
	mY -= n;
	if (mY < 0)
		mY = 0;
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
	if (mY > screenSize_V)
		mY = screenSize_V;
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
	if (mX < 0)
		mX = 0;
	gotoxy(mX, mY);
	cout << char(219) << char(219) << char(219) << "  ";
	gotoxy(mX, mY + 1);
	cout << " " << char(219) << "   ";

}
void CPEOPLE::Right(int n)
{
	mX += n;
	if (mX > screenSize_H)
		mX = screenSize_H;
	gotoxy(mX-2, mY);
	cout << "  " << char(219) << char(219) << char(219);
	gotoxy(mX-2, mY + 1);
	cout << "   " << char(219);
}
bool CPEOPLE::isDead()
{
	if (mState == 0)
		return 1;
	else
		return 0;
}
Point CPEOPLE::currentPos()
{
	Point peoPos;
	peoPos.x = mX;
	peoPos.y = mY;
	return peoPos;
}