#include <windows.h>// ���������� �������� � ��������� API
#include "resource.h"
// �������� ����: 
HINSTANCE hInst; 	//���������� ��������	
LPCTSTR szWindowClass = "Tykhomyrov Valentyn KIUKI 18-2";
LPCTSTR szTitle = "����� ��������";

// ��������� ���� �������

ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// ������� �������� 
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,
	int nCmdShow)
{
	MSG msg;

	// ��������� ����� ���� 
	MyRegisterClass(hInstance);

	// ��������� ���� ��������
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}
	// ���� ������� ����������
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
	case WM_INITDIALOG:  //����������� ����������� ��������� ��������� �����
		return TRUE;

		//���� ������� ���������� �������� �� ���� ���������� ����
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			EndDialog(hDlg, LOWORD(wParam));//�������� ���������� ���������� ����
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
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS; 		//����� ����
	wcex.lpfnWndProc = (WNDPROC)WndProc; 		//������ ���������
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance; 			//���������� ��������
	wcex.hIcon = LoadIcon(NULL, IDI_QUESTION); 		//���������� ������
	wcex.hCursor = LoadCursor(NULL, IDC_CROSS); 	//���������� �������
	wcex.hbrBackground = GetSysColorBrush(COLOR_WINDOW); //��������� ����
	wcex.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1); 				//���������� ����
	wcex.lpszClassName = szWindowClass; 		//��� �����
	wcex.hIconSm = NULL;

	return RegisterClassEx(&wcex); 			//��������� ����� ����
}

// FUNCTION: InitInstance (HANDLE, int)
// ������� ���� �������� � ������ ���������� �������� � ����� hInst

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hInst = hInstance; //������ ���������� ������� � ����� hInst
	hWnd = CreateWindow(szWindowClass, 	// ��� ����� ����
		szTitle, 				// ����� ��������
		WS_MINIMIZEBOX | WS_BORDER | WS_SYSMENU,			// ����� ����
		570, 			// ��������� �� �	
		300,			// ��������� �� Y	
		200, 			// ����� �� �
		150, 			// ����� �� Y
		NULL, 					// ���������� ������������ ����	
		NULL, 					// ���������� ���� ����
		hInstance, 				// ���������� ��������
		NULL); 				// ��������� ���������.

	if (!hWnd) 	//���� ���� �� ���������, ������� ������� FALSE
	{
		return FALSE;
	}
	ShowWindow(hWnd, SW_MINIMIZE); 		//�������� ����
	UpdateWindow(hWnd); 				//������� ����
	return TRUE;
}



// FUNCTION: WndProc (HWND, unsigned, WORD, LONG)
// ³����� ���������. ������ � �������� �� �����������, �� ��������� � �������


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
	case WM_PAINT: //������������ ����
		int nHeight;
		hdc = BeginPaint(hWnd, &ps); 	//������ ��������� ����	
		GetClientRect(hWnd, &rt); 		//������� ���� ��� ���������
		EndPaint(hWnd, &ps); 		//�������� ��������� ����
		break;
	case WM_CLOSE:
		if (wParam == SC_CLOSE)
		{
			if ((::GetAsyncKeyState(VK_MENU)) && (::GetAsyncKeyState(VK_F4)))
				return NULL;
		}
		break;
	case WM_DESTROY: 				//���������� ������
		PostQuitMessage(0);
		break;
	default:
		//������� ����������, �� �� �������� ������������
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}



