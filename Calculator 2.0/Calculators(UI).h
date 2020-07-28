#pragma once

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <Shlwapi.h>
#include <iostream>
#include"Buttons.h"
void SimpleCalcuter(HWND hWnd,HWND*hButton,HINSTANCE hInst,HBITMAP hBitmap, HWND *hEdit)
{
	hEdit[0] = CreateWindow(_T("edit"), _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT, 10, 5, 380, 35, hWnd, (HMENU)ID_EDIT, hInst, 0);
	hButton[0] = CreateWindow(_T("Button"), _T("0"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 85, 275, 70, 70, hWnd, (HMENU)ID_BUTTON, hInst, 0);
	hButton[7] = CreateWindow(_T("Button"), _T("7"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 45, 70, 70, hWnd, (HMENU)ID_BUTTON_7, hInst, 0);
	hButton[8] = CreateWindow(_T("Button"), _T("8"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 85, 45, 70, 70, hWnd, (HMENU)ID_BUTTON_8, hInst, 0);
	hButton[9] = CreateWindow(_T("Button"), _T("9"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 160, 45, 70, 70, hWnd, (HMENU)ID_BUTTON_9, hInst, 0);
	hButton[4] = CreateWindow(_T("Button"), _T("4"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 120, 70, 70, hWnd, (HMENU)ID_BUTTON_4, hInst, 0);
	hButton[5] = CreateWindow(_T("Button"), _T("5"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 85, 120, 70, 70, hWnd, (HMENU)ID_BUTTON_5, hInst, 0);
	hButton[6] = CreateWindow(_T("Button"), _T("6"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 160, 120, 70, 70, hWnd, (HMENU)ID_BUTTON_6, hInst, 0);
	hButton[1] = CreateWindow(_T("Button"), _T("1"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 200, 70, 70, hWnd, (HMENU)ID_BUTTON_1, hInst, 0);
	hButton[2] = CreateWindow(_T("Button"), _T("2"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 85, 200, 70, 70, hWnd, (HMENU)ID_BUTTON_2, hInst, 0);
	hButton[3] = CreateWindow(_T("Button"), _T("3"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 160, 200, 70, 70, hWnd, (HMENU)ID_BUTTON_3, hInst, 0);
	hButton[10] = CreateWindow(_T("Button"), _T("+"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 235, 200, 70, 70, hWnd, (HMENU)ID_BUTTON_ADD, hInst, 0);
	hButton[11] = CreateWindow(_T("Button"), _T("-"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 235, 120, 70, 70, hWnd, (HMENU)ID_BUTTON_SUB, hInst, 0);
	hButton[12] = CreateWindow(_T("Button"), _T("*"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 235, 45, 70, 70, hWnd, (HMENU)ID_BUTTON_MUL, hInst, 0);
	hButton[13] = CreateWindow(_T("Button"), _T("/"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 310, 120, 70, 70, hWnd, (HMENU)ID_BUTTON_DIV, hInst, 0);
	hButton[14] = CreateWindow(_T("Button"), _T("="), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 310, 200, 70, 70, hWnd, (HMENU)ID_BUTTON_RES, hInst, 0);
	hButton[15] = CreateWindow(_T("Button"), _T("C"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 310, 45, 70, 70, hWnd, (HMENU)ID_BUTTON_C, hInst, 0);
	hButton[19] = CreateWindow(_T("Button"), _T("."), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 160, 275, 70, 70, hWnd, (HMENU)ID_BUTTON_POINT, hInst, 0);
	hButton[29] = CreateWindow(_T("Button"), _T(" "), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP, 10, 275, 70, 70, hWnd, (HMENU)ID_BUTTON_SWAP1, hInst, 0);
	SendMessage(hButton[29], BM_SETIMAGE, IMAGE_BITMAP, LPARAM(hBitmap));
}
void EngeeringCalcuter(HWND hWnd, HWND* hButton, HINSTANCE hInst, HBITMAP hBitmap,HWND *hEdit)
{
	hEdit[0] = CreateWindow(_T("edit"), _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT, 10, 5, 380, 35, hWnd, (HMENU)ID_EDIT, hInst, 0);
	hButton[0] = CreateWindow(_T("Button"), _T("0"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 65, 210, 50, 50, hWnd, (HMENU)ID_BUTTON, hInst, 0);
	hButton[7] = CreateWindow(_T("Button"), _T("7"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 45, 50, 50, hWnd, (HMENU)ID_BUTTON_7, hInst, 0);
	hButton[8] = CreateWindow(_T("Button"), _T("8"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 65, 45, 50, 50, hWnd, (HMENU)ID_BUTTON_8, hInst, 0);
	hButton[9] = CreateWindow(_T("Button"), _T("9"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 120, 45, 50, 50, hWnd, (HMENU)ID_BUTTON_9, hInst, 0);
	hButton[4] = CreateWindow(_T("Button"), _T("4"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 100, 50, 50, hWnd, (HMENU)ID_BUTTON_4, hInst, 0);
	hButton[5] = CreateWindow(_T("Button"), _T("5"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 65, 100, 50, 50, hWnd, (HMENU)ID_BUTTON_5, hInst, 0);
	hButton[6] = CreateWindow(_T("Button"), _T("6"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 120, 100, 50, 50, hWnd, (HMENU)ID_BUTTON_6, hInst, 0);
	hButton[1] = CreateWindow(_T("Button"), _T("1"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 155, 50, 50, hWnd, (HMENU)ID_BUTTON_1, hInst, 0);
	hButton[2] = CreateWindow(_T("Button"), _T("2"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 65, 155, 50, 50, hWnd, (HMENU)ID_BUTTON_2, hInst, 0);
	hButton[3] = CreateWindow(_T("Button"), _T("3"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 120, 155, 50, 50, hWnd, (HMENU)ID_BUTTON_3, hInst, 0);
	hButton[10] = CreateWindow(_T("Button"), _T("+"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 175, 155, 50, 50, hWnd, (HMENU)ID_BUTTON_ADD, hInst, 0);
	hButton[11] = CreateWindow(_T("Button"), _T("-"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 175, 100, 50, 50, hWnd, (HMENU)ID_BUTTON_SUB, hInst, 0);
	hButton[12] = CreateWindow(_T("Button"), _T("*"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 175, 45, 50, 50, hWnd, (HMENU)ID_BUTTON_MUL, hInst, 0);
	hButton[13] = CreateWindow(_T("Button"), _T("/"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 230, 45, 50, 50, hWnd, (HMENU)ID_BUTTON_DIV, hInst, 0);
	hButton[14] = CreateWindow(_T("Button"), _T("="), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 175, 210, 50, 50, hWnd, (HMENU)ID_BUTTON_RES, hInst, 0);
	hButton[15] = CreateWindow(_T("Button"), _T("C"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 285, 155, 50, 50, hWnd, (HMENU)ID_BUTTON_C, hInst, 0);
	hButton[16] = CreateWindow(_T("Button"), _T("("), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 285, 45, 50, 50, hWnd, (HMENU)ID_BUTTON_OPEN, hInst, 0);
	hButton[17] = CreateWindow(_T("Button"), _T(")"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 340, 45, 50, 50, hWnd, (HMENU)ID_BUTTON_CLOSE, hInst, 0);
	hButton[18] = CreateWindow(_T("Button"), _T("e"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 210, 50, 50, hWnd, (HMENU)ID_BUTTON_E, hInst, 0);
	hButton[19] = CreateWindow(_T("Button"), _T("."), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 120, 210, 50, 50, hWnd, (HMENU)ID_BUTTON_POINT, hInst, 0);
	hButton[20] = CreateWindow(_T("Button"), _T("cos"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 230, 155, 50, 50, hWnd, (HMENU)ID_BUTTON_COS, hInst, 0);
	hButton[21] = CreateWindow(_T("Button"), _T("sin"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 230, 100, 50, 50, hWnd, (HMENU)ID_BUTTON_SIN, hInst, 0);
	hButton[22] = CreateWindow(_T("Button"), _T("tan"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 285, 100, 50, 50, hWnd, (HMENU)ID_BUTTON_TAN, hInst, 0);
	hButton[23] = CreateWindow(_T("Button"), _T("ctg"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 340, 100, 50, 50, hWnd, (HMENU)ID_BUTTON_CTG, hInst, 0);
	hButton[24] = CreateWindow(_T("Button"), _T("X ^"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 340, 155, 50, 50, hWnd, (HMENU)ID_BUTTON_POWER, hInst, 0);
	hButton[25] = CreateWindow(_T("Button"), _T("lg"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 230, 210, 50, 50, hWnd, (HMENU)ID_BUTTON_LOG, hInst, 0);
	hButton[26] = CreateWindow(_T("Button"), _T("ln"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 285, 210, 50, 50, hWnd, (HMENU)ID_BUTTON_LN, hInst, 0);
	hButton[27] = CreateWindow(_T("Button"), _T("sqrt"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 340, 210, 50, 50, hWnd, (HMENU)ID_BUTTON_SQRT, hInst, 0);
	hButton[28] = CreateWindow(_T("Button"), _T("pi"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 265, 50, 50, hWnd, (HMENU)ID_BUTTON_PI, hInst, 0);
	hButton[29] = CreateWindow(_T("Button"), _T(" "), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP, 65, 265, 50, 50, hWnd, (HMENU)ID_BUTTON_SWAP, hInst, 0);
	SendMessage(hButton[29], BM_SETIMAGE, IMAGE_BITMAP, LPARAM(hBitmap));	
}

void BinaryCalculator(HWND hWnd, HWND* hButton, HINSTANCE hInst, HWND *hEdit,HWND* hBinary)
{
	hEdit[1] = CreateWindow(_T("edit"), _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT, 10, 5, 380, 35, hWnd, (HMENU)ID_EDIT1, hInst, 0);
	hEdit[2] = CreateWindow(_T("edit"), _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT, 10, 50, 380, 35, hWnd, (HMENU)ID_EDIT2, hInst, 0);
	hEdit[3] = CreateWindow(_T("edit"), _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT, 10, 95, 380, 35, hWnd, (HMENU)ID_EDIT3, hInst, 0);
	hBinary[0] = CreateWindow(_T("Button"), _T("And"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 140, 70, 70, hWnd, (HMENU)ID_BUTTON_AND, hInst, 0);
	hBinary[1] = CreateWindow(_T("Button"), _T("Or"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 85, 140, 70, 70, hWnd, (HMENU)ID_BUTTON_OR, hInst, 0);
	hBinary[2] = CreateWindow(_T("Button"), _T("Xor"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 160, 140, 70, 70, hWnd, (HMENU)ID_BUTTON_XOR, hInst, 0);
	hBinary[3] = CreateWindow(_T("Button"), _T("Nand"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 235, 140, 70, 70, hWnd, (HMENU)ID_BUTTON_NAND, hInst, 0);
	hBinary[4] = CreateWindow(_T("Button"), _T("Nor"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 310, 140, 70, 70, hWnd, (HMENU)ID_BUTTON_NOR, hInst, 0);
	hBinary[5] = CreateWindow(_T("Button"), _T("C"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 215, 70, 70, hWnd, (HMENU)ID_BUTTON_C, hInst, 0);
}