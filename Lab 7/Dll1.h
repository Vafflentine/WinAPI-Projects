#pragma once
#include"windows.h"
#ifdef L7_2_API
#else
#define L7_2_API __declspec(dllexport)
#endif

L7_2_API void CircleSpam(HDC hdc, int x, int y);