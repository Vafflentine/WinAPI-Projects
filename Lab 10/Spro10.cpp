// Spro10.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Spro10.h"
#include<ctime>
#include <stack>
#define MAX_LOADSTRING 100
#define ID_CLOCK 1
#define ID_CHOOSE1 200
#define ID_CHOOSE2 300
#define ID_CHOOSE3 400
#define ID_CHOOSE4 500
// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
std::stack<PROCESS_INFORMATION> SrackPi;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Dialog(HWND, UINT, WPARAM, LPARAM);
void showClock(HWND hClock, HDC hdc);
void showSecondMode(HDC hdc1);
void createListBoxes(HWND hwnd[4],HWND parent);
void RefreshWindow(HWND hwnd[4], HWND parent);
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SPRO10));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SPRO10));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SPRO10);
    wcex.lpszClassName  = L"Spro10";
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

   HWND hWnd = CreateWindow("Spro10","SPRO", WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, SW_MAXIMIZE);
   UpdateWindow(hWnd);

   return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	RECT clock;
	clock.bottom = 55;
	clock.left = 1747;
	clock.top = 2;
	clock.right = 1920;
	PROCESS_INFORMATION pi;
	STARTUPINFO sti;
	static LOGFONT lf; //создаём экземпляр структуры LOGFONT
	HFONT hFont;
	static HWND hClock;
	HDC hdc1;
	static HWND hChoose[4];
	int counter;
	char buffer[24];
    switch (message)
    {
	case WM_CREATE:
	{
		SetTimer(hWnd, 1, 1000, NULL);
		lf.lfCharSet = DEFAULT_CHARSET; //заполняем необходимые поля
		lf.lfHeight = 50;
		hClock = CreateWindow(_T("edit"), _T(""), WS_CHILD | WS_VISIBLE | ES_RIGHT, 1747, 2, 1920, 55, hWnd, (HMENU)ID_CLOCK, hInst, 0);
	}
		break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
			switch (wmId)
			{
			case ID_FIRST:
			{
			case ID_EXE1:
				while (!SrackPi.empty())
				{
					TerminateProcess(SrackPi.top().hProcess, 0);
					SrackPi.pop();
				}
				RefreshWindow(hChoose, hWnd);
				ZeroMemory(&sti, sizeof(STARTUPINFO));	// обнулить
				sti.cb = sizeof(STARTUPINFO);
				SrackPi.push(pi);
				if (!CreateProcess("C:\\Users\\Admin\\source\\repos\\Spro10\\CRT_SECURE_NO_WARNINGS\\Project3.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sti, &SrackPi.top()))
					MessageBox(hWnd, "Error of creating of new process...", "Erorr", MB_OK);
				break;
			case ID_EXE2:
				while (!SrackPi.empty())
				{
					TerminateProcess(SrackPi.top().hProcess, 0);
					SrackPi.pop();
				}
				RefreshWindow(hChoose, hWnd);
				ZeroMemory(&sti, sizeof(STARTUPINFO));	// обнулить
				sti.cb = sizeof(STARTUPINFO);
				SrackPi.push(pi);
				if (!CreateProcess("C:\\Users\\Admin\\source\\repos\\Spro10\\CRT_SECURE_NO_WARNINGS\\WindowsProject1.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sti, &SrackPi.top()))
					MessageBox(hWnd, "Error of creating of new process...", "Erorr", MB_OK);
				break;
			case ID_EXE3:
				while (!SrackPi.empty())
				{
					TerminateProcess(SrackPi.top().hProcess, 0);
					SrackPi.pop();
				}
				RefreshWindow(hChoose, hWnd);
				ZeroMemory(&sti, sizeof(STARTUPINFO));	// обнулить
				sti.cb = sizeof(STARTUPINFO);
				SrackPi.push(pi);
				if (!CreateProcess("C:\\Users\\Admin\\source\\repos\\Spro10\\CRT_SECURE_NO_WARNINGS\\WindowsProject2.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sti, &SrackPi.top()))
					MessageBox(hWnd, "Error of creating of new process...", "Erorr", MB_OK);
				break;
			case ID_EXE4:
				while (!SrackPi.empty())
				{
					TerminateProcess(SrackPi.top().hProcess, 0);
					SrackPi.pop();
				}
				RefreshWindow(hChoose, hWnd);
				ZeroMemory(&sti, sizeof(STARTUPINFO));	// обнулить
				sti.cb = sizeof(STARTUPINFO);
				SrackPi.push(pi);
				if (!CreateProcess("C:\\Users\\Admin\\source\\repos\\Spro10\\CRT_SECURE_NO_WARNINGS\\WindowsProject5.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sti, &SrackPi.top()))
					MessageBox(hWnd, "Error of creating of new process...", "Erorr", MB_OK);
				break;
			case ID_EXE5:
				while (!SrackPi.empty())
				{
					TerminateProcess(SrackPi.top().hProcess, 0);
					SrackPi.pop();
				}
				RefreshWindow(hChoose, hWnd);
				ZeroMemory(&sti, sizeof(STARTUPINFO));	// обнулить
				sti.cb = sizeof(STARTUPINFO);
				SrackPi.push(pi);
				if (!CreateProcess("C:\\Users\\Admin\\source\\repos\\Spro10\\CRT_SECURE_NO_WARNINGS\\WindowsProject6.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sti, &SrackPi.top()))
					MessageBox(hWnd, "Error of creating of new process...", "Erorr", MB_OK);
				break;
			case ID_EXE6:
				while (!SrackPi.empty())
				{
					TerminateProcess(SrackPi.top().hProcess, 0);
					SrackPi.pop();
				}
				RefreshWindow(hChoose, hWnd);
				ZeroMemory(&sti, sizeof(STARTUPINFO));	// обнулить
				sti.cb = sizeof(STARTUPINFO);
				SrackPi.push(pi);
				if (!CreateProcess("C:\\Users\\Admin\\source\\repos\\Spro10\\CRT_SECURE_NO_WARNINGS\\spro6.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sti, &SrackPi.top()))
					MessageBox(hWnd, "Error of creating of new process...", "Erorr", MB_OK);
				break;
			case ID_EXE7:
				while (!SrackPi.empty())
				{
					TerminateProcess(SrackPi.top().hProcess, 0);
					SrackPi.pop();
				}
				RefreshWindow(hChoose, hWnd);
				ZeroMemory(&sti, sizeof(STARTUPINFO));	// обнулить
				sti.cb = sizeof(STARTUPINFO);
				SrackPi.push(pi);
				if (!CreateProcess("C:\\Users\\Admin\\source\\repos\\Spro10\\CRT_SECURE_NO_WARNINGS\\Spro7.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sti, &SrackPi.top()))
					MessageBox(hWnd, "Error of creating of new process...", "Erorr", MB_OK);
				break;
			case ID_EXE8:
				while (!SrackPi.empty())
				{
					TerminateProcess(SrackPi.top().hProcess, 0);
					SrackPi.pop();
				}
				RefreshWindow(hChoose, hWnd);
				ZeroMemory(&sti, sizeof(STARTUPINFO));	// обнулить
				sti.cb = sizeof(STARTUPINFO);
				SrackPi.push(pi);
				if (!CreateProcess("C:\\Users\\Admin\\source\\repos\\Spro10\\CRT_SECURE_NO_WARNINGS\\Spro8 v2.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sti, &SrackPi.top()))
					MessageBox(hWnd, "Error of creating of new process...", "Erorr", MB_OK);
				break;
			case ID_EXE9:
				while (!SrackPi.empty())
				{
					TerminateProcess(SrackPi.top().hProcess, 0);
					SrackPi.pop();
				}
				RefreshWindow(hChoose, hWnd);
				ZeroMemory(&sti, sizeof(STARTUPINFO));	// обнулить
				sti.cb = sizeof(STARTUPINFO);
				SrackPi.push(pi);
				if (!CreateProcess("C:\\Users\\Admin\\source\\repos\\Spro10\\CRT_SECURE_NO_WARNINGS\\Spro9 v2.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sti, &SrackPi.top()))
					MessageBox(hWnd, "Error of creating of new process...", "Erorr", MB_OK);
				break;
			}
			break;
			case ID_SECOND:
				if (SrackPi.empty())
					MessageBox(hWnd, "Error of closing new process...", "Erorr", MB_OK);
				else
				{
					while (!SrackPi.empty())
					{
						TerminateProcess(SrackPi.top().hProcess, 0);
						SrackPi.pop();
					}
				}
				hdc1 = GetDC(hWnd);
				showSecondMode(hdc1);
				createListBoxes(hChoose, hWnd);
				ReleaseDC(hWnd, hdc1);
				break;
			case ID_CHOOSE1:// первый комбобокс(верхний левый)
			{
				if (CBN_SELCHANGE == HIWORD(wParam))
				{
					 counter = SendMessage(hChoose[0], CB_GETCURSEL, 0, 0);
				}
				if (counter == 0)
				{
					ZeroMemory(&sti, sizeof(STARTUPINFO));	// обнулить
					sti.cb = sizeof(STARTUPINFO);
					sti.dwX = -5;
					sti.dwY = 66;
					sti.dwXSize = 972;
					sti.dwYSize = 450;
					sti.dwFlags = STARTF_USESIZE | STARTF_USEPOSITION;
					SrackPi.push(pi);
					if (!CreateProcess("C:\\Users\\Admin\\source\\repos\\Spro10\\CRT_SECURE_NO_WARNINGS\\Project3.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sti, &SrackPi.top()))// вот тут создаёт 5 окон вместо 1
						MessageBox(hWnd, "Error of creating of new process...", "Erorr", MB_OK);
				}
				if (counter == 1)
				{
					ZeroMemory(&sti, sizeof(STARTUPINFO));	// обнулить
					sti.cb = sizeof(STARTUPINFO);
					sti.dwX = -5;
					sti.dwY = 66;
					sti.dwXSize = 972;
					sti.dwYSize = 450;
					sti.dwFlags = STARTF_USESIZE | STARTF_USEPOSITION;
					SrackPi.push(pi);
					if(!CreateProcess("C:\\Users\\Admin\\source\\repos\\Spro10\\CRT_SECURE_NO_WARNINGS\\WindowsProject1.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sti, &SrackPi.top()))// вот тут создаёт 5 окон вместо 1
						MessageBox(hWnd, "Error of creating of new process...", "Erorr", MB_OK);
				}
				if (counter == 2)
				{
					ZeroMemory(&sti, sizeof(STARTUPINFO));	// обнулить
					sti.cb = sizeof(STARTUPINFO);
					sti.dwX = -5;
					sti.dwY = 66;
					sti.dwXSize = 972;
					sti.dwYSize = 450;
					sti.dwFlags = STARTF_USESIZE | STARTF_USEPOSITION;
					SrackPi.push(pi);
					if (!CreateProcess("C:\\Users\\Admin\\source\\repos\\Spro10\\CRT_SECURE_NO_WARNINGS\\WindowsProject2.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sti, &SrackPi.top()))// вот тут создаёт 5 окон вместо 1
						MessageBox(hWnd, "Error of creating of new process...", "Erorr", MB_OK);
				}
				if (counter == 3)
				{
					ZeroMemory(&sti, sizeof(STARTUPINFO));	// обнулить
					sti.cb = sizeof(STARTUPINFO);
					sti.dwX = -5;
					sti.dwY = 66;
					sti.dwXSize = 972;
					sti.dwYSize = 450;
					sti.dwFlags = STARTF_USESIZE | STARTF_USEPOSITION;
					SrackPi.push(pi);
					if (!CreateProcess("C:\\Users\\Admin\\source\\repos\\Spro10\\CRT_SECURE_NO_WARNINGS\\WindowsProject5.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sti, &SrackPi.top()))
						MessageBox(hWnd, "Error of creating of new process...", "Erorr", MB_OK);
				}
				if (counter == 4)
				{
					ZeroMemory(&sti, sizeof(STARTUPINFO));	// обнулить
					sti.cb = sizeof(STARTUPINFO);
					sti.dwX = -5;
					sti.dwY = 66;
					sti.dwXSize = 972;
					sti.dwYSize = 450;
					sti.dwFlags = STARTF_USESIZE | STARTF_USEPOSITION;
					SrackPi.push(pi);
					if (!CreateProcess("C:\\Users\\Admin\\source\\repos\\Spro10\\CRT_SECURE_NO_WARNINGS\\WindowsProject6.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sti, &SrackPi.top()))
						MessageBox(hWnd, "Error of creating of new process...", "Erorr", MB_OK);
				}
				if (counter == 5)
				{
					ZeroMemory(&sti, sizeof(STARTUPINFO));	// обнулить
					sti.cb = sizeof(STARTUPINFO);
					sti.dwX = -5;
					sti.dwY = 66;
					sti.dwXSize = 972;
					sti.dwYSize = 450;
					sti.dwFlags = STARTF_USESIZE | STARTF_USEPOSITION;
					SrackPi.push(pi);
					if (!CreateProcess("C:\\Users\\Admin\\source\\repos\\Spro10\\CRT_SECURE_NO_WARNINGS\\spro6.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sti, &SrackPi.top()))
						MessageBox(hWnd, "Error of creating of new process...", "Erorr", MB_OK);
				}
				if (counter == 6)
				{
					ZeroMemory(&sti, sizeof(STARTUPINFO));	// обнулить
					sti.cb = sizeof(STARTUPINFO);
					sti.dwX = -5;
					sti.dwY = 66;
					sti.dwXSize = 972;
					sti.dwYSize = 450;
					sti.dwFlags = STARTF_USESIZE | STARTF_USEPOSITION;
					SrackPi.push(pi);
					if (!CreateProcess("C:\\Users\\Admin\\source\\repos\\Spro10\\CRT_SECURE_NO_WARNINGS\\Spro7.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sti, &SrackPi.top()))
						MessageBox(hWnd, "Error of creating of new process...", "Erorr", MB_OK);
				}
				if (counter == 7)
				{
					ZeroMemory(&sti, sizeof(STARTUPINFO));	// обнулить
					sti.cb = sizeof(STARTUPINFO);
					sti.dwX = -5;
					sti.dwY = 66;
					sti.dwXSize = 972;
					sti.dwYSize = 450;
					sti.dwFlags = STARTF_USESIZE | STARTF_USEPOSITION;
					SrackPi.push(pi);
					if (!CreateProcess("C:\\Users\\Admin\\source\\repos\\Spro10\\CRT_SECURE_NO_WARNINGS\\Spro8 v2.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sti, &SrackPi.top()))
						MessageBox(hWnd, "Error of creating of new process...", "Erorr", MB_OK);
				}
				if (counter == 8)
				{
					ZeroMemory(&sti, sizeof(STARTUPINFO));	// обнулить
					sti.cb = sizeof(STARTUPINFO);
					sti.dwX = -5;
					sti.dwY = 66;
					sti.dwXSize = 972;
					sti.dwYSize = 450;
					sti.dwFlags = STARTF_USESIZE | STARTF_USEPOSITION;
					SrackPi.push(pi);
					if (!CreateProcess("C:\\Users\\Admin\\source\\repos\\Spro10\\CRT_SECURE_NO_WARNINGS\\Spro9 v2.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sti, &SrackPi.top()))
						MessageBox(hWnd, "Error of creating of new process...", "Erorr", MB_OK);
				}
			}
			break;
			case ID_CHOOSE2:// первый комбобокс(верхний левый)
			{
				if (CBN_SELCHANGE == HIWORD(wParam))
				{
					counter = SendMessage(hChoose[1], CB_GETCURSEL, 0, 0);
				}
				if (counter == 0)
				{
					ZeroMemory(&sti, sizeof(STARTUPINFO));	// обнулить
					sti.cb = sizeof(STARTUPINFO);
					sti.dwX = -5;
					sti.dwY = 535;
					sti.dwXSize = 972;
					sti.dwYSize = 500;
					sti.dwFlags = STARTF_USESIZE | STARTF_USEPOSITION;
					SrackPi.push(pi);
					if (!CreateProcess("C:\\Users\\Admin\\source\\repos\\Spro10\\CRT_SECURE_NO_WARNINGS\\Project3.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sti, &SrackPi.top()))// вот тут создаёт 5 окон вместо 1
						MessageBox(hWnd, "Error of creating of new process...", "Erorr", MB_OK);
				}
				if (counter == 1)
				{
					ZeroMemory(&sti, sizeof(STARTUPINFO));	// обнулить
					sti.cb = sizeof(STARTUPINFO);
					sti.dwX = -5;
					sti.dwY = 535;
					sti.dwXSize = 972;
					sti.dwYSize = 500;
					sti.dwFlags = STARTF_USESIZE | STARTF_USEPOSITION;
					SrackPi.push(pi);
					if (!CreateProcess("C:\\Users\\Admin\\source\\repos\\Spro10\\CRT_SECURE_NO_WARNINGS\\WindowsProject1.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sti, &SrackPi.top()))// вот тут создаёт 5 окон вместо 1
						MessageBox(hWnd, "Error of creating of new process...", "Erorr", MB_OK);
				}
				if (counter == 2)
				{
					ZeroMemory(&sti, sizeof(STARTUPINFO));	// обнулить
					sti.cb = sizeof(STARTUPINFO);
					sti.dwX = -5;
					sti.dwY = 535;
					sti.dwXSize = 972;
					sti.dwYSize = 500;
					sti.dwFlags = STARTF_USESIZE | STARTF_USEPOSITION;
					SrackPi.push(pi);
					if (!CreateProcess("C:\\Users\\Admin\\source\\repos\\Spro10\\CRT_SECURE_NO_WARNINGS\\WindowsProject2.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sti, &SrackPi.top()))// вот тут создаёт 5 окон вместо 1
						MessageBox(hWnd, "Error of creating of new process...", "Erorr", MB_OK);
				}
				if (counter == 3)
				{
					ZeroMemory(&sti, sizeof(STARTUPINFO));	// обнулить
					sti.cb = sizeof(STARTUPINFO);
					sti.dwX = -5;
					sti.dwY = 535;
					sti.dwXSize = 972;
					sti.dwYSize = 500;
					sti.dwFlags = STARTF_USESIZE | STARTF_USEPOSITION;
					SrackPi.push(pi);
					if (!CreateProcess("C:\\Users\\Admin\\source\\repos\\Spro10\\CRT_SECURE_NO_WARNINGS\\WindowsProject5.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sti, &SrackPi.top()))
						MessageBox(hWnd, "Error of creating of new process...", "Erorr", MB_OK);
				}
				if (counter == 4)
				{
					ZeroMemory(&sti, sizeof(STARTUPINFO));	// обнулить
					sti.cb = sizeof(STARTUPINFO);
					sti.dwX = -5;
					sti.dwY = 535;
					sti.dwXSize = 972;
					sti.dwYSize = 500;
					sti.dwFlags = STARTF_USESIZE | STARTF_USEPOSITION;
					SrackPi.push(pi);
					if (!CreateProcess("C:\\Users\\Admin\\source\\repos\\Spro10\\CRT_SECURE_NO_WARNINGS\\WindowsProject6.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sti, &SrackPi.top()))
						MessageBox(hWnd, "Error of creating of new process...", "Erorr", MB_OK);
				}
				if (counter == 5)
				{
					ZeroMemory(&sti, sizeof(STARTUPINFO));	// обнулить
					sti.cb = sizeof(STARTUPINFO);
					sti.dwX = -5;
					sti.dwY = 535;
					sti.dwXSize = 972;
					sti.dwYSize = 500;
					sti.dwFlags = STARTF_USESIZE | STARTF_USEPOSITION;
					SrackPi.push(pi);
					if (!CreateProcess("C:\\Users\\Admin\\source\\repos\\Spro10\\CRT_SECURE_NO_WARNINGS\\spro6.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sti, &SrackPi.top()))
						MessageBox(hWnd, "Error of creating of new process...", "Erorr", MB_OK);
				}
				if (counter == 6)
				{
					ZeroMemory(&sti, sizeof(STARTUPINFO));	// обнулить
					sti.cb = sizeof(STARTUPINFO);
					sti.dwX = -5;
					sti.dwY = 535;
					sti.dwXSize = 972;
					sti.dwYSize = 500;
					sti.dwFlags = STARTF_USESIZE | STARTF_USEPOSITION;
					SrackPi.push(pi);
					if (!CreateProcess("C:\\Users\\Admin\\source\\repos\\Spro10\\CRT_SECURE_NO_WARNINGS\\Spro7.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sti, &SrackPi.top()))
						MessageBox(hWnd, "Error of creating of new process...", "Erorr", MB_OK);
				}
				if (counter == 7)
				{
					ZeroMemory(&sti, sizeof(STARTUPINFO));	// обнулить
					sti.cb = sizeof(STARTUPINFO);
					sti.dwX = -5;
					sti.dwY = 535;
					sti.dwXSize = 972;
					sti.dwYSize = 500;
					sti.dwFlags = STARTF_USESIZE | STARTF_USEPOSITION;
					SrackPi.push(pi);
					if (!CreateProcess("C:\\Users\\Admin\\source\\repos\\Spro10\\CRT_SECURE_NO_WARNINGS\\Spro8 v2.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sti, &SrackPi.top()))
						MessageBox(hWnd, "Error of creating of new process...", "Erorr", MB_OK);
				}
				if (counter == 8)
				{
					ZeroMemory(&sti, sizeof(STARTUPINFO));	// обнулить
					sti.cb = sizeof(STARTUPINFO);
					sti.dwX = -5;
					sti.dwY = 535;
					sti.dwXSize = 972;
					sti.dwYSize = 500;
					sti.dwFlags = STARTF_USESIZE | STARTF_USEPOSITION;
					SrackPi.push(pi);
					if (!CreateProcess("C:\\Users\\Admin\\source\\repos\\Spro10\\CRT_SECURE_NO_WARNINGS\\Spro9 v2.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sti, &SrackPi.top()))
						MessageBox(hWnd, "Error of creating of new process...", "Erorr", MB_OK);
				}
			}
			break;
			case ID_CHOOSE3:// первый комбобокс(верхний левый)
			{
				if (CBN_SELCHANGE == HIWORD(wParam))
				{
					counter = SendMessage(hChoose[2], CB_GETCURSEL, 0, 0);
				}
				if (counter == 0)
				{
					ZeroMemory(&sti, sizeof(STARTUPINFO));	// обнулить
					sti.cb = sizeof(STARTUPINFO);
					sti.dwX = 955;
					sti.dwY = 66;
					sti.dwXSize = 972;
					sti.dwYSize = 450;
					sti.dwFlags = STARTF_USESIZE | STARTF_USEPOSITION;
					SrackPi.push(pi);
					if (!CreateProcess("C:\\Users\\Admin\\source\\repos\\Spro10\\CRT_SECURE_NO_WARNINGS\\Project3.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sti, &SrackPi.top()))// вот тут создаёт 5 окон вместо 1
						MessageBox(hWnd, "Error of creating of new process...", "Erorr", MB_OK);
				}
				if (counter == 1)
				{
					ZeroMemory(&sti, sizeof(STARTUPINFO));	// обнулить
					sti.cb = sizeof(STARTUPINFO);
					sti.dwX = 955;
					sti.dwY = 66;
					sti.dwXSize = 972;
					sti.dwYSize = 450;
					sti.dwFlags = STARTF_USESIZE | STARTF_USEPOSITION;
					SrackPi.push(pi);
					if (!CreateProcess("C:\\Users\\Admin\\source\\repos\\Spro10\\CRT_SECURE_NO_WARNINGS\\WindowsProject1.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sti, &SrackPi.top()))// вот тут создаёт 5 окон вместо 1
						MessageBox(hWnd, "Error of creating of new process...", "Erorr", MB_OK);
				}
				if (counter == 2)
				{
					ZeroMemory(&sti, sizeof(STARTUPINFO));	// обнулить
					sti.cb = sizeof(STARTUPINFO);
					sti.dwX = 955;
					sti.dwY = 66;
					sti.dwXSize = 972;
					sti.dwYSize = 450;
					sti.dwFlags = STARTF_USESIZE | STARTF_USEPOSITION;
					SrackPi.push(pi);
					if (!CreateProcess("C:\\Users\\Admin\\source\\repos\\Spro10\\CRT_SECURE_NO_WARNINGS\\WindowsProject2.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sti, &SrackPi.top()))// вот тут создаёт 5 окон вместо 1
						MessageBox(hWnd, "Error of creating of new process...", "Erorr", MB_OK);
				}
				if (counter == 3)
				{
					ZeroMemory(&sti, sizeof(STARTUPINFO));	// обнулить
					sti.cb = sizeof(STARTUPINFO);
					sti.dwX = 955;
					sti.dwY = 66;
					sti.dwXSize = 972;
					sti.dwYSize = 450;
					sti.dwFlags = STARTF_USESIZE | STARTF_USEPOSITION;
					SrackPi.push(pi);
					if (!CreateProcess("C:\\Users\\Admin\\source\\repos\\Spro10\\CRT_SECURE_NO_WARNINGS\\WindowsProject5.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sti, &SrackPi.top()))
						MessageBox(hWnd, "Error of creating of new process...", "Erorr", MB_OK);
				}
				if (counter == 4)
				{
					ZeroMemory(&sti, sizeof(STARTUPINFO));	// обнулить
					sti.cb = sizeof(STARTUPINFO);
					sti.dwX = 955;
					sti.dwY = 66;
					sti.dwXSize = 972;
					sti.dwYSize = 450;
					sti.dwFlags = STARTF_USESIZE | STARTF_USEPOSITION;
					SrackPi.push(pi);
					if (!CreateProcess("C:\\Users\\Admin\\source\\repos\\Spro10\\CRT_SECURE_NO_WARNINGS\\WindowsProject6.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sti, &SrackPi.top()))
						MessageBox(hWnd, "Error of creating of new process...", "Erorr", MB_OK);
				}
				if (counter == 5)
				{
					ZeroMemory(&sti, sizeof(STARTUPINFO));	// обнулить
					sti.cb = sizeof(STARTUPINFO);
					sti.dwX = 955;
					sti.dwY = 66;
					sti.dwXSize = 972;
					sti.dwYSize = 450;
					sti.dwFlags = STARTF_USESIZE | STARTF_USEPOSITION;
					SrackPi.push(pi);
					if (!CreateProcess("C:\\Users\\Admin\\source\\repos\\Spro10\\CRT_SECURE_NO_WARNINGS\\spro6.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sti, &SrackPi.top()))
						MessageBox(hWnd, "Error of creating of new process...", "Erorr", MB_OK);
				}
				if (counter == 6)
				{
					ZeroMemory(&sti, sizeof(STARTUPINFO));	// обнулить
					sti.cb = sizeof(STARTUPINFO);
					sti.dwX = 955;
					sti.dwY = 66;
					sti.dwXSize = 972;
					sti.dwYSize = 450;
					sti.dwFlags = STARTF_USESIZE | STARTF_USEPOSITION;
					SrackPi.push(pi);
					if (!CreateProcess("C:\\Users\\Admin\\source\\repos\\Spro10\\CRT_SECURE_NO_WARNINGS\\Spro7.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sti, &SrackPi.top()))
						MessageBox(hWnd, "Error of creating of new process...", "Erorr", MB_OK);
				}
				if (counter == 7)
				{
					ZeroMemory(&sti, sizeof(STARTUPINFO));	// обнулить
					sti.cb = sizeof(STARTUPINFO);
					sti.dwX = 955;
					sti.dwY = 66;
					sti.dwXSize = 972;
					sti.dwYSize = 450;
					sti.dwFlags = STARTF_USESIZE | STARTF_USEPOSITION;
					SrackPi.push(pi);
					if (!CreateProcess("C:\\Users\\Admin\\source\\repos\\Spro10\\CRT_SECURE_NO_WARNINGS\\Spro8 v2.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sti, &SrackPi.top()))
						MessageBox(hWnd, "Error of creating of new process...", "Erorr", MB_OK);
				}
				if (counter == 8)
				{
					ZeroMemory(&sti, sizeof(STARTUPINFO));	// обнулить
					sti.cb = sizeof(STARTUPINFO);
					sti.dwX = 955;
					sti.dwY = 66;
					sti.dwXSize = 972;
					sti.dwYSize = 450;
					sti.dwFlags = STARTF_USESIZE | STARTF_USEPOSITION;
					SrackPi.push(pi);
					if (!CreateProcess("C:\\Users\\Admin\\source\\repos\\Spro10\\CRT_SECURE_NO_WARNINGS\\Spro9 v2.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sti, &SrackPi.top()))
						MessageBox(hWnd, "Error of creating of new process...", "Erorr", MB_OK);
				}
			}
			break;
			case ID_CHOOSE4:// первый комбобокс(верхний левый)
			{
				if (CBN_SELCHANGE == HIWORD(wParam))
				{
					counter = SendMessage(hChoose[3], CB_GETCURSEL, 0, 0);
				}
				if (counter == 0)
				{
					ZeroMemory(&sti, sizeof(STARTUPINFO));	// обнулить
					sti.cb = sizeof(STARTUPINFO);
					sti.dwX = 955;
					sti.dwY = 535;
					sti.dwXSize = 972;
					sti.dwYSize = 500;
					sti.dwFlags = STARTF_USESIZE | STARTF_USEPOSITION;
					SrackPi.push(pi);
					if (!CreateProcess("C:\\Users\\Admin\\source\\repos\\Spro10\\CRT_SECURE_NO_WARNINGS\\Project3.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sti, &SrackPi.top()))// вот тут создаёт 5 окон вместо 1
						MessageBox(hWnd, "Error of creating of new process...", "Erorr", MB_OK);
				}
				if (counter == 1)
				{
					ZeroMemory(&sti, sizeof(STARTUPINFO));	// обнулить
					sti.cb = sizeof(STARTUPINFO);
					sti.dwX = 955;
					sti.dwY = 535;
					sti.dwXSize = 972;
					sti.dwYSize = 500;
					sti.dwFlags = STARTF_USESIZE | STARTF_USEPOSITION;
					SrackPi.push(pi);
					if (!CreateProcess("C:\\Users\\Admin\\source\\repos\\Spro10\\CRT_SECURE_NO_WARNINGS\\WindowsProject1.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sti, &SrackPi.top()))// вот тут создаёт 5 окон вместо 1
						MessageBox(hWnd, "Error of creating of new process...", "Erorr", MB_OK);
				}
				if (counter == 2)
				{
					ZeroMemory(&sti, sizeof(STARTUPINFO));	// обнулить
					sti.cb = sizeof(STARTUPINFO);
					sti.dwX = 955;
					sti.dwY = 535;
					sti.dwXSize = 972;
					sti.dwYSize = 500;
					sti.dwFlags = STARTF_USESIZE | STARTF_USEPOSITION;
					SrackPi.push(pi);
					if (!CreateProcess("C:\\Users\\Admin\\source\\repos\\Spro10\\CRT_SECURE_NO_WARNINGS\\WindowsProject2.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sti, &SrackPi.top()))// вот тут создаёт 5 окон вместо 1
						MessageBox(hWnd, "Error of creating of new process...", "Erorr", MB_OK);
				}
				if (counter == 3)
				{
					ZeroMemory(&sti, sizeof(STARTUPINFO));	// обнулить
					sti.cb = sizeof(STARTUPINFO);
					sti.dwX = 955;
					sti.dwY = 535;
					sti.dwXSize = 972;
					sti.dwYSize = 500;
					sti.dwFlags = STARTF_USESIZE | STARTF_USEPOSITION;
					SrackPi.push(pi);
					if (!CreateProcess("C:\\Users\\Admin\\source\\repos\\Spro10\\CRT_SECURE_NO_WARNINGS\\WindowsProject5.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sti, &SrackPi.top()))
						MessageBox(hWnd, "Error of creating of new process...", "Erorr", MB_OK);
				}
				if (counter == 4)
				{
					ZeroMemory(&sti, sizeof(STARTUPINFO));	// обнулить
					sti.cb = sizeof(STARTUPINFO);
					sti.dwX = 955;
					sti.dwY = 535;
					sti.dwXSize = 972;
					sti.dwYSize = 500;
					sti.dwFlags = STARTF_USESIZE | STARTF_USEPOSITION;
					SrackPi.push(pi);
					if (!CreateProcess("C:\\Users\\Admin\\source\\repos\\Spro10\\CRT_SECURE_NO_WARNINGS\\WindowsProject6.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sti, &SrackPi.top()))
						MessageBox(hWnd, "Error of creating of new process...", "Erorr", MB_OK);
				}
				if (counter == 5)
				{
					ZeroMemory(&sti, sizeof(STARTUPINFO));	// обнулить
					sti.cb = sizeof(STARTUPINFO);
					sti.dwX = 955;
					sti.dwY = 535;
					sti.dwXSize = 972;
					sti.dwYSize = 500;
					sti.dwFlags = STARTF_USESIZE | STARTF_USEPOSITION;
					SrackPi.push(pi);
					if (!CreateProcess("C:\\Users\\Admin\\source\\repos\\Spro10\\CRT_SECURE_NO_WARNINGS\\spro6.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sti, &SrackPi.top()))
						MessageBox(hWnd, "Error of creating of new process...", "Erorr", MB_OK);
				}
				if (counter == 6)
				{
					ZeroMemory(&sti, sizeof(STARTUPINFO));	// обнулить
					sti.cb = sizeof(STARTUPINFO);
					sti.dwX = 955;
					sti.dwY = 535;
					sti.dwXSize = 972;
					sti.dwYSize = 500;
					sti.dwFlags = STARTF_USESIZE | STARTF_USEPOSITION;
					SrackPi.push(pi);
					if (!CreateProcess("C:\\Users\\Admin\\source\\repos\\Spro10\\CRT_SECURE_NO_WARNINGS\\Spro7.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sti, &SrackPi.top()))
						MessageBox(hWnd, "Error of creating of new process...", "Erorr", MB_OK);
				}
				if (counter == 7)
				{
					ZeroMemory(&sti, sizeof(STARTUPINFO));	// обнулить
					sti.cb = sizeof(STARTUPINFO);
					sti.dwX = 955;
					sti.dwY = 535;
					sti.dwXSize = 972;
					sti.dwYSize = 500;
					sti.dwFlags = STARTF_USESIZE | STARTF_USEPOSITION;
					SrackPi.push(pi);
					if (!CreateProcess("C:\\Users\\Admin\\source\\repos\\Spro10\\CRT_SECURE_NO_WARNINGS\\Spro8 v2.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sti, &SrackPi.top()))
						MessageBox(hWnd, "Error of creating of new process...", "Erorr", MB_OK);
				}
				if (counter == 8)
				{
					ZeroMemory(&sti, sizeof(STARTUPINFO));	// обнулить
					sti.cb = sizeof(STARTUPINFO);
					sti.dwX = 955;
					sti.dwY = 535;
					sti.dwXSize = 972;
					sti.dwYSize = 500;
					sti.dwFlags = STARTF_USESIZE | STARTF_USEPOSITION;
					SrackPi.push(pi);
					if (!CreateProcess("C:\\Users\\Admin\\source\\repos\\Spro10\\CRT_SECURE_NO_WARNINGS\\Spro9 v2.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sti, &SrackPi.top()))
						MessageBox(hWnd, "Error of creating of new process...", "Erorr", MB_OK);
				}
			}
			break;
			case ID_INFO:
			{
				case ID_LAB1:
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Dialog);
					break;
				case ID_LAB2:
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG2), hWnd, Dialog);
					break;
				case ID_LAB3:
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG3), hWnd, Dialog);
					break;
				case ID_LAB4:
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG4), hWnd, Dialog);
					break;
				case ID_LAB5:
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG5), hWnd, Dialog);
					break;
				case ID_LAB6:
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG6), hWnd, Dialog);
					break;
				case ID_LAB7:
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG7), hWnd, Dialog);
					break;
				case ID_LAB8:
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG8), hWnd, Dialog);
					break;
				case ID_LAB9:
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG9), hWnd, Dialog);
					break;
			}
				break;
			case ID_AUTHORS:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_AUTHORS), hWnd, Dialog);
				break;
			case ID_TIMER:
				DestroyWindow(hClock);
				break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
	case WM_TIMER:
		InvalidateRect(hWnd, &clock, TRUE);
		break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
			hFont = CreateFontIndirect(&lf); //создаём объект HFONT на основе заполненной стрктуры
			SelectObject(hdc, hFont); //Он будет иметь силу только когда мы его выберем
			showClock(hWnd, hdc);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
		while(!SrackPi.empty())
		{
			TerminateProcess(SrackPi.top().hProcess, 0);
			SrackPi.pop();
		}
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

INT_PTR CALLBACK Dialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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

void showClock(HWND hClock,HDC hdc)
{
	char buffer[80];
	time_t seconds = time(NULL);
	tm* timeinfo = localtime(&seconds);
	char* format = "%H:%M:%S";
	strftime(buffer, 80, format, timeinfo);
	TextOut(hdc, 1750, 4, buffer, 9);
}
void showSecondMode(HDC hdc1)
{
	MoveToEx(hdc1, GetSystemMetrics(SM_CXSCREEN) / 2, 0, (LPPOINT)NULL);
	LineTo(hdc1, GetSystemMetrics(SM_CXSCREEN) / 2, GetSystemMetrics(SM_CYSCREEN));
	MoveToEx(hdc1, 0, GetSystemMetrics(SM_CYSCREEN) / 2 - 75, (LPPOINT)NULL);
	LineTo(hdc1, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) / 2 - 75);
}

void createListBoxes(HWND hwnd[4],HWND parent)
{
	hwnd[0] = CreateWindow(_T("combobox"), _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER|CBS_DROPDOWNLIST, 1, 1, 192, 200, parent, (HMENU)ID_CHOOSE1, hInst, 0);
	hwnd[1] = CreateWindow(_T("combobox"), _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST, 0, GetSystemMetrics(SM_CYSCREEN)/2-74, 192, 200, parent, (HMENU)ID_CHOOSE2, hInst, 0);
	hwnd[2] = CreateWindow(_T("combobox"), _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST, GetSystemMetrics(SM_CXSCREEN) / 2+1, 0, 192, 200, parent, (HMENU)ID_CHOOSE3, hInst, 0);
	hwnd[3] = CreateWindow(_T("combobox"), _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST, GetSystemMetrics(SM_CXSCREEN)/2+1, GetSystemMetrics(SM_CYSCREEN) / 2-74, 192, 200, parent, (HMENU)ID_CHOOSE4, hInst, 0);
	for (int i = 0; i < 4; i++)
	{
		SendMessage(hwnd[i], CB_ADDSTRING, 0, (LPARAM)(LPSTR)"Лабораторная работа №1");
		SendMessage(hwnd[i], CB_ADDSTRING, 0, (LPARAM)(LPSTR)"Лабораторная работа №2");
		SendMessage(hwnd[i], CB_ADDSTRING, 0, (LPARAM)(LPSTR)"Лабораторная работа №3");
		SendMessage(hwnd[i], CB_ADDSTRING, 0, (LPARAM)(LPSTR)"Лабораторная работа №4");
		SendMessage(hwnd[i], CB_ADDSTRING, 0, (LPARAM)(LPSTR)"Лабораторная работа №5");
		SendMessage(hwnd[i], CB_ADDSTRING, 0, (LPARAM)(LPSTR)"Лабораторная работа №6");
		SendMessage(hwnd[i], CB_ADDSTRING, 0, (LPARAM)(LPSTR)"Лабораторная работа №7");
		SendMessage(hwnd[i], CB_ADDSTRING, 0, (LPARAM)(LPSTR)"Лабораторная работа №8");
		SendMessage(hwnd[i], CB_ADDSTRING, 0, (LPARAM)(LPSTR)"Лабораторная работа №9");
	}
}

void RefreshWindow(HWND hwnd[4], HWND parent)
{
	for (int i = 0; i < 4; i++)
	{
		DestroyWindow(hwnd[i]);
	}
	InvalidateRect(parent, 0, TRUE);
	UpdateWindow(parent);
}