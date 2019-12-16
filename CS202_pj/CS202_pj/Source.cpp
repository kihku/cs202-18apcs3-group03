#include"Library.h"
mutex CGame::mtx;

CGame* CGame::instance = 0;
int main()
{
	ShowConsoleCursor(false);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	CGame* game = game->getInstance();
	system("cls");
	return 0;
}