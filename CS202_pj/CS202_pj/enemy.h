#pragma once
#include"Library.h"

//CVEHICLE
class CVEHICLE
{
private:
	int mX, mY;
public:
	virtual void Move(int, int) = 0;
};
class CTRUCK : public CVEHICLE {
private:
	
public:
	void Move(int, int);
};
class CCAR : public CVEHICLE {
public:
	void Move(int, int);
};
//----------------CANIMAL-----------------
class CANIMAL {
	int mX, mY;
public:
	//virtual void Move(int, int);
	//virtual void Tell() = 0;
};
class CDINAUSOR : public CANIMAL {
private:
public:
	void Move(int, int);
};

class CBIRD : public CANIMAL {
};

