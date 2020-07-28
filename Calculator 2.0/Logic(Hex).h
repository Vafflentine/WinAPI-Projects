#pragma once
#include<iostream>
#include<cstring>
#include<Windows.h>
#include"Buttons.h"
using namespace std;
//convert hexadecimal to decimal
int convert(char num[])
{
    int len = strlen(num);
    int base = 1;
    int temp = 0;
    for (int i = len - 1; i >= 0; i--)
    {
        if (num[i] >= '0' && num[i] <= '9')
        {
            temp += (num[i] - 48) * base;
            base = base * 16;
        }
        else if (num[i] >= 'A' && num[i] <= 'F')
        {
            temp += (num[i] - 55) * base;
            base = base * 16;
        }
    }
    return temp;
}


string DecToHex(int dec_num)
{
    int r;
    string hexdec_num = "";
    char hex[] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
    while (dec_num > 0)
    {
        r = dec_num % 16;
        hexdec_num = hex[r] + hexdec_num;
        dec_num = dec_num / 16;
    }
    return hexdec_num;
}
TCHAR* Calc1(TCHAR* str1, TCHAR* str, TCHAR* buffer, WPARAM wParam)
{
    int c;
    switch (LOWORD(wParam))
    {
    case ID_BUTTON_AND:
        c = convert(str) & convert(str1);
        for (int i = 0; i < DecToHex(c).length(); i++)
        {
            buffer[i] = DecToHex(c)[i];
        }
        break;
    case ID_BUTTON_OR:
        c = convert(str) | convert(str1);
        for (int i = 0; i < DecToHex(c).length(); i++)
        {
            buffer[i] = DecToHex(c)[i];
        }
        break;
    case ID_BUTTON_NOR:
        c = convert(str) | convert(str1);
        c = !c;
        for (int i = 0; i < DecToHex(c).length(); i++)
        {
            buffer[i] = DecToHex(c)[i];
        }
        break;
    case ID_BUTTON_XOR:
        c = convert(str) ^ convert(str1);
        for (int i = 0; i < DecToHex(c).length(); i++)
        {
            buffer[i] = DecToHex(c)[i];
        }
        break;
    case ID_BUTTON_NAND:
        
        break;
    }
    return 0;
}
