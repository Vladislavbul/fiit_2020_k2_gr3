#include "monomial.h"

TMonom::TMonom()
{
	next = NULL;
	power = NULL;
	coeff = 0;
	n = 0;
}

TMonom::TMonom(int _n, int* _power, double _coeff)
{
	if (_n < 0)
		throw -1;
	else if (_n == 0)
	{
		power = NULL;
		next = NULL;
		n = _n;
		coeff = _coeff;
	}
	else
	{
		n = _n;
		coeff = _coeff;
		next = NULL;
		power = new int[_n];
		for (int i = 0; i < _n; i++)
		{
			if (_power[i] >= 0)
				power[i] = _power[i];
			else
				throw -1;
		}
	}
}

TMonom::TMonom(TMonom &A)
{
	n = A.n;
	coeff = A.coeff;
	next = A.next;
	power = new int[n];
	for (int i = 0; i < n; i++)
	{
		power[i] = A.power[i];
	}
}

TMonom::~TMonom()
{
	if (power != 0)
		delete[]power;
	n = 0;
	coeff = 0;
	next = 0;
}

void TMonom::SetNext(TMonom* _next)
{
	next = _next;
}

void TMonom::SetPower(int* _power)
{
	for (int i = 0; i < n; i++)
	{
		if (_power[i] >= 0)
			power[i] = _power[i];
		else
			throw -1;
	}
}

void TMonom::SetCoeff(double _coeff)
{
	coeff = _coeff;
}

void TMonom::SetN(int _n)
{
	if (_n < 0)
		throw -1;
	else if (_n == 0)
	{
		if (power != 0)
			delete[] power;
		n = 0;
		power = 0;
	}
	else
	{
		int *temp = new int[n];
		for (int i = 0; i < n; i++)
			temp[i] = power[i];
		delete[]power;
		int i = 0;
		power = new int[_n];
		if (n < _n)
		{
			for (; i < n; i++)
				power[i] = temp[i];
			for (; i < _n; i++)
				power[i] = 0;
		}
		if (_n < n)
			for (; i < _n; i++)
				power[i] = temp[i];
		n = _n;
	}
}


TMonom* TMonom::GetNext()
{
	return next;
}

int* TMonom::GetPower()
{
	return power;
}

double TMonom::GetCoeff()
{
	return coeff;
}

int TMonom::GetN()
{
	return n;
}

TMonom& TMonom::operator=(TMonom& A)
{
	if (n != A.n)
		throw -1;
	coeff = A.coeff;
	n = A.n;
	next = A.next;
	delete[] power;
	power = new int[n];
	for (int i = 0; i < n; i++)
		power[i] = A.power[i];
	return *this;
}

TMonom TMonom::operator+(TMonom& A)
{
	TMonom temp(A);
	if (n != A.n)
		throw -1;
	if (!(*this == A))
		throw -1;
	temp.coeff = coeff + A.coeff;
	return temp;
}
TMonom TMonom::operator+=(TMonom & A)
{
	if (n != A.n)
		throw -1;
	if (!(*this == A))
		throw -1;
	coeff += A.coeff;
	return *this;
}

TMonom TMonom::operator-(TMonom& A)
{
	TMonom temp(A);
	if (n != A.n)
		throw -1;
	if (!(*this == A))
		throw -1;
	temp.coeff = coeff - A.coeff;
	return temp;
}

TMonom TMonom::operator-=(TMonom & A)
{
	if (n != A.n)
		throw -1;
	if (!(*this == A))
		throw -1;
	coeff -= A.coeff;
	return *this;
}

TMonom TMonom::operator*(TMonom& A)
{
	if (n != A.n)
		throw -1;
	TMonom temp(A);
	temp.coeff = coeff * A.coeff;
	for (int i = 0; i < n; i++)
		temp.power[i] = power[i] + A.power[i];
	return temp;
}

TMonom TMonom::operator*=(TMonom& A)
{
	if (n != A.n)
		throw -1;
	coeff = coeff * A.coeff;
	for (int i = 0; i < n; i++)
		power[i] += A.power[i];
	return *this;
}

bool TMonom::operator==(TMonom& A)
{
	if (n != A.n)
		throw -1;
	for (int i = 0; i < n; i++)
		if (power[i] != A.power[i])
			return false;
	return true;
}

bool TMonom::operator>(TMonom& A)
{
	if (n != A.n)
		throw -1;
	if (*this == A)
		throw -1;
	for (int i = 0; i < n; i++)
	{
		if (power[i] == A.power[i])
			continue;
		else if (power[i] > A.power[i])
			return true;
		else
			return false;
	}
	return true;
}

bool TMonom::operator<(TMonom& A)
{
	if (n != A.n)
		throw -1;
	if (*this == A)
		throw -1;
	for (int i = 0; i < n; i++)
	{
		if (power[i] == A.power[i])
			continue;
		else if (power[i] < A.power[i])
			return true;
		else
			return false;
	}
	if (coeff > A.coeff)
		return false;
	return true;
}