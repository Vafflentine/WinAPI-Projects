// WindowsProject5.cpp : Определяет точку входа для приложения.
//

#include "stdafx.h"
#include "WindowsProject5.h"

#define MAX_LOADSTRING 100
#define ID_LISTBOX 100;
#define ID_PUSHBUTTON 101;
#define ID_DEFPUSHBUTTON 102;
#define ID_CHECKBOX 103;
#define ID_AUTOCHECKBOX 104;
#define ID_RADIOBUTTON 105;
#define ID_AUTO3STATE 107;
#define ID_GROUPBOX 108;
#define ID_AUTORADIOBUTTON 109;
#define ID_OWNERDRAW 110;

int xPos, yPos;        // current horizontal scrolling position 
static int Hscroll, Vscroll;
HWND hScroll;// Идентификатор окна полосы просмотра

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
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

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT5, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT5));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT5));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT5);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

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
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
HWND hListBox, PushButton, CheckBox, RadioButtons, hwndStaticWindow, AutoCheckBox, DefPushButton, hwndEdit, AutoRadioButtons, Scrollbar;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static WORD cxClient, cyClient;
	static  int a;
	int index;
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rt;
	switch (message)
	{
	case WM_CREATE: 				//Повідомлення приходить при створенні вікна
		Hscroll = 10; // Устанавливаем текущую позицию
		Vscroll = 10;
		SetScrollRange(hWnd, SB_HORZ, 0, 50, TRUE); // Устанавливаем минимальное и максимальное значения для полосы просмотра
		SetScrollRange(hWnd, SB_VERT, 0, 50, TRUE);
		hListBox = CreateWindow(L"ListBox", NULL, WS_CHILD | WS_VISIBLE | LBS_STANDARD, 30, 30, 100, 100, hWnd, (HMENU)100, NULL, NULL);
		if (!hListBox)return FALSE;
		SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)"Кучков");
		SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)"Тихомиров");
		//ShowWindow(hListBox, SW_NORMAL);
		UpdateWindow(hListBox);
		break;
	case WM_HSCROLL:
	{
		switch (wParam)
		{
		case SB_LEFT:
		{
			Hscroll = 0;
			break;
		}
		case SB_RIGHT:
		{
			Hscroll = 50;
			break;
		}
		case SB_LINELEFT:
		{
			Hscroll -= 1;
			break;
		}
		case SB_LINERIGHT:
		{
			Hscroll += 1;
			break;
		}
		case SB_PAGELEFT:
		{
			Hscroll -= 5;
			break;
		}
		case SB_PAGERIGHT:
		{
			Hscroll += 5;
			break;
		}
		case SB_THUMBPOSITION:
		{
			Hscroll = LOWORD(lParam);
			break;
		}
		// Блокируем для того чтобы избежать
		// мерцания содержимого окна при
		// перемещении ползунка
		case SB_THUMBTRACK:
		{
			Hscroll = LOWORD(lParam);
			return 0;
		}
		default:
			break;
		}

		// Ограничиваем диапазон изменения значений
		if (Hscroll > 50) Hscroll = 50;
		if (Hscroll < 1) Hscroll = 0;

		// Устанавливаем ползунок в новое положение
		if (Hscroll != xPos)
		{
			ScrollWindow(hWnd, 10 * (xPos - Hscroll), 0, NULL, NULL);
			UpdateWindow(hWnd);
		}
		SetScrollPos(hWnd, SB_HORZ, Hscroll, TRUE);
		return 0;
	}
	case WM_VSCROLL:
	{
		switch (wParam)
		{
		case SB_TOP:
		{
			Vscroll = 0;
			break;
		}
		case SB_BOTTOM:
		{
			Vscroll = 50;
			break;
		}
		case SB_LINEUP:
		{
			Vscroll -= 1;
			break;
		}
		case SB_LINEDOWN:
		{
			Vscroll += 1;
			break;
		}
		case SB_PAGEUP:
		{
			Vscroll -= 5;
			break;
		}
		case SB_PAGEDOWN:
		{
			Vscroll += 5;
			break;
		}
		case SB_THUMBPOSITION:
		{
			Vscroll = LOWORD(lParam);
			break;
		}
		// Блокируем для того чтобы избежать
		// мерцания содержимого окна при
		// перемещении ползунка
		case SB_THUMBTRACK:
		{
			return 0;
		}
		default:
			break;
		}

		// Ограничиваем диапазон изменения значений
		if (Vscroll > 50) Vscroll = 50;
		if (Vscroll < 0) Vscroll = 0;

		// Устанавливаем ползунок в новое положение
		SetScrollPos(hWnd, SB_VERT, Vscroll, TRUE);
		if (Vscroll != yPos)
		{
			ScrollWindow(hWnd, 0, 10 * (yPos - Vscroll), NULL, NULL);
			UpdateWindow(hWnd);
		}
		return 0;
	}
	case WM_COMMAND:
		switch (HIWORD(wParam))
		{
		case LBN_DBLCLK:
			a = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
			if (a == 0)
			{
				DestroyWindow(PushButton);
				DestroyWindow(DefPushButton);
				DestroyWindow(CheckBox);
				DestroyWindow(AutoCheckBox);
				DestroyWindow(RadioButtons);
				DestroyWindow(hwndStaticWindow);
				DestroyWindow(hwndEdit);
				DestroyWindow(AutoRadioButtons);

				PushButton = CreateWindow(L"button", L"Кучков", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 135, 30, 150, 50, hWnd, (HMENU)101, NULL, NULL);
				DefPushButton = CreateWindow(L"button", L"Кучков", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 135, 80, 150, 50, hWnd, (HMENU)102, NULL, NULL);
				CheckBox = CreateWindow(L"button", L"Кучков", WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 135, 130, 150, 50, hWnd, (HMENU)103, NULL, NULL);
				AutoCheckBox = CreateWindow(L"button", L"Кучков", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 135, 180, 150, 50, hWnd, (HMENU)104, NULL, NULL);
				RadioButtons = CreateWindow(L"button", L"Кучков", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, 135, 230, 150, 50, hWnd, (HMENU)105, NULL, NULL);
				hwndStaticWindow = CreateWindow(L"static", L"Кучков", WS_CHILD | WS_VISIBLE | SS_CENTER, 135, 380, 150, 50, hWnd, (HMENU)106, NULL, NULL);
				hwndEdit = CreateWindow(L"edit", L"Кучков", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT, 135, 330, 150, 50, hWnd, (HMENU)107, NULL, NULL);
				AutoRadioButtons = CreateWindow(L"button", L"Кучков", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 135, 280, 150, 50, hWnd, (HMENU)108, NULL, NULL);
			}
			else if (a == 1)
			{
				DestroyWindow(PushButton);
				DestroyWindow(DefPushButton);
				DestroyWindow(CheckBox);
				DestroyWindow(AutoCheckBox);
				DestroyWindow(RadioButtons);
				DestroyWindow(hwndStaticWindow);
				DestroyWindow(hwndEdit);
				DestroyWindow(AutoRadioButtons);

				PushButton = CreateWindow(L"button", L"Тихомиров", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 135, 30, 150, 50, hWnd, (HMENU)101, NULL, NULL);
				DefPushButton = CreateWindow(L"button", L"Тихомиров", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 135, 80, 150, 50, hWnd, (HMENU)102, NULL, NULL);
				CheckBox = CreateWindow(L"button", L"Тихомиров", WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 135, 130, 150, 50, hWnd, (HMENU)103, NULL, NULL);
				AutoCheckBox = CreateWindow(L"button", L"Тихомиров", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 135, 180, 150, 50, hWnd, (HMENU)104, NULL, NULL);
				RadioButtons = CreateWindow(L"button", L"Тихомиров", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, 135, 230, 150, 50, hWnd, (HMENU)105, NULL, NULL);
				hwndStaticWindow = CreateWindow(L"static", L"Тихомиров", WS_CHILD | WS_VISIBLE | SS_CENTER, 135, 380, 150, 50, hWnd, (HMENU)106, NULL, NULL);
				hwndEdit = CreateWindow(L"edit", L"Тихомиров", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 135, 330, 150, 50, hWnd, (HMENU)107, NULL, NULL);
				AutoRadioButtons = CreateWindow(L"button", L"Тихомиров", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 135, 280, 150, 50, hWnd, (HMENU)108, NULL, NULL);
			}

			InvalidateRect(hWnd, NULL, TRUE);
			break;
		default:
			break;
		}
		break;
	case WM_SIZE:
	{
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		return 0;
		break;
	}
	case WM_PAINT: 				//Перемалювати вікно
	{
		hdc = BeginPaint(hWnd, &ps); 	//Почати графічний вивід	
		GetClientRect(hWnd, &rt); 		//Область вікна для малювання
		yPos = Vscroll;
		xPos = Hscroll;
		ShowWindow(hListBox, SW_SHOW);
		EndPaint(hWnd, &ps); 		//Закінчити графічний вивід	
		break;
	}
	case WM_DESTROY: 				//Завершення роботи
		PostQuitMessage(0);
		break;
	default:
		//Обробка повідомлень, які не оброблені користувачем
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
