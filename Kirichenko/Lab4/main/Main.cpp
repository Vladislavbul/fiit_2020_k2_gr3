#include "list.h"
#include "polinom.h"
#include <iostream>

using namespace std;

void main()
{ 
	setlocale(LC_ALL, "Russian");
	try
	{
		int c = 0;
		while (c == 0)
		{
			cout << "Введите полином P1" << endl;
			Polinom p1;
			cin >> p1;
			cout << "Введите полином P2" << endl;
			Polinom p2;
			cin >> p2;
			cout << "Выберите операцию с полиномами" << endl;
			cout << "1. P1 + P2" << endl;
			cout << "2. P1 - P2" << endl;
			cout << "3. P1 * P2" << endl;
			cout << "Если вы хотите закончить, введите 0" << endl;
			int counter;
			cin >> counter;
			Polinom result;
			while (counter != 0)
			{
				bool flag = true;
				switch (counter)
				{
				case 1:
				{
					result = p1 + p2;
					break;
				}
				case 2:
				{
					result = p1 - p2;
					break;
				}
				case 3:
				{
					result = p1 * p2;
					break;
				}
				default:
				{
					cout << "Введено неверно" << endl;
					flag = false;
					break;
				}
				}
				if (flag == true)
				{
					cout << "Результат операции: " << result << endl;
					cout << "Выберете операцию или введите 0 " << endl;
				}
				cin >> counter;
			}
			int ad = 19;
			cout << "Если вы хотите ввести новые полиномы, нажмите «0», если нет,то  нажмите любую другую  цифру" << endl;
			cin >> c;
			getchar();
		}
	}
	catch (const char* error)
	{
		cout << error << endl;
	}
}