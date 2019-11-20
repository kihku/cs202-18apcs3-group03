#include"Library.h"
void CGAME::updatePosPeople(char keyPressed)
{
	const int step_horizontal = 2;
	const int step_vertical = 1;
	if (keyPressed == 'D')
	{
		cn.Right(step_horizontal);
	}
	else if (keyPressed == 'A')
	{
		cn.Left(step_horizontal);
	}
	else if (keyPressed == 'W')
	{
		cn.Up(step_vertical);
	}
	else if (keyPressed == 'S')
	{
		cn.Down(step_vertical);
	}
}