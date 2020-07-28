#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <Shlwapi.h>
#include"Logic.h"
#include "resource.h"
#include"Calculators(UI).h"
#include"Logic(Binary).h"
#include"Buttons.h"

static TCHAR szWindowClass[] = _T("win32app");
static TCHAR szTitle[] = _T("Калькулятор");
TCHAR buf[256];
TCHAR buf1[256];
TCHAR buf2[256];
TCHAR buf3[256];

HINSTANCE hInst;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Главная часть программы-------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
    // Структура класса окна---------------------------------------------------------------------------------------
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 11);
    wcex.lpszMenuName = MAKEINTRESOURCE(IDC_KURSAACH);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);
   
    // Регистрируем класс окна------------------------------------------------------------------------------------
    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("Win32 Guided Tour"),
            0);
        return 1;
    }

    hInst = hInstance;
    HWND hWnd = CreateWindow(szWindowClass,szTitle,WS_SYSMENU,CW_USEDEFAULT, CW_USEDEFAULT,415, 410,NULL,NULL,hInstance,NULL);

    if (!hWnd)
    {
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("Win32 Guided Tour"),
            0);
        return 1;
    }

    // Отображаем окно---------------------------------------------------------------------------------------------
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // Цикл обработки сообщений для прослушивания отправляемых ОС сообщений----------------------------------------
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

// Функция------------------------------------------------------------------------------------------------------------

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // Структура класса кнопки-------------------------------------------------------------------------------------
    static HWND hButton[38], hEdit[126],hBinary[187];
    PAINTSTRUCT ps;
    HDC hdc;
    HBITMAP hBitmap = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(IDB_BITMAP1),IMAGE_BITMAP, 0, 0, 0);
    switch (message)
    {
    case WM_CREATE:
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
        break;
    case WM_COMMAND:
    {
        if ((LOWORD(wParam) == ID_BUTTON) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit[0], buf, sizeof(buf));
            if (*buf == TEXT('0') && 0 == buf[1]) *buf = 0;
            StrCat(buf, TEXT("0"));
            SetWindowText(hEdit[0], buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_1) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit[0], buf, sizeof(buf));
            if (*buf == TEXT('0') && 0 == buf[1]) *buf = 0;
            StrCat(buf, TEXT("1"));
            SetWindowText(hEdit[0], buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_2) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit[0], buf, sizeof(buf));
            if (*buf == '0' && 0 == buf[1]) *buf = 0;
            StrCat(buf, TEXT("2"));
            SetWindowText(hEdit[0], buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_3) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit[0], buf, sizeof(buf));
            if (*buf == '0' && 0 == buf[1]) *buf = 0;
            StrCat(buf, TEXT("3"));
            SetWindowText(hEdit[0], buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_4) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit[0], buf, sizeof(buf));
            if (*buf == '0' && 0 == buf[1]) *buf = 0;
            StrCat(buf, TEXT("4"));
            SetWindowText(hEdit[0], buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_5) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit[0], buf, sizeof(buf));
            if (*buf == '0' && 0 == buf[1]) *buf = 0;
            StrCat(buf, TEXT("5"));
            SetWindowText(hEdit[0], buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_6) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit[0], buf, sizeof(buf));
            if (*buf == '0' && 0 == buf[1]) *buf = 0;
            StrCat(buf, TEXT("6"));
            SetWindowText(hEdit[0], buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_7) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit[0], buf, sizeof(buf));
            if (*buf == '0' && 0 == buf[1]) *buf = 0;
            StrCat(buf, TEXT("7"));
            SetWindowText(hEdit[0], buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_8) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit[0], buf, sizeof(buf));
            if (*buf == '0' && 0 == buf[1]) *buf = 0;
            StrCat(buf, TEXT("8"));
            SetWindowText(hEdit[0], buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_9) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit[0], buf, sizeof(buf));
            if (*buf == '0' && 0 == buf[1]) *buf = 0;
            StrCat(buf, TEXT("9"));
            SetWindowText(hEdit[0], buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_ADD) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit[0], buf, sizeof(buf));
            StrCat(buf, TEXT("+"));
            SetWindowText(hEdit[0], buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_SUB) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit[0], buf, sizeof(buf));
            StrCat(buf, TEXT("-"));
            SetWindowText(hEdit[0], buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_MUL) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit[0], buf, sizeof(buf));
            StrCat(buf, TEXT("*"));
            SetWindowText(hEdit[0], buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_DIV) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit[0], buf, sizeof(buf));
            StrCat(buf, TEXT("/"));
            SetWindowText(hEdit[0], buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_RES) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit[0], buf, sizeof(buf));
            SetWindowText(hEdit[0], Calculate(buf));
        }

        if ((LOWORD(wParam) == ID_BUTTON_C) && (HIWORD(wParam) == BN_CLICKED))
        {
            SetWindowText(hEdit[0], TEXT(""));
            SetWindowText(hEdit[1], TEXT(""));
            SetWindowText(hEdit[2], TEXT(""));
            SetWindowText(hEdit[3], TEXT(""));
            buf[0] = 0;
            buf1[0] = 0;
            buf2[0] = 0;
            buf3[0] = 0;
        }

        if ((LOWORD(wParam) == ID_BUTTON_POINT) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit[0], buf, sizeof(buf));
            if (*buf == '0' && 0 == buf[1]) *buf = 0;
            StrCat(buf, TEXT("."));
            SetWindowText(hEdit[0], buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_OPEN) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit[0], buf, sizeof(buf));
            if (*buf == '0' && 0 == buf[1]) *buf = 0;
            StrCat(buf, TEXT("("));
            SetWindowText(hEdit[0], buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_CLOSE) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit[0], buf, sizeof(buf));
            if (*buf == '0' && 0 == buf[1]) *buf = 0;
            StrCat(buf, TEXT(")"));
            SetWindowText(hEdit[0], buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_COS) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit[0], buf, sizeof(buf));
            if (*buf == '0' && 0 == buf[1]) *buf = 0;
            StrCat(buf, TEXT("cos("));
            SetWindowText(hEdit[0], buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_SIN) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit[0], buf, sizeof(buf));
            if (*buf == '0' && 0 == buf[1]) *buf = 0;
            StrCat(buf, TEXT("sin("));
            SetWindowText(hEdit[0], buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_TAN) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit[0], buf, sizeof(buf));
            if (*buf == '0' && 0 == buf[1]) *buf = 0;
            StrCat(buf, TEXT("tan("));
            SetWindowText(hEdit[0], buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_CTG) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit[0], buf, sizeof(buf));
            if (*buf == '0' && 0 == buf[1]) *buf = 0;
            StrCat(buf, TEXT("ctg("));
            SetWindowText(hEdit[0], buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_E) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit[0], buf, sizeof(buf));
            if (*buf == '0' && 0 == buf[1]) *buf = 0;
            StrCat(buf, TEXT("e"));
            SetWindowText(hEdit[0], buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_LOG) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit[0], buf, sizeof(buf));
            if (*buf == '0' && 0 == buf[1]) *buf = 0;
            StrCat(buf, TEXT("lg("));
            SetWindowText(hEdit[0], buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_LN) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit[0], buf, sizeof(buf));
            if (*buf == '0' && 0 == buf[1]) *buf = 0;
            StrCat(buf, TEXT("ln("));
            SetWindowText(hEdit[0], buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_PI) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit[0], buf, sizeof(buf));
            if (*buf == '0' && 0 == buf[1]) *buf = 0;
            StrCat(buf, TEXT("pi"));
            SetWindowText(hEdit[0], buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_SQRT) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit[0], buf, sizeof(buf));
            if (*buf == '0' && 0 == buf[1]) *buf = 0;
            StrCat(buf, TEXT("sqrt("));
            SetWindowText(hEdit[0], buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_POWER) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit[0], buf, sizeof(buf));
            if (*buf == '0' && 0 == buf[1]) *buf = 0;
            StrCat(buf, TEXT("^"));
            SetWindowText(hEdit[0], buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_SWAP) && (HIWORD(wParam) == BN_CLICKED))
        {
            DestroyWindow(hEdit[0]);
                for (int i = 0; i < 30; i++)
                {
                    DestroyWindow(hButton[i]);
                }
                SimpleCalcuter(hWnd, hButton, hInst, hBitmap,hEdit);
                SetWindowText(hEdit[0], TEXT("0"));
                buf[0] = 0;
        }

        if ((LOWORD(wParam) == ID_BUTTON_SWAP1) && (HIWORD(wParam) == BN_CLICKED))
        {
            DestroyWindow(hEdit[0]);
                for (int i = 0; i < 30; i++)
                {
                 DestroyWindow(hButton[i]);
                }
            EngeeringCalcuter(hWnd, hButton, hInst, hBitmap,hEdit);
            SetWindowText(hEdit[0], TEXT("0"));
            buf[0] = 0;
        }

        if ((LOWORD(wParam) == ID_BUTTON_AND) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit[1], buf1, sizeof(buf1));
            GetWindowText(hEdit[2], buf2, sizeof(buf2));
            SetWindowText(hEdit[3], Calc(buf1, buf2, buf3,wParam));
        }

        if ((LOWORD(wParam) == ID_BUTTON_OR) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit[1], buf1, sizeof(buf1));
            GetWindowText(hEdit[2], buf2, sizeof(buf2));
            SetWindowText(hEdit[3], Calc(buf1, buf2, buf3, wParam));
        }

        if ((LOWORD(wParam) == ID_BUTTON_NAND) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit[1], buf1, sizeof(buf1));
            GetWindowText(hEdit[2], buf2, sizeof(buf2));
            SetWindowText(hEdit[3], Calc(buf1, buf2, buf3, wParam));
        }

        if ((LOWORD(wParam) == ID_BUTTON_NOR) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit[1], buf1, sizeof(buf1));
            GetWindowText(hEdit[2], buf2, sizeof(buf2));
            SetWindowText(hEdit[3], Calc(buf1, buf2, buf3, wParam));
        }

        if ((LOWORD(wParam) == ID_BUTTON_XOR) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit[1], buf1, sizeof(buf1));
            GetWindowText(hEdit[2], buf2, sizeof(buf2));
            SetWindowText(hEdit[3], Calc(buf1, buf2, buf3, wParam));
        }

        switch (LOWORD(wParam))
        {
        case ID_BINARY:
            for (int i = 0; i < 30; i++)
            {
                DestroyWindow(hEdit[i]);
                DestroyWindow(hButton[i]);
                DestroyWindow(hBinary[i]);
            }
            BinaryCalculator(hWnd, hButton, hInst, hEdit,hBinary);
            break;
        case ID_DECIMAL:
            for (int i = 0; i < 30; i++)
            {
                DestroyWindow(hButton[i]);
                DestroyWindow(hBinary[i]);
                DestroyWindow(hEdit[i]);
            }
            EngeeringCalcuter(hWnd, hButton, hInst, hBitmap, hEdit);
            SetWindowText(hEdit[0], TEXT("0"));
            buf[0] = 0;
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }
    return 0;
}