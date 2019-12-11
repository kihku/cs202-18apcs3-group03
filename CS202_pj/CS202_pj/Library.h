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


#include"extra.h"
#include"cpeople.h"
#include"enemy.h"
#include"cgame.h"

const int screenSize_V = 24;
const int screenSize_H = 84;
#define ESC 27;
#define ENTER 13;




