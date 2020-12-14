#include "Polynom.h"

using namespace std;

Monom::Monom(double _coef, int _power)
{
	coef = _coef;
	power = _power;
}

Polynom::Polynom(const Polynom & polynom)
{
	monoms = polynom.monoms;
	size = polynom.size;
}

void Polynom::printAll()
{
	Polynom temp(*this);
	while (temp.size != 0)
	{
		if (temp.monoms.getHead().getPower() == 1) 
		{
			if (temp.monoms.getHead().getCoef() == 1)
			{
				cout << "x";
				temp.monoms.pop();
				temp.size--;
			}
			else if (temp.monoms.getHead().getCoef() == -1)
			{
				cout << "-x";
				temp.monoms.pop();
				temp.size--;
			}
			else if (temp.monoms.getHead().getCoef() == 0)
			{
				temp.monoms.pop();
				temp.size--;
				continue;
			}
			else
			{
				cout << temp.monoms.getHead().getCoef()<<"x";
				temp.monoms.pop();
				temp.size--;
			}
			if (!temp.monoms.isEmpty())
			{
				if (temp.monoms.getHead().getCoef() > 0)
				{
					cout << "+";
				}
			}
			continue;
		}
		if (temp.monoms.getHead().getPower() == 0)
		{
			if (temp.monoms.getHead().getCoef() == 0)
			{
				temp.monoms.pop();
				temp.size--;
				continue;
			}
			else
			{
				cout << temp.monoms.getHead().getCoef();
				temp.monoms.pop();
				temp.size--;
			}
			if (!temp.monoms.isEmpty())
			{
				if (temp.monoms.getHead().getCoef() > 0)
				{
					cout << "+";
				}
			}
			continue;

		}
		if (temp.monoms.getHead().getCoef() == 1)
		{
			cout << "x^" << temp.monoms.getHead().getPower();
			temp.monoms.pop();
			temp.size--;
		}
		else if (temp.monoms.getHead().getCoef() == -1)
		{
			cout << "-x^" << temp.monoms.getHead().getPower();
			temp.monoms.pop();
			temp.size--;
		}
		else if (temp.monoms.getHead().getCoef() == 0)
		{
			temp.monoms.pop();
			temp.size--;
			continue;
		}
		else
		{
			cout << temp.monoms.pop();
			temp.size--;
		}
		if (!temp.monoms.isEmpty())
		{
			if (temp.monoms.getHead().getCoef() > 0)
			{
				cout << "+";
			}
		}
	}
}

void Polynom::resize()
{
	int tempSize = 0;
	Polynom temp(*this);
	while (!temp.monoms.isEmpty())
	{
		temp.monoms.pop();
		tempSize++;
	}
	size = tempSize;
}

void Polynom::parse(string str)
{
	bool nextPower = false;
	bool minus = false;
	string tempCoef;
	string tempPower = "";
	Monom temp;
	
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == 'x')
		{
			nextPower = true;
		}
		if (str[i] == '-')
		{
			minus = true;
		}
		if (nextPower == false )
		{
			if (isdigit(str[i]) && str[i] != '+' && str[i] != '-')
			{
				tempCoef += str[i];
			}
			if (str[i + 1] == 'x')
			{
				if (!tempCoef.empty())
				{
					temp.setCoef(stod(tempCoef));
				}
				if (minus) 
				{
					temp.setCoef(-temp.getCoef());
					minus = false;
				}
				tempCoef = "";
				nextPower = true;
			}
			if (i == str.length() - 1 ||str[i + 1] == '+' || str[i + 1] == '-')
			{
				if (!tempCoef.empty())
				{
					temp.setCoef(stod(tempCoef));
				}
				if (minus)
				{
					temp.setCoef(-temp.getCoef());
					minus = false;
				}
				tempCoef = "";
				temp.setPower(0);
				monoms.pushBack(temp);
				temp.setCoef(1);
				temp.setPower(1);
				size++;
			}
		}
		else
		{
			if (isdigit(str[i]))
			{
				tempPower += str[i];
			}
			if (str[i + 1] == '+' || str[i + 1] == '-' || i == str.length() - 1)
			{
				if (tempPower != "")
				{
					temp.setPower(stoi(tempPower));
				}
				tempPower = "";
				monoms.pushBack(temp);
				temp.setCoef(1);
				temp.setPower(1);
				nextPower = false;
				size++;
			}
		}
	}
}

void Polynom::normalize()
{
	if (size > 1)
	{
		Polynom temp(*this);
		Polynom result;
		Monom resultM;
		int index;
		for (int i = 0; i < temp.size; i++)
		{
			if (!temp.monoms.isEmpty()) 
			{
				resultM = temp.monoms.pop();
				Polynom temp1(temp);
				temp1.resize();
				for (int j = 0; j < temp1.size; j++)
				{
					Monom tempM = temp1.monoms.pop();
					index = temp.monoms.getIndex(tempM);
					if (resultM.getPower() == tempM.getPower())
					{
						resultM.setCoef(resultM.getCoef() + tempM.getCoef());
						temp.monoms.remove(index);
						temp.size--;
					}
				}
				result.monoms.pushBack(resultM);
			}
		}
		result.resize();
		*this = result;
	}
}

bool operator==(const Monom & m1, const Monom & m2)
{
	if (m1.power == m2.power)
	{
		if (m1.coef == m2.coef)
		{
			return true;
		}
	}
	return false;
}

Monom operator+(const Monom & m1, const Monom & m2)
{
	if (m1.power != m2.power)
	{
		throw - 1;
	}
	Monom temp;
	temp.power = m1.power;
	temp.coef = m1.coef + m2.coef;
	return temp;
}

Monom operator-(const Monom & m1, const Monom & m2)
{
	if (m1.power != m2.power)
	{
		throw - 1;
	}
	Monom temp;
	temp.power = m1.power;
	temp.coef = m1.coef - m2.coef;
	return temp;
}

Monom operator*(const Monom & m1, const Monom & m2)
{
	Monom temp;
	temp.power = m1.power + m2.power;
	temp.coef = m1.coef * m2.coef;
	return temp;
}

ostream & operator<<(ostream & out, const Monom & m)
{
	out << m.coef << "x^" << m.power;
	return out;
}

Polynom Polynom::operator+(Polynom& p2)
{
	Polynom res;
	Polynom copy1(*this), copy2(p2);
	Node <Monom>* t1, * t2, * t3;
	t1 = res.monoms.getheadptr();
	t2 = copy1.monoms.getheadptr();
	t3 = copy2.monoms.getheadptr();

	while (t2 && t3)
	{
		if (t2->data.getPower() == t3->data.getPower())
		{
			if (t2->data.getCoef() + t3->data.getCoef())
			{
				Monom p = Monom(t2->data.getCoef() + t3->data.getCoef(), t2->data.getPower());
				res.monoms.pushBack(p);
				res.resize();
				res.normalize();
			}
			t2 = t2->next;
			t3 = t3->next;
		}
		else if (t2->data.getPower() < t3->data.getPower())
		{
			Monom p = Monom(t2->data.getCoef(), t2->data.getPower());
			res.monoms.pushBack(p);
			res.resize();
			res.normalize();
			t2 = t2->next;
		}
		else
		{
			Monom p = Monom(t3->data.getCoef(), t3->data.getPower());
			res.monoms.pushBack(p);
			res.resize();
			res.normalize();
			t3 = t3->next;
		}
	}

	while (t2)
	{
		Monom p = Monom(t2->data.getCoef(), t2->data.getPower());
		res.monoms.pushBack(p);
		res.resize();
		res.normalize();
		t2 = t2->next;
	}

	while (t3)
	{
		Monom p = Monom(t3->data.getCoef(), t3->data.getPower());
		res.monoms.pushBack(p);
		res.resize();
		res.normalize();
		t3 = t3->next;
	}
	return res;
}

/*
Polynom operator+(const Polynom & p1, const Polynom & p2)
{
	Polynom temp1(p1);
	Polynom	temp2(p2);
	for (int i = 0; i < p2.size; i++)
	{
		Monom tempM = temp2.monoms.pop();
		temp1.monoms.pushBack(tempM);
		temp1.resize();
		temp1.normalize();
	}
	return temp1;
}
*/

Polynom Polynom::operator-(Polynom& p2)
{
	Polynom res;
	Polynom copy1(*this), copy2(p2);
	Node <Monom>* t1, * t2, * t3;
	t1 = res.monoms.getheadptr();
	t2 = copy1.monoms.getheadptr();
	t3 = copy2.monoms.getheadptr();

	while (t2 && t3)
	{
		if (t2->data.getPower() == t3->data.getPower())
		{
			if (t2->data.getCoef() - t3->data.getCoef())
			{
				Monom p = Monom(t2->data.getCoef() - t3->data.getCoef(), t2->data.getPower());
				res.monoms.pushBack(p);
				res.resize();
				res.normalize();
			}
			t2 = t2->next;
			t3 = t3->next;
		}
		else if (t2->data.getPower() < t3->data.getPower())
		{
			Monom p = Monom(t2->data.getCoef(), t2->data.getPower());
			res.monoms.pushBack(p);
			res.resize();
			res.normalize();
			t2 = t2->next;
		}
		else
		{
			Monom p = Monom(-t3->data.getCoef(), t3->data.getPower());
			res.monoms.pushBack(p);
			res.resize();
			res.normalize();
			t3 = t3->next;
		}
	}

	while (t2)
	{
		Monom p = Monom(t2->data.getCoef(), t2->data.getPower());
		res.monoms.pushBack(p);
		res.resize();
		res.normalize();
		t2 = t2->next;
	}

	while (t3)
	{
		Monom p = Monom(-t3->data.getCoef(), t3->data.getPower());
		res.monoms.pushBack(p);
		res.resize();
		res.normalize();
		t3 = t3->next;
	}
	return res;
}

/*
Polynom operator-(const Polynom & p1, const Polynom & p2)
{
	Polynom temp1(p1);
	Polynom	temp2(p2);
	for (int i = 0; i < p2.size; i++)
	{
		Monom tempM = temp2.monoms.pop();
		tempM.setCoef(-tempM.getCoef());
		temp1.monoms.pushBack(tempM);
		temp1.resize();
		temp1.normalize();
	}
	return temp1;
}
*/

Polynom operator*(const Polynom & p1, const Polynom & p2)
{
	Polynom result;
	Polynom temp1(p1);
	for (int i = 0; i < p1.size; i++)
	{
		Monom tempM1 = temp1.monoms.pop();
		Polynom	temp2(p2);
		for (int j = 0; j < p2.size; j++)
		{
			Monom tempM2 = temp2.monoms.pop();
			Monom resultM = tempM1 * tempM2;
			result.monoms.pushBack(resultM);
		}
	}
	result.resize();
	result.normalize();
	return result;
}