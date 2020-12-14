#include "Polynom.h"
#include <string>
#include <iostream>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");

	string str1, str2;

	while (true)
	{
		cout << "Вводите полином вида k0x^p0+k1x^p1+..+knx^pn" << endl;

		cout << "Введите первый полином:" << endl;
		cin >> str1;
		Polynom poly1;
		poly1.parse(str1);
		poly1.normalize();

		cout << "Введите второй полином:" << endl;
		cin >> str2;
		Polynom poly2;
		poly2.parse(str2);
		poly2.normalize();

		cout << "Сумма: ";
		Polynom poly3 = poly1 + poly2;
		poly3.printAll();
		cout << endl;

		cout << "Разность (Первый - второй): ";
		poly3 = poly1 - poly2;
		poly3.printAll();
		cout << endl;

		cout << "Умножение: ";
		poly3 = poly1 * poly2;
		poly3.printAll();
		cout << '\n' << endl;
	}
	system("pause");
}