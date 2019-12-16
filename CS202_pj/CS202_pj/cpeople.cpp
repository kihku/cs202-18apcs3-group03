#include"Library.h"
CPEOPLE::CPEOPLE()
{
	lives = peopleLives;
	mState = 1;
	mX = delta_screenSize_H / 2;
	mY = delta_screenSize_V+3;
}
CPEOPLE::CPEOPLE(int x, int y, int live)
{
	lives = live;
	if (live < 0)
		mState = 0;
	else mState = 1;
	mX = x;
	mY = y;
}
void CPEOPLE::backToCheckPoint()
{
	mX = delta_screenSize_H / 2;
	mY = delta_screenSize_V + 3;
	//print People at checkpoint
	unique_lock<mutex>lk(CGame::mtx);
	gotoxy(mX, mY);
	cout << char(219) << char(219) << char(219);
	gotoxy(mX, mY + 1);
	cout << " " << char(219) << "   ";
}

void CPEOPLE::eraseCorpse()
{
	unique_lock<mutex>lk(CGame::mtx);
	gotoxy(mX, mY);
	cout << "   ";
	gotoxy(mX, mY + 1);
	cout << "     ";
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
	cout << "   ";
	gotoxy(mX, mY + 3);
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
	gotoxy(mX, mY - 1);
	cout << "   ";
	gotoxy(mX, mY -2);
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
void CPEOPLE::resetLives()
{
	lives = peopleLives;
}
bool CPEOPLE::isFinish()
{
	if (mY == screenSize_V_top + 1)
		return true;
	else
		return false;
}
bool CPEOPLE::isCrash(Point pos, ShapeSize ss) {
	if ((mX - pos.x) >= 0 && (mY - pos.y) >= 0) //People in the right & below
	{
		if ((mX - pos.x) <= ss.w && (mY - pos.y) < ss.h) {
			//lives--;
			return true;
		}
	}
	else 
		if ((mX - pos.x) < 0 && (mY - pos.y) < 0) { //People in the left & above
			if ((pos.x - mX) <=2 && (pos.y - mY) <= 1) {
				//lives--;
				return true;
			}
		}
		else
			if ((mX - pos.x) < 0 && (mY - pos.y) >= 0) { //People in the left & below
				if ((pos.x- mX) <= 2 && (mY - pos.y) < ss.h) {
					//lives--;
					return true;
				}
			}
			else
				if ((mX - pos.x) >= 0 && (mY - pos.y) < 0) { //People in the right & above
					if ((mX - pos.x) <=ss.w && (pos.y - mY) <= 1) {
						//lives--;
						return true;
					}
				}
	return false;
}
	
	
	
