#include"Library.h"
//start x,y CDINAUSOR is (4,3)
int main()
{
	/*CDINAUSOR str;
	CDINAUSOR str2,str3,str4;
	for (int i = 5; i < 100; ++i)
	{
		Sleep(300);
		str.Move(i, 5);
		str2.Move(i + 15, 5);
		str3.Move(i + 40, 5);
	}*/
	CCAR car;
	CTRUCK truck;
	for (int i = 5; i < 100; ++i)
	{
		truck.Move(i, 10);
		Sleep(200);
	}
	
	return 0;
}