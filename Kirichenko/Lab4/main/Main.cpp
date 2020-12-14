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
			cout << "������� ������� P1" << endl;
			Polinom p1;
			cin >> p1;
			cout << "������� ������� P2" << endl;
			Polinom p2;
			cin >> p2;
			cout << "�������� �������� � ����������" << endl;
			cout << "1. P1 + P2" << endl;
			cout << "2. P1 - P2" << endl;
			cout << "3. P1 * P2" << endl;
			cout << "���� �� ������ ���������, ������� 0" << endl;
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
					cout << "������� �������" << endl;
					flag = false;
					break;
				}
				}
				if (flag == true)
				{
					cout << "��������� ��������: " << result << endl;
					cout << "�������� �������� ��� ������� 0 " << endl;
				}
				cin >> counter;
			}
			int ad = 19;
			cout << "���� �� ������ ������ ����� ��������, ������� �0�, ���� ���,��  ������� ����� ������  �����" << endl;
			cin >> c;
			getchar();
		}
	}
	catch (const char* error)
	{
		cout << error << endl;
	}
}