#ifndef MAIN_H
#define MAIN_H
#include <windows.h>
#include <cstring>
#include "resource.h"
#define BUFF_SIZE 128
BOOL initOpen(HWND hWnd);
HWND CreateEdit(HWND hWnd);
void CreateNewFile(HWND hWnd);
void OpenSelectFile(HWND hEdit);
void FillEdit(HWND hEdit, HANDLE hf);
void SaveFile(HWND hEdit);
void GetEditText(HWND hEdit, HANDLE hf);
void CopyLastFile(HWND hEdit);
BOOL CALLBACK CreateNewFileProc(HWND hDlg, UINT msg, WPARAM wParm, LPARAM lParam);
#endif 