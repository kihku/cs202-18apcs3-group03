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
#include<string>
#include<MMSystem.h>
#include <ctime>
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

//const int screenSize_V = 24;
//const int screenSize_H = 84;
const int screenSize_H_left = 3;
const int screenSize_H_right = 84;
const int screenSize_V_top = 3;
const int screenSize_V_bot = 24;
const int delta_screenSize_H = screenSize_H_right - screenSize_H_left;
const int delta_screenSize_V = screenSize_V_bot - screenSize_V_top;
const int peopleLives = 5;
const int heart_y = 13;

const int MAXLEVEL = 5;
const int MAXCAR = 5;
const int MAXTRUCK = 4;
const int MAXSPEED = 100;		//1s
#define ESC 27
#define KEY_UP 72
#define KEY_DOWN 80
#define ENTER 13
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_BACK 8

#define BUTTON_COLOR SetColor(14);
#define SCREEN_COLOR system("Color B0");
#define PAUSE_BUTTON_CO TextColor(8);
#define PAUSE_SCREEN_CO system("Color C0");
#define SETTING_BUT_CO TextColor(3);
//#define RED_LIGHT SetColor(10);
//#define GREEN_LIGHT SetColor(8);
#include"extra.h"
#include"cpeople.h"
#include"enemy.h"
#include"clane.h"
#include"cgame.h"






