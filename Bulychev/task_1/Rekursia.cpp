#include <stdio.h>
#include <iostream>

using namespace std;

void Rekursia(int M[], int l, int a)
{
	if (a < 0 || a >= l) return;
	cout << M[a] << " | ";
	Rekursia(M, l, ++a);
}

int main()
{
	const int size = 10;
	int M[size];
	for (int i = 0; i < size; ++i)
	{
		M[i] = 1 + rand() % 100;
	}

	Rekursia(M, 10, 0);
	return 0;
	system("pause");
}