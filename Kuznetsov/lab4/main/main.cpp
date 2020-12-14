#include <iostream>
#include "polinomial.h"
#include "monomial.h"

using namespace std;

int main()
{
	int mas1[] = { 1, 2, 3 };
    int mas2[] = { 7, 3, 4};
    int mas3[] = { 4, 9, 5 };
    int mas4[] = { 5, 1, 3 };

	TMonom M1(3, mas1, 2),  M2(3, mas2, 1), M3(3, mas3, 4),  M4(3, mas4, 8); 

	cout << "Monomial 1: " << M1 << endl;
	cout << "Monomial 2: " << M2 << endl;
	cout << "Monomial 3: " << M3 << endl;
	cout << "Monomial 4: " << M4 << endl << endl;
	
	TPolynom P1(3), P2(3);
	P1 += M1;
	P1 += M2;
	P2 += M3;
	P2 += M4;
	
	cout << "P1 = M1 + M2 = " << P1 << endl;
    cout << "P2 = M3 + M4 = " << P2 << endl;
    TPolynom P(3);
    P = P1 + P2;
    cout << "P1 + P2 = " << P << endl;
    P = P1 - P2;
    cout << "P1 - P2 = " << P << endl;
	P = P1 * P2;
	cout << "P1 * P2 = " << P << endl;
	return 0;
}