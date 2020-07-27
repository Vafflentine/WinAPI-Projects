#include <iostream>
int result1[32];
void DecimalToBinary(int x, int * masResult);
int Sub(int number1, int number2);
int Div(int number1, int number2);
int main()
{
	setlocale(LC_ALL, "Russian");
	int result[32];
	int firstOperand = 0, secondOperand = 0;
	std::cout << "Ввидите первое число: ";
	std::cin >> firstOperand;
	std::cout << "Ввидите второе число: ";
	std::cin >> secondOperand;
	std::cout << "Ниже реализована функция вычитания. Используемые для этого регистры: eax и ebx"<<'\n';
	std::cout << "Значение регистра eax(тут хранится первое число) до вычитания: ";
	DecimalToBinary(firstOperand, result);
	for (int i = 0; i < 32; i++)
	{
		std::cout << result[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "Значение регистра ebx(тут хранится второе число) до вычитания: ";
	DecimalToBinary(secondOperand, result);
	for (int i = 0; i < 32; i++)
	{
		std::cout << result[i] << " ";
	}
	std::cout << std::endl;
	std::cout<<"Значение регистра eax после вычитания: ";
	DecimalToBinary(Sub(firstOperand, secondOperand)/secondOperand, result);
	for (int i = 0; i < 32; i++)
	{
		std::cout << result[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "Значение регистра ebx после вычитания: ";
	DecimalToBinary(secondOperand, result);
	for (int i = 0; i < 32; i++)
	{
		std::cout << result[i] << " ";
	}
	std::cout << std::endl;



	std::cout << "Ниже реализована функция деление. Используемые для этого регистры: eax,ebx,edx" << '\n';
	std::cout << "Значение регистра eax(тут хранится первое число) до деления: ";
	DecimalToBinary(firstOperand, result);
	for (int i = 0; i < 32; i++)
	{
		std::cout << result[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "Значение регистра ebx(тут хранится второе число) до деления: ";
	DecimalToBinary(secondOperand, result);
	for (int i = 0; i < 32; i++)
	{
		std::cout << result[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "Значение регистра edx(тут хранится остаток от деления) до деления: ";
	for (int i = 0; i < 32; i++)
	{
		result[i] = 0;
		std::cout << result[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "Значение регистра eax после вычитания: ";
	DecimalToBinary(Div(firstOperand, secondOperand), result);
	for (int i = 0; i < 32; i++)
	{
		std::cout << result[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "Значение регистра ebx после вычитания: ";
	DecimalToBinary(secondOperand, result);
	for (int i = 0; i < 32; i++)
	{
		std::cout << result[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "Значение регистра edx после вычитания: ";
	for (int i = 0; i < 32; i++)
	{
		std::cout << result1[i] << " ";
	}
	std::cout << std::endl;

	return 0;
}

void DecimalToBinary(int x, int * masResult)
{
	int mas[32];
	_asm { mov esi, 32 * 4 - 4
	mov cx, 32
		mov eax, x
		mov edx, 0

		jmp check
		m1 : mov mas[esi], 1
		sub esi, 4
		jmp check
		m2 : mov mas[esi], 0
		sub esi, 4

		check :
		JCXZ m3

		bt eax, edx
		dec cx
		inc edx

		jc m1
		jnc m2
		m3 : }

	for (int i = 31; i >= 0; i--)
		masResult[i] = mas[i];
}


int Sub(int number1,int number2)
{
	int i = 0, a = 0;
	_asm {
		mov eax, number1
		mov ebx, number2
		sub eax, ebx
		mov i, eax
		mov a, ebx
	}
	return i*a;
}
	
	
int Div(int number1, int number2)
{
	int a,i,c;
	_asm {
		mov eax, number1
		mov edx, 0
		mov ebx, number2
		div ebx
		mov i,eax
		mov a,ebx
		mov c,edx
	}
	DecimalToBinary(c, result1);
	return i;
}


