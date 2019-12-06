#pragma once
#include<iostream>
#include<deque>
#include<Windows.h>
#include<thread>
#include<conio.h>
#include<vector>
#include <cstdlib>	//rand
#include <ctime>
#include<mutex>
#include<fstream>
using namespace std;
struct Point { 
	int x, y;
	void display()
	{
		cout << x << " " << y;
	}
};
struct ShapeSize {
	int w, h;
};

#include"extra.h"
#include"cpeople.h"
#include"enemy.h"
#include"clane.h"
#include"CGame.h"

const int screenSize_V = 24;
const int screenSize_H = 84;

const int MAXLEVEL = 5;
const int MAXCAR = 5;
const int MAXTRUCK = 4;
const int MAXSPEED = 100;		//1s
#define ESC 27;
#define ENTER 13;




