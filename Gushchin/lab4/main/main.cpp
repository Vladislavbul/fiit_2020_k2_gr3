#include <iostream>
#include "Polinom.h"

using namespace std;

int main()
{
	cout << "Please enter the base of polinoms: " << endl;

	int base = 0;
	cin >> base;

	cout << "Please enter the number of variables: " << endl;

	int number = 0;
	cin >> number;

	vector<string> v;
	string tmp;

	for (int i = 0; i < number; i++)
	{
		cout << "Enter the " << i << " var:" << endl;
		
		cin >> tmp;
		v.push_back(tmp);
	}

	try
	{
		// Examples: 5*x^5*y^1*z^4+7*x^4*y^2*z^1+12*x^3-7*z^2-3
		// 10*x^5*y^1*z^4+7*x^4*y^2*z^1+12*x^3+7*z^2+7-13*x^7*y^1*z^3

		cout << "Enter the polinom number 1: " << endl;
		cin >> tmp;
		Polinom polinom1(tmp, v, base);

		cout << "Enter the polinom number 2: " << endl;
		cin >> tmp;
		Polinom polinom2(tmp, v, base);

		int choice = 0;
		double num = 0;

		do
		{
			cout << "What do you want to perform?" << endl;
			cout << "1. pol1 + pol2" << endl;
			cout << "2. pol1 - pol2" << endl;
			cout << "3. pol2 - pol1" << endl;
			cout << "4. pol1 * pol2" << endl;
			cout << "5. pol1 * number" << endl;
			cout << "6. pol2 * number" << endl << endl;
			cout << "0 to exit" << endl;

			cin >> choice;

			switch (choice)
			{
			case 1:
				cout << polinom1 + polinom2 << endl << endl;
				break;
			case 2:
				cout << polinom1 - polinom2 << endl << endl;
				break;
			case 3:
				cout << polinom2 - polinom1 << endl << endl;
				break;
			case 4:
				cout << polinom1 * polinom2 << endl << endl;
				break;
			case 5:
				cout << "Enter number: " << endl;
				cin >> num;

				cout << polinom1 * num << endl;
				break;
			case 6:
				cout << "Enter number: " << endl;
				cin >> num;

				cout << polinom2 * num << endl;
				break;
			}
		} while (choice);
		


	}
	catch (char* err)
	{
		cout << err;
	}
	return 0;
}