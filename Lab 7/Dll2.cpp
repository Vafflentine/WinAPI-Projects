#include"pch.h"
#include<Windows.h>
#include"Dll2.h"
void RectangleOnClick(HDC hdc, LPARAM lParam)
{
	int x, y;
	x = LOWORD(lParam); //узнаём координаты
	y = HIWORD(lParam);
	Rectangle(hdc, x, y, x + 100, y + 40);
}

