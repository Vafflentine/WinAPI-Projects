#include"pch.h"
#include<Windows.h>
#include"Dll1.h"
void CircleSpam(HDC hdc, int x, int y)
{
	HPEN newPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	SelectObject(hdc, newPen);
	Ellipse(hdc, x, y, x + 40, y + 40);
}

