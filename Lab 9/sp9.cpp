#include<iostream>
#include <time.h>   // Директива нужна для инициализации функции rand()
#include <locale.h>
#define N 3
#define M 3
int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");
	int i, j, tmp;
	int mas[N][M];
	int mas1[N][M];
	int sum[N][M] = { 0 };
	printf("\nИсходная матрица:\n");
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			mas[i][j] = rand() % 10;
			printf("%d ", mas[i][j]);
		}
		printf("\n");
	}
	_asm {
		//          for (i = 0; i<N; i++)                     
		xor         ebx, ebx
		xor         esi, esi
		mov         dword ptr i, ebx

		//      {
		//          for (j = i; j < M; j++)
		m1 :
		mov         eax, dword ptr i
			mov         dword ptr j, eax
			imul        edx, dword ptr j, 0cH
			shl         eax, 2
			add         eax, ebx
			add         edx, esi
			m2 :
		cmp         dword ptr j, 3
			jge         m3

			//          {
			//              tmp = mas[j][i];
			mov         ecx, dword ptr mas[edx]
			inc         dword ptr j
			mov         dword ptr tmp, ecx
			mov         ecx, dword ptr mas[eax]

			//              mas[j][i] = mas[i][j];
			//              mas[i][j] = tmp;
			//         }
			add         eax, 4
			mov         dword ptr mas[edx], ecx

			mov         ecx, dword ptr tmp
			add         edx, 0cH
			mov         mas[eax - 4], ecx
			jmp         m2
			m3 :
		mov         eax, dword ptr i

			//      }
			add         ebx, 0cH
			inc         eax
			add         esi, 4
			mov         dword ptr i, eax
			cmp         ebp, eax
			jg			m1
	}
	printf("\nТранспортированная матрица:\n");
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			printf("%d ", mas[i][j]);
		}
		printf("\n");
	}
	std::cout << "Первая матрица для сложения" << '\n';
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			mas1[i][j] = rand() % 10;
			printf("%d ", mas1[i][j]);
		}
		printf("\n");
	}
	std::cout << "Вторая матрица для сложения" << '\n';
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			printf("%d ", mas[i][j]);
		}
		printf("\n");
	}
	_asm
	{
		XOR   EDX, EDX
		MOV   ECX, N*M
		ADD_LOOP :
		MOV   EAX, mas[EDX]
			ADD   EAX, mas1[EDX]
			MOV   sum[EDX], EAX
			ADD   EDX, 4
			LOOP  ADD_LOOP
	}
	std::cout << "Результирующия матрица" << '\n';
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			printf("%d ", sum[i][j]);
		}
		printf("\n");
	}
	std::cout << "Первая матрица для умножения" << '\n';
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			mas1[i][j] = rand() % 10;
			printf("%d ", mas1[i][j]);
		}
		printf("\n");
	}
	std::cout << "Вторая матрица для умножения" << '\n';
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			printf("%d ", mas[i][j]);
		}
		printf("\n");
	}
	_asm
	{
		XOR   EDX, EDX
		MOV   ECX, N*M
		ADD_LOOPP :
		MOV   EAX, mas[EDX]
			MUL   mas1[EDX]
			MOV   sum[EDX], EAX
			ADD   EDX, 4
			LOOP  ADD_LOOPP
	}
	std::cout << "Результирующия матрица" << '\n';
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			printf("%d ", sum[i][j]);
		}
		printf("\n");
	}

}

