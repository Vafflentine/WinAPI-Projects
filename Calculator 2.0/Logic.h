#include <iostream>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <cmath>
#include<cctype>
#include "Windows.h"
using namespace std;

void eatspaces(char* str); //������� ��� �������� ��������
double expr(char* str); //�������, ����������� ���������
double term(char* str, int& index); //������� ��� ������� ��������
double trigon(char* str, int& index); //������� ��� ���������� ������������������ ��������
double power(char* str, int& index); //������� ��� ���������� �������
double number(char* str, int& index); //�������, ������������ �����
char* extract(char* str, int& index); //������� ��� ���������� ���������
const int MAX = 100; //������������ ������ ������

TCHAR* Calculate(TCHAR* buf)
{
	TCHAR p[17]= "Divison by zero";
	TCHAR q[13] = "Wrong input";
	eatspaces(buf); //������� ��� ������� �� ������
	int count = 0, count1 = 0;
	for (int i = 0; i < strlen(buf); i++)
	{
		if (buf[i] == ')')
		{
			count++;
		}
		else if (buf[i] == '(')
		{
			count1++;
		}
		else if (buf[i] == '/' && buf[i + 1] == '0' && isdigit(buf[i - 1]) && buf[i + 2]!='.')
		{
			return p;
		}
	}
	if (count != count1)
	{
		return q;
	}
	else
	{
		sprintf(buf, "%f", expr(buf));
		return buf;
	}
}

void eatspaces(char* str)
{
	int i = 0;                          //������ ����� � ������ "���� ����������"
	int j = 0;                          //������ ����� � ������ "������ ����������"
	while ((*(str + i) = *(str + j++)) != '\0') //����, ���� ��������� ������ �� '\0'
		if (*(str + i) != ' ')  //����������� i, ���� ������ �� ������
			i++;
	return;
}

bool is_used = false;

double expr(char* str)
{
	double value = 0.0;         //����� ��������� ���������
	int index = 0;              //������� ������� �������
	value = term(str, index);   //�������� ������ �������
	for (; ;)                 //����������� ����, ����� ������
	{
		switch (*(str + index++)) //������� �������� �� ������ �������� �������
		{
		case '\0':          //����� ������, ���������� ��������
			is_used = false;
			return value;
		case '+':           //���� ����, ���������� ������� � value
			value += term(str, index);
			is_used = false;
			break;
		case '-':           //���� �����, �������� ������� �� value
			value -= term(str, index);
			is_used = false;
			break;
		default:            //��� ��������� �� ����������
			if (is_used == true)
				break;
			is_used = true;
			break;
		}
	}
}


double term(char* str, int& index)
{
	double value = 0.0;             //����� ������������� �������� ����������
	value = power(str, index);      //�������� ������ ����� ��������
	//��������� ���� �� ��� ���, ���� ����� ���������� ��������
	while ((*(str + index) == '*') || (*(str + index) == '/'))
	{
		if (*(str + index) == '*')
			value *= power(str, ++index);
		if (*(str + index) == '/')
			value /= power(str, ++index);			
	}
	return value;
}


double power(char* str, int& index)
{
	double value = 0.0;
	value = trigon(str, index);
	while (*(str + index) == '^')
	{
		value = pow(value, trigon(str, ++index)); //�������� � �������
	}
	return value;
}

double trigon(char* str, int& index)
{
	int buf_index = 0;
	int temp_index = index; //���������� ��� �������� ������� (����� ���� ��� ������� ������ ��� ���������)
	char* p_str = 0;    //��������� ��������� ��� ��������� ��������
	double value = 0;
	int a = 1;
	while (isalpha(*(str + temp_index)))
	{
		buf_index++;    //������� ����
		temp_index++;   //������� ������
	}
	if (!buf_index)     //���� ��� �� ����� �����, �� ���������� �����
	{
		value = number(str, index);
		return value;
	}
	else                //����� �������, �������� �� ����� ���-������ ����
	{
		p_str = new char[buf_index + 1];  //� ��� ����� ������� ��������� ������, ����� ��������
		p_str[buf_index] = '\0';
		strncpy(p_str, str + index, buf_index);
	}
	if (strcmp(p_str, "sin") == 0)      //����� � ��������
	{
		value = sin(3.141592 / 180 * number(str, temp_index));
		index = temp_index;
		delete[] p_str;     //�� �������� ������� ��������� ������
		return value;
	}
	
	else if (strcmp(p_str, "cos") == 0) //������� � ��������
	{
		value = cos(3.141592 / 180 * number(str, temp_index));
		index = temp_index;
		delete[] p_str;     //�� �������� ������� ��������� ������
		return value;
	}
	else if (strcmp(p_str, "tan") == 0) //������� � ��������
	{
		value = tan(3.141592 / 180 * number(str, temp_index));
		index = temp_index;
		delete[] p_str;     //�� �������� ������� ��������� ������
		return value;
	}
	else if (strcmp(p_str, "ctg") == 0) //������� � ��������
	{
		value = 1/tan(3.141592 / 180 * number(str, temp_index));
		index = temp_index;
		delete[] p_str;     //�� �������� ������� ��������� ������
		return value;
	}
	else if (strcmp(p_str, "sqrt") == 0) //������ 
	{
		value = sqrt(number(str, temp_index));
		index = temp_index;
		delete[] p_str;     //�� �������� ������� ��������� ������
		return value;
	}
	else if (strcmp(p_str, "lg") == 0) //��������
	{
		value = log10(number(str, temp_index));
		index = temp_index;
		delete[] p_str;     //�� �������� ������� ��������� ������
		return value;
	}
	else if (strcmp(p_str, "e") == 0) //����������
	{
		value = 2.7182818284590452354;
		index = temp_index;
		delete[] p_str;     //�� �������� ������� ��������� ������
		return value;
	}
	else if (strcmp(p_str, "pi") == 0) //�������� pi
	{
		value = 3.1415926535897932385;
		index = temp_index;
		delete[] p_str;     //�� �������� ������� ��������� ������
		return value;
	}
	else if (strcmp(p_str, "ln") == 0) //��������
	{
		value = log(number(str, temp_index));
		index = temp_index;
		delete[] p_str;     //�� �������� ������� ��������� ������
		return value;
	}
	else
	{
		return value;
	}
}

double number(char* str, int& index)
{
	double value = 0.0;                 //������ �������������� ��������
	if (*(str + index) == '(')
	{
		char* p_substr = 0;
		p_substr = extract(str, ++index);
		value = expr(p_substr);
		delete[] p_substr;
		return value;
	}
	//������������ ����, ���������� ������� � �����
	while (isdigit(*(str + index)))       //���� ����������� ������� ����� 
		value = 10 * value + (*(str + index++) - '0');
	if (*(str + index) != '.')          //���� �� �����, ��������� �� ���������� �����
		return value;
	double factor = 1.0;             //��������� ��� ���������� ��������
	//��� ���� ������������ ����, ���������� ���������� �����
	while (isdigit(*(str + (++index)))) //��������� ����, ���� ���� ����� 
	{
		factor *= 0.1;
		value = value + (*(str + index) - '0') * factor;
	}
	return value;
}

char* extract(char* str, int& index)
{
	char buffer[MAX];       //��������� ������������ ��� ���������
	char* p_str = 0;        //��������� �� ����� ������ ��� ��������
	int numL = 0;           //������� ��������� ����� ������
	int buf_index = index;  //��������� ��������� �������� index
	do
	{
		buffer[index - buf_index] = *(str + index); //�������� ������ ������� ������ � ���������
		switch (buffer[index - buf_index]) //�������, �� ��� �� ������
		{
		case ')':
			if (numL == 0)
			{
				buffer[index - buf_index] = '\0'; //���� ������� �������� ������, ������ ������ ����� ������
				++index;    //������������� ������ �� ��������� �� ��������� �������
				p_str = new char[index - buf_index];
				if (!p_str)
				{
					exit(1);
				}
				strcpy_s(p_str, index - buf_index, buffer); //� �������� ��������� � ����� ������
				return p_str;
			}
			else
				numL--;     //��������� ������� ������
			break;
		case '(':
			numL++;         //�������������� �����������
			break;
		}
	} while (*(str + index++) != '\0');     //������������� ������ � ��������� �������
	exit(1);
	return p_str;
}
