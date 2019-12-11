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

//const int screenSize_V = 24;
//const int screenSize_H = 84;
const int screenSize_H_left = 3;
const int screenSize_H_right = 84;
const int screenSize_V_top = 3;
const int screenSize_V_bot = 24;
const int delta_screenSize_H = screenSize_H_right - screenSize_H_left;
const int delta_screenSize_V = screenSize_V_bot - screenSize_V_top;


const int MAXLEVEL = 5;
const int MAXCAR = 5;
const int MAXTRUCK = 4;
const int MAXSPEED = 100;		//1s
#define ESC 27;
#define ENTER 13;




