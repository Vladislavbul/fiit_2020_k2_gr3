#include <iostream>
#pragma once
using namespace std;

class link
{
public:
	int pow;
	double a;
	link* next;
	link(int _powx, int _powy, int _powz, double _a = 0)
	{

		pow = _powx + _powy * 20 + _powz * 400;
		a = _a;
		next = NULL;
	}
	link(const link& t)
	{
		pow = t.pow;
		a = t.a;
		next = NULL;
	}

	link(int _pow = 0, double _a = 0)
	{
		pow = _pow;
		a = _a;
		next = NULL;
	}

	void setx(int x)
	{
		int _pow = pow;
		int powx = _pow % 20;
		_pow /= 20;
		int powy = _pow % 20;
		_pow /= 20;
		int powz = _pow % 20;
		_pow /= 20;
		powx = x;
		pow = powx + powy * 20 + powz * 400;
	}

	void sety(int y)
	{
		int _pow = pow;
		int powx = _pow % 20;
		_pow /= 20;
		int powy = _pow % 20;
		_pow /= 20;
		int powz = _pow % 20;
		_pow /= 20;
		powy = y;
		pow = powx + powy * 20 + powz * 400;
	}


	void setz(int z)
	{
		int _pow = pow;
		int powx = _pow % 20;
		_pow /= 20;
		int powy = _pow % 20;
		_pow /= 20;
		int powz = _pow % 20;
		_pow /= 20;
		powz = z;
		pow = powx + powy * 20 + powz * 400;
	}

	friend bool operator <(const link& x, const link& y);
	friend bool operator >=(const link& x, const link& y);
	friend bool operator ==(const link& x, const link& y);
	friend link operator *(const link& x, const link& y);
	friend ostream& operator<<(ostream& out, const link& t);
	friend istream& operator>>(istream& in, link& t);
};
