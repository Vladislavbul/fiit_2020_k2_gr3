#pragma once
#include <iostream>
#include "monomial.h"
using namespace std; 
class TPolynom
{
protected:
	TMonom *start;
	int n;          
	int size;      
public:
	TPolynom(int _n = 10);
	TPolynom(TPolynom & P);
	~TPolynom();
	int GetSize();
	int GetN();
	TMonom* GetStart();
	TPolynom operator+(TPolynom &P);
	TPolynom operator-(TPolynom &P);
	TPolynom operator*(TPolynom &P);
	TPolynom &operator=(const TPolynom &P);
	TPolynom &operator+=(TMonom &M);
	TPolynom &operator-=(TMonom &M);
	bool operator==(const TPolynom &P);
	friend std::ostream& operator<<(std::ostream& ostr, TPolynom& P)
        {
	TMonom *temp = P.start;
	if (temp != 0)
	{
		ostr << *temp;
		temp = temp->GetNext();
	}
	while (temp != 0)
	{
		if (temp->GetCoeff() != 0)
			ostr << " + " << *temp;
		temp = temp->GetNext();
	}
	return ostr;
	}
};