#pragma once
#include"windows.h"
#ifdef L7_3_API
#else
#define L7_3_API __declspec(dllexport)
#endif

L7_3_API void RectangleOnClick(HDC hdc, int x, int y);