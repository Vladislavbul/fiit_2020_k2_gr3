#pragma once
#include "Monom.h"
#include <vector>
#include <string>
#include <queue>
#include <map>

using namespace std;

enum ElemType { Operation, Operand, Variable };

class Polinom
{
	Monom* head;
	int numOfPows;
	int base;
	vector<string> var;

	const string operations = { '+', '-', '*', '^', '(', ')', '=' };
public:
	vector<int> toBaseSystem(int pow) const;
	int toDecimalSystem(const vector<int> v) const;
	int isOperator(string str);
	int isNumber(string str);
	queue<pair<string, ElemType>> Parse(string expr);



	Polinom(vector<string> _var, int _base = 20):
		base(_base)
	{
		if (_base < 2) throw "Base should be higher than 2";
		head = new Monom;
		head->next = head;
		var = _var;
		numOfPows = var.size();
	}

	Polinom(string str, vector<string> var, int _base = 20);

	Polinom(const Polinom& r);

	void sortedAdd(int coef, int pows);

	Polinom operator+(const Polinom& r);
	Polinom operator-(const Polinom& r);
	Polinom operator*(const Polinom& r);
	bool operator==(const Polinom& r) const;
	bool operator!=(const Polinom& r) const;

	Polinom operator*(double factor);

	friend ostream& operator<<(ostream& ostr, const Polinom& pol);
};

