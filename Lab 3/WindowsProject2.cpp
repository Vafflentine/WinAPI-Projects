// WindowsProject9.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "WindowsProject2.h"
#include<iostream>
#include<cstdlib>
using namespace std;
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
RECT rect;
COLORREF clrf;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_WINDOWSPROJECT2, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT2));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT2));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT2);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	GetClientRect(hWnd, &rect);
	HBRUSH newBrush = CreateSolidBrush(RGB(255, 0, 0));
	int digit = 17;
	char symbol;
	char buffer[256];
	int pos = 0;
	int pos1 = 0;
	double h = 0;
	double q = 0;
	POINT tPoints[6];
	HDC hdc1;
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_RAND:
			hdc1 = GetDC(hWnd);
			digit = 17;
			for (int i = 0; i < rect.right; i += 20)
			{
				for (int j = 0; j < rect.bottom; j += 20)
				{
					Rectangle(hdc1, i, j, i + 20, j + 20);
					char symbol = digit + '0';
					TextOut(hdc1, i, j, buffer, wsprintf(buffer, "%c", symbol));
					digit++;
					SetTextColor(hdc1, RGB(rand() % 255, rand() % 255, rand() % 255));
					clrf = RGB(255, rand() % 255, 0);
					newBrush = CreateSolidBrush(clrf);
					SelectObject(hdc1, newBrush);
					SetBkMode(hdc1, TRANSPARENT);
				}
			}
			Sleep(3000);
			for (int i = 0; i < rect.right; i += 20)
			{
				for (int j = 0; j < rect.bottom; j += 20)
				{
					clrf = RGB(255, rand() % 255, 0);
					newBrush = CreateSolidBrush(clrf);
					if ((GetGValue(clrf) + GetRValue(clrf)) % 5 == 0)
					{
						newBrush = CreateSolidBrush(RGB(0, 0, 0));
						SelectObject(hdc1, newBrush);

						Rectangle(hdc1, i, j, i + 20, j + 20);
					}
				}
			}
			newBrush = CreateSolidBrush(RGB(255, 255, 255));
			SelectObject(hdc1, newBrush);
			tPoints[0].x = 5;
			tPoints[0].y = 20;
			tPoints[1].x = 10;
			tPoints[1].y = 0;
			tPoints[2].x = 15;
			tPoints[2].y = 20;
			tPoints[3].x = 0;
			tPoints[3].y = 10;
			tPoints[4].x = 20;
			tPoints[4].y = 10;
			tPoints[5].x = 5;
			tPoints[5].y = 20;

			Polygon(hdc1, tPoints, 6);
			tPoints[0].x = rect.right - 15;
			tPoints[0].y = 20;
			tPoints[1].x = rect.right - 10;
			tPoints[1].y = 0;
			tPoints[2].x = rect.right - 5;
			tPoints[2].y = 20;
			tPoints[3].x = rect.right - 20;
			tPoints[3].y = 10;
			tPoints[4].x = rect.right;
			tPoints[4].y = 10;
			tPoints[5].x = rect.right - 15;
			tPoints[5].y = 20;
			Polygon(hdc1, tPoints, 6);

			tPoints[0].x = rect.right - 15;
			tPoints[0].y = rect.bottom;
			tPoints[1].x = rect.right - 10;
			tPoints[1].y = rect.bottom - 20;
			tPoints[2].x = rect.right - 5;
			tPoints[2].y = rect.bottom;
			tPoints[3].x = rect.right - 20;
			tPoints[3].y = rect.bottom - 10;
			tPoints[4].x = rect.right;
			tPoints[4].y = rect.bottom - 10;
			tPoints[5].x = rect.right - 15;
			tPoints[5].y = rect.bottom;
			Polygon(hdc1, tPoints, 6);

			tPoints[0].x = 5;
			tPoints[0].y = rect.bottom;
			tPoints[1].x = 10;
			tPoints[1].y = rect.bottom - 20;
			tPoints[2].x = 15;
			tPoints[2].y = rect.bottom;
			tPoints[3].x = 0;
			tPoints[3].y = rect.bottom - 10;
			tPoints[4].x = 20;
			tPoints[4].y = rect.bottom - 10;
			tPoints[5].x = 5;
			tPoints[5].y = rect.bottom;
			Polygon(hdc1, tPoints, 6);
			ReleaseDC(hWnd, hdc1);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		SetBkColor(hdc, RGB(255, 0, 0));
		SelectObject(hdc, newBrush);
		for (int i = 0; i < rect.right; i += 20)
		{
			for (int j = 0; j < rect.bottom; j += 20)
			{
				Rectangle(hdc, i, j, i + 20, j + 20);
				char symbol = digit + '0';
				TextOut(hdc, i, j, buffer, wsprintf(buffer, "%c",symbol));
				digit++;
				SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
			}
			newBrush = CreateSolidBrush(RGB(255, h+=2.5, 0));
			SelectObject(hdc, newBrush);
			SetBkColor(hdc, RGB(255, q+=2.5, 0));
		}
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
