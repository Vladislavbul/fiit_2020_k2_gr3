#pragma once
#include "polinomial.h"

TPolynom::TPolynom(int _n)
{
	if (_n <= 0)
		throw -1;
	n = _n;
	size = 0;
	start = 0;
}

TPolynom::TPolynom(TPolynom & P)
{
	n = P.n;
	size = P.size;
	if (P.start == 0)
		start = 0;
	else
	{
		start = new TMonom(*P.start);
		TMonom* a = P.start;
		TMonom* b = start;
		while (a->GetNext() != 0)
		{
			b->SetNext(new TMonom(*(a->GetNext())));
			b = b->GetNext();
			a = a->GetNext();
		}
		b->SetNext(NULL);
	}
}

TPolynom::~TPolynom()
{}

int TPolynom::GetSize()
{
	return size;
}


int TPolynom::GetN()
{
	return n;
}

TMonom* TPolynom::GetStart()
{
	return start;
}

TPolynom TPolynom::operator+(TPolynom & P)
{
	if (this->n != P.n)
		throw -1;
	TPolynom res(n);

	TMonom *a = start; 
	TMonom *b = P.start;
	TMonom *i = res.start;

	while ((a!= 0) && (b != 0))
	{
		TMonom *temp;
		if ((*a) == (*b))
		{
			TMonom h = (*a);
			h += (*b);
			temp = new TMonom(h);
			if (temp->GetCoeff() == 0)
				continue;
			a = a->GetNext();
			b = b->GetNext();
		}
		else if ((*a) < (*b))
		{
			temp = new TMonom((*b));
			if (temp->GetCoeff() == 0)
				continue;
			b = b->GetNext();
		}
		else if ((*a) > (*b))
		{
			temp = new TMonom((*a));
			if (temp->GetCoeff() == 0)
				continue;
			a = a->GetNext();
		}
		if (i == 0)
		{
			i = temp;
			res.start = temp;
			res.size++;
		}
		else
		{
			i->SetNext(temp);
			res.size++;
			i = i->GetNext();
		}
	}
	if (a == 0)
		a = b;
	while (a != 0)
	{
		if (a->GetCoeff() == 0)
			continue;
		i->SetNext(new TMonom(*a));
		a = a->GetNext();
		res.size++;
		i = i->GetNext();
	}
	return res;
}

TPolynom TPolynom::operator-(TPolynom & P)
{
	if (this->n != P.n)
		throw -1;
	TPolynom res(n);
	TMonom *a = start;
	TMonom *b = P.start;
	TMonom	*i = res.start;
	while ((a != 0) && (b != 0))
	{
		TMonom *temp;
		if ((*a) == (*b))
		{
			TMonom h = (*a);
			h -= (*b);
			temp = new TMonom(h);
			a = a->GetNext();
			b = b->GetNext();
		}
		else if ((*a) < (*b))
		{
			temp = new TMonom((*b));
			if (temp->GetCoeff() == 0)
				continue;
			temp->SetCoeff(temp->GetCoeff() * (-1));
			b = b->GetNext();
		}
		else if ((*a) > (*b))
		{
			temp = new TMonom((*a));
			if (temp->GetCoeff() == 0)
				continue;
			a = a->GetNext();
		}
		if (temp->GetCoeff() == 0)
			continue;
		if (i == 0)
		{
			i = temp;
			res.start = temp;
			res.size++;
		}
		else
		{
			i->SetNext(temp);
			res.size++;
			i = i->GetNext();
		}
	}
	while (a != 0)
	{
		if (a->GetCoeff() == 0)
			continue;
		i->SetNext(new TMonom(*a));
		a = a->GetNext();
		res.size++;
		i = i->GetNext();
	}
	while (b!= 0)
	{
		if (b->GetCoeff() == 0)
			continue;
		TMonom temp(*b);
		temp.SetCoeff(temp.GetCoeff() * (-1));
		i->SetNext(&temp);
		b = b->GetNext();
		res.size++;
		i = i->GetNext();
	}
	return res;
}

TPolynom& TPolynom::operator=(const TPolynom & P)
{
	if (*this == P)
		return *this;
	if (this->n != P.n)
		throw -1;
	else
	{
		size = P.size;
		TMonom *a = start, *b = start;
		while (a != 0)
		{
			a = a->GetNext();
			delete b;
			b = a;
		}
		a = P.start->GetNext();
		b = new TMonom(*P.start);
		start = b;
		while (a!= 0)
		{
			b->SetNext(new TMonom(*a));
			b = b->GetNext();
			a = a->GetNext();
		}
		return *this;
	}
}

bool TPolynom::operator==(const TPolynom & P)
{
	if (this->n != P.n)
		throw -1;
	if (this->size != P.size)
		return false;
	TMonom* a = start;
	TMonom* b = P.start;
	while (a != 0)
	{
		if (!(*a == *b))
			return false;
		if (a->GetCoeff() != b->GetCoeff())
			return false;
		a = a->GetNext();
		b = b->GetNext();
	}
	return true;
}


TPolynom &TPolynom::operator+=(TMonom &M)
{
	if (M.GetCoeff() == 0)
		return *this;
	if (start == 0)
		start = new TMonom(M);
	else
	{
		TMonom *a, *b;
		a = start;
		b = start->GetNext();
		if (*start < M)
		{
			TMonom* temp = new TMonom(M);
			temp->SetNext(start);
			start = temp;
		}
		else if (*start == M)
		{
			*start += M;
			if (start->GetCoeff() == 0)
			{
				TMonom* temp = start->GetNext();
				delete[] start;
				start = temp;
			}
		}
		else
		{
			while (b != 0)
			{
				if (*b == M)
				{
					*b += M;
					if (b->GetCoeff() == 0)
					{
						start->SetNext(b->GetNext());
						delete[] b;
					}
					return *this;
				}
				if (*b < M)
				{
					TMonom* temp = new TMonom(M);
					a->SetNext(temp);
					temp->SetNext(b);
					size++;
					return *this;
				}
				a = b;
				b = b->GetNext();
			}
			a->SetNext(new TMonom(M));
		}
	}
	size++;
	return *this;
}

TPolynom &TPolynom::operator-=(TMonom &M)
{
	if (M.GetCoeff() == 0)
		return *this;
	M.SetCoeff(M.GetCoeff() * (-1));
	if (start == 0)
		start = new TMonom(M);
	else
	{
		TMonom *a, *b;
		a = start;
		b = start->GetNext();
		if (*start < M)
		{
			TMonom* temp = new TMonom(M);
			temp->SetNext(start);
			start = temp;
		}
		else if (*start == M)
		{
			*start -= M;
			if (start->GetCoeff() == 0)
			{
				TMonom* temp = start->GetNext();
				delete[] start;
				start = temp;
			}
		}
		else
		{
			while (b != 0)
			{
				if (*b == M)
				{
					*b -= M;
					if (b->GetCoeff() == 0)
					{
						start->SetNext(b->GetNext());
						delete[] b;
					}
	                                  size++;
					return *this;
				}
				if (*b < M)
				{
					TMonom* temp = new TMonom(M);
					a->SetNext(temp);
					temp->SetNext(b);
					size++;
					return *this;
				}
				a = b;
				b = b->GetNext();
			}
			a->SetNext(new TMonom(M));
		}
	}
	size++;
	return *this;
}


TPolynom TPolynom::operator*(TPolynom & P)
{
	if (this->n != P.n)
		throw -1;
	TPolynom res(n);
	TMonom *a = start;
	TMonom *b = P.start;
	while (a != 0)
	{
		if (a->GetCoeff() == 0)
			continue;
		while (b != 0)
		{
			if (b->GetCoeff() == 0)
				continue;
			TMonom h = (*a);
			h *= (*b);
			TMonom* t = new TMonom(h);
			t->SetNext(NULL);
			res += *t;
			b = b->GetNext();
		}
		a = a->GetNext();
		b = P.start;
	}
	return res;
}