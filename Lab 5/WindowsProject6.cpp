#include"stdafx.h"
#include <windows.h> // підключення бібліотеки з функціями API
#include "resource.h"
#include "time.h"
#include <process.h>
#include <stack>

// Глобальні змінні:
std::stack<PROCESS_INFORMATION> SrackPi;
HINSTANCE hInst; 	//Дескриптор програми	
CRITICAL_SECTION sc;
int mass[10][10];
WCHAR buff[100];
WCHAR lspzName[] = L"Новый текстовый документ.txt";

// Попередній опис функцій

ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
// Основна програма 
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,
	int nCmdShow)
{
	MSG msg;

	// Реєстрація класу вікна 
	MyRegisterClass(hInstance);

	// Створення вікна програми
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}
	// Цикл обробки повідомлень
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW; 		//стиль вікна
	wcex.lpfnWndProc = (WNDPROC)WndProc; 		//віконна процедура
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance; 			//дескриптор програми
	wcex.hIcon = LoadIcon(NULL, IDI_HAND); 		//визначення іконки
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW); 	//визначення курсору
	wcex.hbrBackground = GetSysColorBrush(COLOR_WINDOW); //установка фону
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_WINDOWSPROJECT6); 				//визначення меню
	wcex.lpszClassName = L"QWERTY"; 		//ім’я класу
	wcex.hIconSm = NULL;

	return RegisterClassEx(&wcex); 			//реєстрація класу вікна
}

// FUNCTION: InitInstance (HANDLE, int)
// Створює вікно програми і зберігає дескриптор програми в змінній hInst

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hInst = hInstance; //зберігає дескриптор додатка в змінній hInst
	hWnd = CreateWindow(L"QWERTY", 	// ім’я класу вікна
		L"ПЕРША ПРОГРАМА", 				// назва програми
		WS_OVERLAPPEDWINDOW,			// стиль вікна
		CW_USEDEFAULT, 			// положення по Х	
		CW_USEDEFAULT,			// положення по Y	
		CW_USEDEFAULT, 			// розмір по Х
		CW_USEDEFAULT, 			// розмір по Y
		NULL, 					// дескриптор батьківського вікна	
		NULL, 					// дескриптор меню вікна
		hInstance, 				// дескриптор програми
		NULL); 				// параметри створення.

	if (!hWnd) 	//Якщо вікно не творилось, функція повертає FALSE
	{
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow); 		//Показати вікно
	UpdateWindow(hWnd); 				//Оновити вікно
	return TRUE;
}

// FUNCTION: WndProc (HWND, unsigned, WORD, LONG)
// Віконна процедура. Приймає і обробляє всі повідомлення, що приходять в додаток
DWORD WINAPI RstMass(LPVOID t)
{
	EnterCriticalSection(&sc);
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			mass[i][j] = 0;
	LeaveCriticalSection(&sc);
	ExitThread(0);
}
DWORD WINAPI FillingMass(LPVOID t)
{
	srand(time(0));
	EnterCriticalSection(&sc);
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			mass[i][j] = rand() % 500;
	LeaveCriticalSection(&sc);
	ExitThread(1);
}
DWORD WINAPI PrintMass(LPVOID t)
{
	HDC c;
	c = GetDC(FindWindow(L"QWERTY", L"ПЕРША ПРОГРАМА"));
	EnterCriticalSection(&sc);
	InvalidateRect(FindWindow(L"QWERTY", L"ПЕРША ПРОГРАМА"), NULL, TRUE);
	UpdateWindow(FindWindow(L"QWERTY", L"ПЕРША ПРОГРАМА"));
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			TextOut(c, 10 + (20 * j), 10 + (i * 20), buff, wsprintf(buff, L" %d", mass[i][j]));
	LeaveCriticalSection(&sc);
	ExitThread(2);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PROCESS_INFORMATION pi;
	STARTUPINFO sti;
	HANDLE hThread[3];
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rt;
	LPDWORD Dw;

	switch (message)
	{
	case WM_CREATE: 				//Повідомлення приходить при створенні вікна
		SetTimer(hWnd, 1, 3000, NULL);
		InitializeCriticalSection(&sc);
		break;
	case WM_TIMER:
		hThread[0] = CreateThread(NULL, 0, &RstMass, NULL, 0, NULL);
		hThread[1] = CreateThread(NULL, 0, &FillingMass, NULL, 0, NULL);
		hThread[2] = CreateThread(NULL, 0, &PrintMass, NULL, 0, NULL);
		InvalidateRect(hWnd, NULL, FALSE);
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_40001:
			ZeroMemory(&sti, sizeof(STARTUPINFO));	// обнулить
			sti.cb = sizeof(STARTUPINFO);
			SrackPi.push(pi);
			if (!CreateProcess(L"c:\\windows\\notepad.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sti, &SrackPi.top()))
				MessageBox(hWnd, L"Error of creating of new process...", L"Erorr", MB_OK);
			break;
		case ID_40002:
			if (SrackPi.empty())
				MessageBox(hWnd, L"Error of closing new process...", L"Erorr", MB_OK);
			else
			{
				TerminateProcess(SrackPi.top().hProcess, 0);
				SrackPi.pop();
			}
			break;
		case ID_40003:
			while (!SrackPi.empty())
			{
				TerminateProcess(SrackPi.top().hProcess, 0);
				SrackPi.pop();
			}
			ExitProcess(0);
			break;
		}
		break;
	case WM_PAINT: 				//Перемалювати вікно
		hdc = BeginPaint(hWnd, &ps); 	//Почати графічний вивід	
		GetClientRect(hWnd, &rt); 		//Область вікна для малювання
		TextOut(hdc, 200, 200, buff, wsprintf(buff, "dwProcessId = %4d, dwThreadId = %4d, hProcess = %4d, hThread = %4d ", pi.dwProcessId, pi.dwThreadId, pi.hProcess, pi.hThread));
		EndPaint(hWnd, &ps); 		//Закінчити графічний вивід	
		break;

	case WM_DESTROY: 				//Завершення роботи
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		break;
	default:
		//Обробка повідомлень, які не оброблені користувачем
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
