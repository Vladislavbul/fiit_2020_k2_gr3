#pragma once

#include "Monom.h"
#include <string>
#include <iostream>
#include "TList.h"

using namespace std;

class Polinom
{
private:
	TList<int, float>* monoms;
	void SortMonoms();
	void SimilarMonoms();
public:
	Polinom();
	Polinom(TList<int, float>* list);
	Polinom(const string&);
	Polinom(const Polinom& list);
	~Polinom();

	Polinom operator + (const Polinom& polynom)const;
	Polinom operator + (const TNode<int, float>& monom);
	Polinom operator - () const;
	Polinom operator - (const Polinom& polynom);
	Polinom operator - (const TNode<int, float>& monom);
	Polinom operator * (const Polinom& polynom)const;
	Polinom operator *(const TNode<int, float>& monom)const;
	bool operator ==(const Polinom& polynom)const;
	const Polinom& operator= (const Polinom& polynom);
	friend ostream& operator <<(std::ostream& out, const Polinom& pol);
};

Polinom::Polinom()
{
	monoms = new TList<int, float>();
}

Polinom::Polinom(TList<int, float>* list)
{
	list->Reset();
	while (!list->IsEnded())
	{
		if (list->GetCurrent()->key > 999 || list->GetCurrent()->key < 0)
			throw "invalid parameter";
		list->Next();
	}
	monoms = new TList<int, float>(*list);
	SimilarMonoms();
	SortMonoms();
}

Polinom::Polinom(const Polinom& list)
{
	monoms = new TList<int, float>(*list.monoms);
}

Polinom :: ~Polinom()
{
	delete monoms;
}

void Polinom::SortMonoms()
{
	if (monoms->GetFirst() == nullptr)
		return;
	if (monoms->GetFirst()->pNext == nullptr)
		return;
	TNode<int, float>* a, *b, *p, *h = nullptr;
	for (TNode<int, float>* i = monoms->GetFirst(); i != nullptr; ) {
		a = i;
		i = i->pNext;
		b = h;
		for (p = nullptr; (b != nullptr) && (a->key < b->key); ) {
			p = b;
			b = b->pNext;
		}

		if (p == nullptr) {
			a->pNext = h;
			h = a;
		}
		else {
			a->pNext = b;
			p->pNext = a;
		}
	}
	if (h != nullptr)
		monoms->pFirst = h;
	monoms->Reset();
}

void Polinom::SimilarMonoms()
{
	monoms->Reset();
	while (!monoms->IsEnded())
	{
		TNode<int, float>* tmp = monoms->GetNext();
		TNode<int, float>* prev_tmp = monoms->GetCurrent();
		while (tmp != nullptr)
		{
			if (monoms->GetCurrent()->key == tmp->key)
			{
				if (monoms->GetCurrent()->pData == -tmp->pData)
				{
					monoms->Remove(tmp->key);
					monoms->Remove(tmp->key);
					tmp = monoms->GetNext();
					prev_tmp = monoms->GetCurrent();
					continue;
				}
				else
				{
					monoms->GetCurrent()->pData += tmp->pData;
					TNode<int, float>* node = tmp;
					prev_tmp->pNext = tmp->pNext;
					if (monoms->GetNext() == node)
						monoms->pNext = node->pNext;
					delete node;
					tmp = prev_tmp->pNext;
					continue;
				}
			}
			tmp = tmp->pNext;
			prev_tmp = prev_tmp->pNext;
		}
		monoms->Next();
	}
	monoms->Reset();
}

Polinom::Polinom(const string& polinom)
{
	monoms = new TList<int, float>();
	string str = polinom;
	unsigned int i = 0;
	float coeff = 1;
	bool is_x = false;
	bool is_y = false;
	bool is_z = false;
	int deg_x = 0;
	int deg_y = 0;
	int deg_z = 0;
	while (i < str.length())
	{
		do
		{
			if (isdigit(str[i]) && !is_x && !is_y && !is_z)
			{
				string StrCoeff;
				while (isdigit(str[i]))
				{
					if (str[i + 1] == '.')
					{
						StrCoeff += str[i];
						StrCoeff += str[i + 1];
						i = i + 2;
					}
					else
					{
						StrCoeff += str[i];
						i++;
					}
				}
				coeff *= (float)(atof(StrCoeff.c_str()));
				continue;
			}
			if (str[i] == '^')
			{
				i++;
				continue;
			}
			if (str[i] == 'x')
			{

				is_x = true;
				is_y = false;
				is_z = false;
				i++;

			}
			if (is_x && (str[i] == 'y' || str[i] == 'z' || str[i] == ' ' || str[i] == '+' || str[i] == '-'))
			{
				deg_x = 1;
				is_x = false;
				continue;
			}
			if (is_x && isdigit(str[i]))
			{
				if (isdigit(str[i + 1]))
					throw "degree > 9";
				deg_x = (int)str[i] - 48;
				is_x = false;
				i++;
				continue;
			}
			if (is_x && (i == str.length()))
			{
				deg_x = 1;
				is_x = false;
				continue;
			}
			if (is_x && (i + 1 == str.length()))
			{
				deg_x = 1;
				is_x = false;
				i++;
			}
			if (str[i] == 'y')
			{
				is_x = false;
				is_y = true;
				is_z = false;
				i++;
			}
			if (is_y && (str[i] == 'x' || str[i] == 'z' || str[i] == ' ' || str[i] == '+' || str[i] == '-'))
			{
				deg_y = 1;
				is_y = false;
				continue;
			}
			if (is_y && isdigit(str[i]))
			{
				if (isdigit(str[i + 1]))
					throw "degree > 9";
				deg_y = (int)str[i] - 48;
				is_y = false;
				i++;
				continue;
			}
			if (is_y && i == str.length())
			{
				deg_y = 1;
				is_y = false;
				continue;
			}
			if (is_y && i + 1 == str.length())
			{
				deg_y = 1;
				is_y = false;
				i++;
			}

			if (str[i] == 'z')
			{
				is_x = false;
				is_y = false;
				is_z = true;
				i++;
			}
			if (is_z && (str[i] == 'x' || str[i] == 'y' || str[i] == ' ' || str[i] == '+' || str[i] == '-'))
			{
				deg_z = 1;
				is_z = false;
				continue;
			}
			if (is_z && isdigit(str[i]))
			{
				if (isdigit(str[i + 1]))
					throw "degree > 9";
				deg_z = (int)str[i] - 48;
				is_z = false;
				i++;
				continue;
			}
			if (is_z && i == str.length())
			{
				deg_z = 1;
				is_z = false;
				continue;
			}
			if (is_z && i + 1 == str.length())
			{
				deg_z = 1;
				is_z = false;
				i++;
			}
			if (str[i] == '+')
			{
				i++;
				continue;
			}
			if (str[i] == '-')
			{
				coeff *= -1;
				i++;
				continue;
			}
			if (str[i] == ' ')
			{
				i++;
				continue;
			}
		} while ((!is_x || !is_y || !is_z) && !((str[i] == '+') || (str[i] == '-')) && (i != str.length()));
		TNode<int, float>* NewMon = new TNode<int, float>(deg_x, deg_y, deg_z, coeff);
		monoms->InsertEnd(NewMon);
		deg_x = deg_y = deg_z = 0;
		coeff = 1;
	}
	SimilarMonoms();
	SortMonoms();
}

Polinom Polinom::operator+(const Polinom& polynom)const
{
	if (monoms->IsEmpty())
		return polynom;
	if (polynom.monoms->IsEmpty())
		return *this;
	Polinom sum;
	Polinom pol1(*this);
	Polinom pol2(polynom);
	pol1.monoms->Reset();
	pol2.monoms->Reset();
	while (!pol1.monoms->IsEnded() && !pol2.monoms->IsEnded())
	{
		TNode<int, float> m1(pol1.monoms->GetCurrent()->key, pol1.monoms->GetCurrent()->pData);
		TNode<int, float> m2(pol2.monoms->GetCurrent()->key, pol2.monoms->GetCurrent()->pData);
		if (m1 > m2)
		{
			sum = sum + m1;
			pol1.monoms->Next();
		}
		else if (m1 < m2)
		{
			sum = sum + m2;
			pol2.monoms->Next();
		}
		else if (m1.key == m2.key)
		{
			if (m1.pData + m2.pData != 0)
			{
				TNode<int, float> SumMon = m1 + m2;
				sum = sum + SumMon;
			}
			pol2.monoms->Next();
			pol1.monoms->Next();
		}
	}
	while (!pol2.monoms->IsEnded())
	{
		TNode<int, float> m2(pol2.monoms->GetCurrent()->key, pol2.monoms->GetCurrent()->pData);
		sum = sum + m2;
		pol2.monoms->Next();
	}
	while (!pol1.monoms->IsEnded())
	{
		TNode<int, float> m1(pol1.monoms->GetCurrent()->key, pol1.monoms->GetCurrent()->pData);
		sum = sum + m1;
		pol1.monoms->Next();
	}
	sum.monoms->Reset();
	return sum;
}

Polinom Polinom::operator-(const Polinom& polynom)
{
	return (Polinom(*this) + (-polynom));
}

Polinom Polinom::operator-() const
{
	Polinom tmp(*this);
	tmp.monoms->Reset();
	while (!tmp.monoms->IsEnded())
	{
		tmp.monoms->pCurrent->pData = -tmp.monoms->pCurrent->pData;
		tmp.monoms->Next();
	}
	tmp.monoms->Reset();
	return tmp;
}

bool Polinom::operator==(const Polinom& polynom) const
{
	TNode<int, float>* first = monoms->pFirst;////
	TNode<int, float>* second = polynom.monoms->pFirst;
	while (first != nullptr && second != nullptr && (*first == *second))
	{
		first = first->pNext;
		second = second->pNext;
	}
	if (first == nullptr && second == nullptr)///
		return true;
	return false;
}

const Polinom& Polinom::operator=(const Polinom& polynom)
{
	if (*this == polynom)
		return *this;
	delete monoms;
	monoms = new TList<int, float>(*polynom.monoms);
	return *this;
}

Polinom Polinom::operator+(const TNode<int, float>& monom)
{
	Polinom res;
	bool FlagOfAddMonom = false;
	monoms->Reset();
	while (!monoms->IsEnded()) //////сначала ищем позицию, куда вставлять, потом делаем вставку
	{
		TNode<int, float> CurrentMon(monoms->GetCurrent()->key, monoms->GetCurrent()->pData);
		if (CurrentMon > monom)
			res.monoms->InsertEnd(&CurrentMon);
		else if (CurrentMon.key == monom.key)
		{
			if (CurrentMon.pData + monom.pData != 0)
				res.monoms->InsertEnd(CurrentMon.key, CurrentMon.pData + monom.pData);
			FlagOfAddMonom = true;
		}
		else if (CurrentMon < monom)
		{
			if (FlagOfAddMonom)
				res.monoms->InsertEnd(&CurrentMon);
			else
			{
				if (monom.pData != 0)
					res.monoms->InsertEnd(monom.key, monom.pData);
				FlagOfAddMonom = true;
				continue;
			}
		}
		monoms->Next();
	}
	if (!FlagOfAddMonom)
		res.monoms->InsertEnd(monom.key, monom.pData);
	monoms->Reset();
	return res;
}

Polinom Polinom::operator-(const TNode<int, float>& monom)
{
	return(Polinom(*this) + TNode<int, float>(monom.key, -monom.pData));
}

Polinom Polinom::operator*(const Polinom& polynom)const
{
	if (polynom.monoms->IsEmpty())
		return *this; ///
	Polinom product;
	Polinom pol(polynom);
	pol.monoms->Reset();
	while (!pol.monoms->IsEnded())
	{
		TNode<int, float> tmp1(pol.monoms->GetCurrent()->key, pol.monoms->GetCurrent()->pData);
		Polinom tmp2(Polinom(*this) * tmp1);
		product = product + tmp2; //product = product + copy * tmp1

		pol.monoms->Next();
	}
	return product;
}

Polinom Polinom::operator*(const TNode<int, float>& monom)const
{
	Polinom res;
	Polinom pol(*this);
	if (monom.pData == 0)
		return res;
	pol.monoms->Reset();
	while (!pol.monoms->IsEnded())
	{
		TNode<int, float> tmp(pol.monoms->GetCurrent()->key, pol.monoms->GetCurrent()->pData);
		tmp = tmp * monom;
		if (tmp.pData != 0)
			res = res + tmp;
		pol.monoms->Next();
	}
	return res;
}

ostream& operator <<(std::ostream& out, const Polinom& pol)
{
	pol.monoms->Reset();
	while (!pol.monoms->IsEnded())
	{
		int deg_x = pol.monoms->GetCurrent()->key / 100;
		int deg_y = (pol.monoms->GetCurrent()->key - deg_x * 100) / 10;
		int deg_z = pol.monoms->GetCurrent()->key - deg_x * 100 - deg_y * 10;
		if (pol.monoms->GetCurrent()->pData == 0)
		{
			pol.monoms->Next();
			continue;
		}
		else
		{
			if (pol.monoms->GetCurrent()->pData != 1 && pol.monoms->GetCurrent()->pData != -1)
			{
				if (pol.monoms->GetCurrent()->pData > 0)
					out << "+" << pol.monoms->GetCurrent()->pData;
				if (pol.monoms->GetCurrent()->pData < 0)
					out << pol.monoms->GetCurrent()->pData;
			}
			if (pol.monoms->GetCurrent()->pData == -1)
				out << "-";
			if (pol.monoms->GetCurrent()->pData == 1 && pol.monoms->GetCurrent() != pol.monoms->GetFirst())
				out << "+";
			if (deg_x > 0 && deg_x != 1)
				out << "x^" << deg_x;
			if (deg_x == 1)
				out << "x";
			if (deg_y > 0 && deg_y != 1)
				out << "y^" << deg_y;
			if (deg_y == 1)
				out << "y";
			if (deg_z > 0 && deg_z != 1)
				out << "z^" << deg_z;
			if (deg_z == 1)
				out << "z";
		}
		pol.monoms->Next();
	}
	return out;
}