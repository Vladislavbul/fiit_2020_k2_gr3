#pragma once
struct Monom
{
	double coef;
	int pow;

	Monom* next;

	Monom()
	{
		next = this;
		coef = 0;
		pow = -1;
	}
};