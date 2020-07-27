#include "main.h"
static const int WINDOW_SIZEH = 600;
static const int WINDOW_SIZEV = 450;

static HINSTANCE hInst;
static LPCTSTR szWindowClass = "lab";
static LPCTSTR szTitle = "lab";
static OPENFILENAME ofn;

static char new_file_name[BUFF_SIZE] = "";
static char fileName[BUFF_SIZE] = "";

ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,
	int nCmdShow)
{
	MSG msg;
	MyRegisterClass(hInstance);
	if (!InitInstance(hInstance, nCmdShow)) { return FALSE; }
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
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = (WNDPROC)WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = NULL;

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hInst = hInstance;
	hWnd = CreateWindow(
		szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
	if (!hWnd) { return FALSE; }
	initOpen(hWnd);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}

BOOL initOpen(HWND hWnd)
{
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = (LPSTR)fileName; 
	ofn.nMaxFile = sizeof(fileName);
	ofn.lpstrFilter = (LPCSTR)"Text file(.txt)\0 * .txt\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rt;
	static HWND hEdit;

	switch (message)
	{
	case WM_CREATE:
		hEdit = CreateEdit(hWnd);
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rt);
		EndPaint(hWnd, &ps);
		break;

	case WM_COMMAND:
		switch (wParam)
		{
		case ID_CREATEFILE:
			CreateNewFile(hWnd);
			break;

		case ID_OPENFILE:
			OpenSelectFile(hEdit);
			break;

		case ID_SAVEFILE:
			SaveFile(hEdit);
			break;

		case ID_COPYFILE:
			CopyLastFile(hWnd);
			break;
		}
		break;
/*
	case WM_KEYDOWN:
		if (wParam == VK_RETURN)
			CreateNewFile(hWnd);
		else if (wParam == VK_TAB)
			OpenSelectFile(hEdit);
		else if (wParam == VK_SHIFT)
			SaveFile(hEdit);
		else if (wParam == VK_CONTROL)
			CopyLastFile(hWnd);
		break;
*/
	case WM_SIZE:
		MoveWindow(hEdit, 0, 0, LOWORD(lParam), HIWORD(lParam), TRUE);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

HWND CreateEdit(HWND hWnd)
{
	return CreateWindow("Edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | ES_MULTILINE,
		0, 0, WINDOW_SIZEH, WINDOW_SIZEV, hWnd, (HMENU)"ID_EDIT", hInst, NULL);
}

void CreateNewFile(HWND hWnd)
{
	DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, (DLGPROC)CreateNewFileProc);
	CreateFile((LPCSTR)new_file_name, NULL, NULL, NULL, CREATE_ALWAYS, NULL, NULL);
}

void OpenSelectFile(HWND hEdit)
{
	HANDLE hf = (HANDLE)NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (GetOpenFileName(&ofn))
	{
		hf = CreateFile(ofn.lpstrFile, GENERIC_READ, 0, (LPSECURITY_ATTRIBUTES)NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, (HANDLE)NULL);
		if (hf == INVALID_HANDLE_VALUE)
			return;

		FillEdit(hEdit, hf);

		CloseHandle(hf);
	}
}

void FillEdit(HWND hEdit, HANDLE hf)
{
	int len = GetFileSize(hf, NULL);
	char *buffer = new char[len + 1];
	ReadFile(hf, buffer, len, NULL, NULL);
	buffer[len] = '\0';
	MessageBox(hEdit, "Work", "ERROR", NULL);
	SendMessage(hEdit, WM_SETTEXT, WPARAM(0), LPARAM(""));
	SendMessage(hEdit, WM_SETTEXT, WPARAM(0), (LPARAM) buffer);
	delete[] buffer;
}

void SaveFile(HWND hEdit)
{
	HANDLE hf = (HANDLE)NULL;
	ofn.Flags = OFN_PATHMUSTEXIST;
	if (GetSaveFileName(&ofn)) 
	{ 
		hf = CreateFile(fileName, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		GetEditText(hEdit, hf);

		CloseHandle(hf);
	}
}

void GetEditText(HWND hEdit, HANDLE hf)
{
	int len = GetWindowTextLength(hEdit);
	char *buffer = new char[len + 1];
	SendMessage(hEdit, WM_GETTEXT, (WPARAM)len, (LPARAM)buffer);
	buffer[len] = '\0';
	WriteFile(hf, buffer, len, NULL, NULL);
	delete[] buffer;
}

void CopyLastFile(HWND hEdit)
{
	UINT copy_count = 1;
	static char new_file_name[BUFF_SIZE] = "";
	static char buffer[BUFF_SIZE] = "";

	if (!strlen(fileName))
		return;

	strncpy_s(buffer, fileName, BUFF_SIZE);
	for (int i = strlen(buffer) - 1; i; --i)
	{
		if (buffer[i] == '.')
		{
			buffer[i] = '\0';
			break;
		}
	}

	do {
		wsprintf(new_file_name, "%s(%u).txt", buffer, copy_count++);
	} while (!CopyFile(fileName, new_file_name, TRUE));
}

BOOL CALLBACK CreateNewFileProc(HWND hDlg, UINT msg, WPARAM wParm, LPARAM lParam)
{
	static HWND hEdit;
	switch (msg)
	{
	case WM_COMMAND:
		switch (LOWORD(wParm))
		{
		case IDOK:
			hEdit = GetDlgItem(hDlg, IDC_EDIT1);
			SendMessage(hEdit, WM_GETTEXT, (WPARAM)BUFF_SIZE, (LPARAM)new_file_name);

		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParm));
			return TRUE;
		}
	}
	return FALSE;
}
