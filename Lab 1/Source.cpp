#include <windows.h>// підключення бібліотеки з функціями API
#include "resource.h"
// Глобальні змінні: 
HINSTANCE hInst; 	//Дескриптор програми	
LPCTSTR szWindowClass = "Tykhomyrov Valentyn KIUKI 18-2";
LPCTSTR szTitle = "ПЕРША ПРОГРАМА";

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

int CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:  //ініціалізація функціоналу керування діалоговим вікном
		return TRUE;

		//цикл обробки натискання елементів на формі діалогового вікна
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			EndDialog(hDlg, LOWORD(wParam));//знищення модального діалогового вікна
			return TRUE;
		}
		if (LOWORD(wParam) == IDCANCEL)
		{
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG2), hDlg, DlgProc);
		}
		if (LOWORD(wParam) == IDCANCEL13)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		if (LOWORD(wParam) == IDOK13)
		{
			PostQuitMessage(0);
		}
		break;
	}
	return FALSE;
}


ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS; 		//стиль вікна
	wcex.lpfnWndProc = (WNDPROC)WndProc; 		//віконна процедура
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance; 			//дескриптор програми
	wcex.hIcon = LoadIcon(NULL, IDI_QUESTION); 		//визначення іконки
	wcex.hCursor = LoadCursor(NULL, IDC_CROSS); 	//визначення курсору
	wcex.hbrBackground = GetSysColorBrush(COLOR_WINDOW); //установка фону
	wcex.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1); 				//визначення меню
	wcex.lpszClassName = szWindowClass; 		//ім’я класу
	wcex.hIconSm = NULL;

	return RegisterClassEx(&wcex); 			//реєстрація класу вікна
}

// FUNCTION: InitInstance (HANDLE, int)
// Створює вікно програми і зберігає дескриптор програми в змінній hInst

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hInst = hInstance; //зберігає дескриптор додатка в змінній hInst
	hWnd = CreateWindow(szWindowClass, 	// ім’я класу вікна
		szTitle, 				// назва програми
		WS_MINIMIZEBOX | WS_BORDER | WS_SYSMENU,			// стиль вікна
		570, 			// положення по Х	
		300,			// положення по Y	
		200, 			// розмір по Х
		150, 			// розмір по Y
		NULL, 					// дескриптор батьківського вікна	
		NULL, 					// дескриптор меню вікна
		hInstance, 				// дескриптор програми
		NULL); 				// параметри створення.

	if (!hWnd) 	//Якщо вікно не творилось, функція повертає FALSE
	{
		return FALSE;
	}
	ShowWindow(hWnd, SW_MINIMIZE); 		//Показати вікно
	UpdateWindow(hWnd); 				//Оновити вікно
	return TRUE;
}



// FUNCTION: WndProc (HWND, unsigned, WORD, LONG)
// Віконна процедура. Приймає і обробляє всі повідомлення, що приходять в додаток


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rt;
	char buffer[20];
	HBRUSH newBackGround;
	LPCSTR header;
	switch (message)
	{
	case WM_INITDIALOG:
		LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU1));//creating of menu
		break;

	case WM_LBUTTONDBLCLK:
		MessageBox(hWnd, "Double click", "It's work", MB_OK);
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_TOOLS_POINTER:
			SetClassLong(hWnd, GCL_HCURSOR, (LONG)LoadCursor(hInst, MAKEINTRESOURCE(IDC_CURSOR1)));
			break;
		case ID_TOOLS_BACKGROUND:
			newBackGround = CreateSolidBrush(RGB(0, 255, 0));
			SetClassLong(hWnd, GCL_HBRBACKGROUND, (LONG)newBackGround);
			InvalidateRect(hWnd, NULL, TRUE);
			UpdateWindow(hWnd);
			break;
		case ID_TOOLS_ICON:
			SetClassLong(hWnd, GCL_HICON, (LONG)LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1)));
			break;
		case ID_TOOLS_HEADER:
			LoadString(hInst, 106,buffer, sizeof(buffer));
			SetWindowText(hWnd, (LPCTSTR)buffer);
			InvalidateRect(hWnd, NULL, TRUE);
			UpdateWindow(hWnd);
			break;
		case ID_INFO:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DlgProc);
		default:
			break;
		}
		break;
	case WM_PAINT: //Перемалювати вікно
		int nHeight;
		hdc = BeginPaint(hWnd, &ps); 	//Почати графічний вивід	
		GetClientRect(hWnd, &rt); 		//Область вікна для малювання
		EndPaint(hWnd, &ps); 		//Закінчити графічний вивід
		break;
	case WM_CLOSE:
		if (wParam == SC_CLOSE)
		{
			if ((::GetAsyncKeyState(VK_MENU)) && (::GetAsyncKeyState(VK_F4)))
				return NULL;
		}
		break;
	case WM_DESTROY: 				//Завершення роботи
		PostQuitMessage(0);
		break;
	default:
		//Обробка повідомлень, які не оброблені користувачем
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}



