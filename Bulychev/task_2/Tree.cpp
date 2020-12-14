#include <iostream>
#include "Stack.h"

using namespace std;

//LTR

struct Top
{
	int val;
	Top* l;
	Top* r;

	Top(int _val = 0.0, Top* _l = NULL, Top* _r = NULL) : val(_val), l(_l), r(_r) {}
};

void Print_r(Top* curr_t)  //rekursia
{
	if (curr_t == NULL) return;

	//LTR

	Print_r(curr_t->l);
	cout << curr_t->val << ' ';
	Print_r(curr_t->r);
}

void Print_Itr(Top* root)
{
	Stack<Top*> st;
	
	while (root != NULL || !st.IsEmpty())
	{
		if (root != NULL)
		{
			st.Push(root);
			root = root->l;
		}
		else
		{
			root = st.Pop();
			cout << root->val << ' ';
			root = root->r;
		}
	}
}

class Itr
{
	Stack<Top*> st;
	Top* a;
public:
	Itr(Top* root)
	{
		a = root;
	}

	bool hasNext()
	{
		return (a != NULL || !st.IsEmpty());
	}

	int next()
	{
		if (a != NULL)
		{
			st.Push(a);
			a = a->l;
			return 0;
		}
		else
		{
			a = st.Pop();
			int value = a->val;
			a = a->r;
			return value;
		}
	}
};

int main()
{
	Top* t1 = new Top(4);
	Top* t2 = new Top(5);
	Top* t3 = new Top(7);
	Top* t4 = new Top(2, t1, NULL);
	Top* t5 = new Top(6, t3, NULL);
	Top* t6 = new Top(3, t2, t5);
	Top* t7 = new Top(1, t4, t6);

	Top* root = t7;

	//cout << "Hi!";

	cout << "Rekursia: ";
	Print_r(root);
	cout << '\n';

	cout << "Iter: ";
	Print_Itr(root);
	cout << '\n';

	cout << "Iterator: ";
	Itr i(root);
	while (i.hasNext())
	{
		int b = i.next();
		if (b != 0)
		{
			cout << b << ' ';
		}
	}
	cout << '\n';

	return 0;
}