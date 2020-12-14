#include "Polinom.h"
#include "Monom.h"
#include <iostream>
#include <cmath>

using namespace std;

Polinom::Polinom(const Polinom& r)
{
	numOfPows = r.numOfPows;
	base = r.base;
	var = r.var;

	Monom* tempR = r.head->next;

	head = new Monom;
	head->next = head;

	Monom* tempL = head;

	while (tempR != r.head)
	{
		Monom* copy = new Monom;
		copy->coef = tempR->coef;
		copy->pow = tempR->pow;
		copy->next = tempL->next;

		tempL->next = copy;


		tempL = tempL->next;
		tempR = tempR->next;
	}
}

Polinom::Polinom(string str, vector<string> _var, int _base)
{
	if (_base < 2) throw "Base should be higher than 2";

	head = new Monom;
	head->next = head;

	var = _var;
	numOfPows = var.size();
	base = _base;

	queue<pair<string, ElemType>> q = Parse(str);

	map<string, int> vars;

	for (auto i = var.begin(); i != var.end(); i++)
		vars.insert({ *i, 0 });

	double coef = 0.0;

	int state = 0, sign = 0;

	while (!q.empty())
	{
		if (state == 0)
		{
			if (q.front().second == Operation && (q.front().first == "+" || q.front().first == "-"))
			{
				state = 1;

				if (q.front().first == "+") sign = 1;
				else sign = -1;

				q.pop();

				if (q.empty()) throw "Parse error";

				///////////////////////
				if (q.front().second == Operand)
				{
					state = 2;
					coef = stod(q.front().first);
					q.pop();
				}
				else if (q.front().second == Variable)
				{
					state = 2;
					coef = 1.0;
				}
				else throw "Parse error";

				if (q.empty())
				{
					vector<int> pows;
					for (map<string, int>::iterator i = vars.begin(); i != vars.end(); i++)
					{
						pows.push_back(i->second);
						i->second = 0;
					}

					sortedAdd(coef * sign, toDecimalSystem(pows));
				}
				////////////////////////
			}
			else if (q.front().second == Operand)
			{
				state = 2;
				coef = stod(q.front().first);
				sign = 1;
				q.pop();
			}
			else if (q.front().second == Variable)
			{
				state = 2;
				coef = 1.0;
				sign = 1;
			}
			else throw "Parse error";
		}
		else
		{
			if (q.front().second == Operation && (q.front().first == "+" || q.front().first == "-"))
			{
				vector<int> pows;
				for (map<string, int>::iterator i = vars.begin(); i != vars.end(); i++)
				{
					pows.push_back(i->second);
					i->second = 0;
				}

				sortedAdd(coef * sign, toDecimalSystem(pows));

				state = 0;
			}
			else if (q.front().second == Operation && q.front().first == "*")
			{
				q.pop();
			}
			else if (q.front().second == Variable)
			{
				string tmp = q.front().first;

				q.pop();

				if (!q.empty() && q.front().second == Operation && q.front().first == "^")
				{
					q.pop();

					if (q.front().second == Operand)
					{
						map<string, int>::iterator it = vars.find(tmp);
						if (it != vars.end())
						{
							it->second = stoi(q.front().first);
						}
						else throw "Parse error: unknown var";
						q.pop();
					}
					else throw "Parse error";
				}
				else
				{
					map<string, int>::iterator it = vars.find(tmp);
					if (it != vars.end())
					{
						it->second = 1;
					}
					else throw "Parse error: unknown var";
				}

				if (q.empty())
				{
					vector<int> pows;
					for (map<string, int>::iterator i = vars.begin(); i != vars.end(); i++)
					{
						pows.push_back(i->second);
						i->second = 0;
					}

					sortedAdd(coef * sign, toDecimalSystem(pows));
				}
			}
			else throw "Parse error";
		}
	}
}

vector<int> Polinom::toBaseSystem(int pow) const
{
	vector<int> resPows;
	int temp = pow;

	for (int i = 0; i < numOfPows; i++)
	{
		resPows.push_back(temp % base);
		temp /= base;
	}

	if (temp) throw "Converting to base system error";

	return resPows;
}

int Polinom::toDecimalSystem(const vector<int> v) const
{
	int dec = 0;

	for (int i = 0; i < numOfPows; i++)
		dec += v[i] * pow(base, i);

	return dec;
}

void Polinom::sortedAdd(int coef, int pows)
{
	Monom* p = head;

	while ((p->next != head) && (p->next->pow < pows)) p = p->next;

	if (p->next->pow == pows)
	{
		p = p->next;
		p->coef += coef;
	}
	else
	{
		Monom* t = new Monom;

		t->pow = pows;
		t->coef = coef;

		t->next = p->next;
		p->next = t;
	}
}

Polinom Polinom::operator+(const Polinom& r)
{
	if (var.size() != r.var.size()) throw "Can't sum with different sizes";
	if (base != r.base) throw "Can't sum with different bases";

	Polinom res(var, base);

	Monom* t1, * t2, * t3;
	t1 = res.head;
	t2 = head->next;
	t3 = r.head->next;

	while ((t2 != head) && (t3 != r.head))
	{
		if (t2->pow == t3->pow)
		{
			if (t2->coef + t3->coef)
			{
				Monom* p = new Monom;

				p->pow = t2->pow;
				p->next = t1->next;
				t1->next = p;

				p->coef = t2->coef + t3->coef;

				t1 = t1->next;
			}
			
			t2 = t2->next;
			t3 = t3->next;
		}
		else if (t2->pow < t3->pow)
		{
			Monom* p = new Monom;

			p->pow = t2->pow;
			p->coef = t2->coef;
			p->next = t1->next;
			t1->next = p;

			t1 = t1->next;
			t2 = t2->next;
		}
		else
		{
			Monom* p = new Monom;

			p->pow = t3->pow;
			p->coef = t3->coef;
			p->next = t1->next;
			t1->next = p;

			t1 = t1->next;
			t3 = t3->next;
		}
	}

	while (t2 != head)
	{
		Monom* p = new Monom;
		p->pow = t2->pow;
		p->coef = t2->coef;
		p->next = t1->next;
		t1->next = p;

		t1 = t1->next;
		t2 = t2->next;
	}

	while (t3 != r.head)
	{
		Monom* p = new Monom;
		p->pow = t3->pow;
		p->coef = t3->coef;
		p->next = t1->next;
		t1->next = p;

		t1 = t1->next;
		t3 = t3->next;
	}

	return res;
}

Polinom Polinom::operator-(const Polinom& r)
{
	if (var.size() != r.var.size()) throw "Can't diff with different sizes";
	if (base != r.base) throw "Can't diff with different bases";

	Polinom res(var, base);

	Monom* t1, * t2, * t3;
	t1 = res.head;
	t2 = head->next;
	t3 = r.head->next;

	while ((t2 != head) && (t3 != r.head))
	{
		if (t2->pow == t3->pow)
		{
			if (t2->coef - t3->coef)
			{
				Monom* p = new Monom;

				p->pow = t2->pow;
				p->next = t1->next;
				t1->next = p;

				p->coef = t2->coef - t3->coef;

				t1 = t1->next;
				t2 = t2->next;
			}

			t3 = t3->next;
		}
		else if (t2->pow < t3->pow)
		{
			Monom* p = new Monom;

			p->pow = t2->pow;
			p->coef = t2->coef;
			p->next = t1->next;
			t1->next = p;

			t1 = t1->next;
			t2 = t2->next;
		}
		else
		{
			Monom* p = new Monom;

			p->pow = t3->pow;
			p->coef = -t3->coef;
			p->next = t1->next;
			t1->next = p;

			t1 = t1->next;
			t3 = t3->next;
		}
	}

	while (t2 != head)
	{
		Monom* p = new Monom;
		p->pow = t2->pow;
		p->coef = t2->coef;
		p->next = t1->next;
		t1->next = p;

		t1 = t1->next;
		t2 = t2->next;
	}

	while (t3 != r.head)
	{
		Monom* p = new Monom;
		p->pow = t3->pow;
		p->coef = -t3->coef;
		p->next = t1->next;
		t1->next = p;

		t1 = t1->next;
		t3 = t3->next;
	}

	return res;
}

Polinom Polinom::operator*(const Polinom& r)
{
	if (var.size() != r.var.size()) throw "Can't mul with different sizes";
	if (base != r.base) throw "Can't mul with different bases";

	Polinom res(var, base);

	Monom* t1, * t2, * t3;
	t1 = res.head;
	t2 = head->next;
	t3 = r.head->next;

	while (t2 != head)
	{
		for (t3 = r.head->next; t3 != r.head; t3 = t3->next)
		{
			if (t2->coef * t3->coef)
			{
				if ((t2->pow + t3->pow) >= pow(base, numOfPows)) throw "Overflow error: power is bigger than base";
				res.sortedAdd(t2->coef * t3->coef, t2->pow + t3->pow);
			}
		}

		t2 = t2->next;
	}

	return res;
}

Polinom Polinom::operator*(double factor)
{
	Polinom res(var, base);

	Monom* t1, * t2;
	t1 = res.head;
	t2 = head->next;

	while (t2 != head)
	{
		res.sortedAdd(t2->coef * factor, t2->pow);

		t2 = t2->next;
	}

	return res;
}

queue<pair<string, ElemType>> Polinom::Parse(string expr)
{
	int state = 0;
	string tmp;

	queue<pair<string, ElemType>> parsed;

	for (string::const_iterator i = expr.cbegin(); i != expr.cend(); i++)
	{
		switch (state)
		{
		case 0:
			if (*i == '-' && (parsed.empty() || parsed.back().second == Operation))
			{
				tmp = *i;
				state = 1;
			}
			else if (operations.find(*i) != string::npos)
			{
				parsed.push({ string(1, *i), Operation });
			}
			else if (*i == ' ')
			{
				break;
			}
			else
			{
				tmp = *i;
				state = 1;
			}
			break;
		case 1:
			if (operations.find(*i) != string::npos)
			{
				if (tmp.length())
				{
					if (!isNumber(tmp))
						parsed.push({ tmp, Variable });
					else
						parsed.push({ tmp, Operand });
					tmp.clear();
				}
				parsed.push({ string(1, *i), Operation });
				state = 0;
			}
			else if (*i == ' ')
			{
				if (tmp.length())
				{
					if (!isNumber(tmp))
						parsed.push({ tmp, Variable });
					else
						parsed.push({ tmp, Operand });
					tmp.clear();
				}
				state = 0;
				//break;
			}
			else
			{
				tmp += *i;
			}
			break;
		}
	}

	if (tmp.size())
	{
		if (!isNumber(tmp))
			parsed.push({ tmp, Variable });
		else
			parsed.push({ tmp, Operand });
	}

	return parsed;
}

bool Polinom::operator==(const Polinom& r) const
{
	if (base != r.base) return 0;
	//if (numOfPows != numOfPows)
	Monom* t1, * t2;
	t1 = head->next;
	t2 = r.head->next;

	while (t1 != head && t2 != r.head)
	{
		if ((t1->coef != t2->coef) || (t1->pow != t2->pow)) return 0;

		t1 = t1->next;
		t2 = t2->next;
	}

	if (t1 != head || t2 != r.head) return 0;

	return 1;
}

bool Polinom::operator!=(const Polinom& r) const
{
	return !(operator==(r));
}

int Polinom::isOperator(string str)
{
	if (operations.find(str) != string::npos)
		return true;
	return false;
}

int Polinom::isNumber(string str)
{
	//if(str[0] == '-') str.erase(str.begin(), str.begin() + 1);
	for (auto i = str.begin(); i < str.end(); i++)
	{
		if (*i == '-') continue;
		if (*i < '0' || *i > '9') return false;
	}
	return true;
}

ostream& operator<<(ostream& ostr, const Polinom& pol)
{
	Monom* p = pol.head->next;

	while (p != pol.head)
	{
		if (p->coef > 0) ostr << "+";
		ostr << p->coef;
		vector<int> pows;
		pows = pol.toBaseSystem(p->pow);
		for (int i = 0; i < pol.numOfPows; i++)
		{
			if (pows[i])
			{
				ostr << "*" << pol.var[i];
				if (pows[i] != 1)
					ostr << "^" << pows[i];
			}
		}
			
		ostr << " ";
		p = p->next;
	}

	return ostr;
}