#include <iostream>
#include<cstring>
#include<windows.h>
#include"Buttons.h"
#include<cmath>
using namespace std;
void ORfunction(TCHAR* str, TCHAR* str1, TCHAR* buffer)
{
    for (int i = 0; i < 32; i++)
    {
        if (str1[i] == '1' && str[i] == '1')
        {
            strcat(buffer, "1");
        }
        else if (str1[i] == '1' && str[i] == '0')
        {
            strcat(buffer, "1");
        }
        else if (str1[i] == '0' && str[i] == '1')
        {
            strcat(buffer, "1");
        }
        else if (str1[i] == '0' && str[i] == '0')
        {
            strcat(buffer, "0");
        }
    }
}

void ANDfunction(TCHAR* str, TCHAR* str1, TCHAR* buffer)
{
    for (int i = 0; i < 32; i++)
    {
        if (str1[i] == '1' && str[i] == '1')
        {
            strcat(buffer, "1");
        }
        else if (str1[i] == '1' && str[i] == '0')
        {
            strcat(buffer, "0");
        }
        else if (str1[i] == '0' && str[i] == '1')
        {
            strcat(buffer, "0");
        }
        else if (str1[i] == '0' && str[i] == '0')
        {
            strcat(buffer, "0");
        }
    }
}

void NORfunction(TCHAR* str, TCHAR* str1, TCHAR* buffer)
{
    for (int i = 0; i < 32; i++)
    {
        if (str1[i] == '1' && str[i] == '1')
        {
            strcat(buffer, "0");
        }
        else if (str1[i] == '1' && str[i] == '0')
        {
            strcat(buffer, "0");
        }
        else if (str1[i] == '0' && str[i] == '1')
        {
            strcat(buffer, "0");
        }
        else if (str1[i] == '0' && str[i] == '0')
        {
            strcat(buffer, "1");
        }
    }
}

void NANDfunction(TCHAR* str, TCHAR* str1, TCHAR* buffer)
{
    for (int i = 0; i < 32; i++)
    {
        if (str1[i] == '1' && str[i] == '1')
        {
            strcat(buffer, "0");
        }
        else if (str1[i] == '1' && str[i] == '0')
        {
            strcat(buffer, "1");
        }
        else if (str1[i] == '0' && str[i] == '1')
        {
            strcat(buffer, "1");
        }
        else if (str1[i] == '0' && str[i] == '0')
        {
            strcat(buffer, "1");
        }
    }
}

void XORfunction(TCHAR* str,TCHAR* str1, TCHAR* buffer)
{
    for (int i = 0; i < 32; i++)
    {
        if (str1[i] == '1' && str[i] == '1')
        {
            strcat(buffer, "0");
        }
        else if (str1[i] == '1' && str[i] == '0')
        {
            strcat(buffer, "1");
        }
        else if (str1[i] == '0' && str[i] == '1')
        {
            strcat(buffer, "1");
        }
        else if (str1[i] == '0' && str[i] == '0')
        {
            strcat(buffer, "0");
        }
    }
}

TCHAR* Calc(TCHAR* str1,TCHAR* str,TCHAR* buffer,WPARAM wParam)
{
    int a = strlen(str) - strlen(str1);
    if (a < 0)
    {
        a = a * (-1);
    }
    if (strlen(str) > strlen(str1))
    {
        strcpy(buffer, str1);
        str1[0] = '\0';
        for (int i = 0; i < a; i++)
        {
            str1[i] = '0';
        }
        strcat(str1, buffer);
		buffer[0] = '\0';
		switch (LOWORD(wParam))
		{
		case ID_BUTTON_AND:
			ANDfunction(str, str1, buffer);
			break;
		case ID_BUTTON_OR:
			ORfunction(str, str1, buffer);
			break;
		case ID_BUTTON_NOR:
			NORfunction(str, str1, buffer);
			break;
		case ID_BUTTON_XOR:
			XORfunction(str, str1, buffer);
			break;
		case ID_BUTTON_NAND:
			NANDfunction(str, str1, buffer);
			break;
		}
    }
    else if (strlen(str) < strlen(str1))
    {
        strcpy(buffer, str);
        str[0] = '\0';
        for (int i = 0; i < a; i++)
        {
            str[i] = '0';
        }
        strcat(str, buffer);
		buffer[0] = '\0';
		switch (LOWORD(wParam))
		{
		case ID_BUTTON_AND:
			ANDfunction(str, str1, buffer);
			break;
		case ID_BUTTON_OR:
			ORfunction(str, str1, buffer);
			break;
		case ID_BUTTON_NOR:
			NORfunction(str, str1, buffer);
			break;
		case ID_BUTTON_XOR:
			XORfunction(str, str1, buffer);
			break;
		case ID_BUTTON_NAND:
			NANDfunction(str, str1, buffer);
			break;
		}
    }
    else if (strlen(str) == strlen(str1))
    {
        buffer[0] = '\0';
        switch (LOWORD(wParam))
        {
        case ID_BUTTON_AND:
            ANDfunction(str, str1, buffer);
            break;
        case ID_BUTTON_OR:
            ORfunction(str, str1, buffer);
            break;
        case ID_BUTTON_NOR:
            NORfunction(str, str1, buffer);
            break;
        case ID_BUTTON_XOR:
            XORfunction(str, str1, buffer);
            break;
        case ID_BUTTON_NAND:
            NANDfunction(str, str1, buffer);
            break;
        }
    }
    return buffer;
}
