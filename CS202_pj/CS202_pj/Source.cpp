#include"Library.h"
mutex CGame::mtx;

bool constVar::isMute = false;
bool constVar::isHard = true;

int main()
{
	ShowConsoleCursor(false);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	CGame game;
	system("cls");
	return 0;
}