#include <iostream>
#include "Stack.h"

using namespace std;

struct Node
{
	int val;
	Node* l;
	Node* r;

	Node(int _val=0.0, Node* _l=NULL, Node* _r=NULL):
	  val(_val), l(_l),  r(_r){}
};


void printTLR(Node* curr_t)  // Рекурсия TLR
{
	if (curr_t == NULL) return;
	cout << curr_t->val << "";
	printTLR(curr_t->l);
	printTLR(curr_t->r);
}

void printLTR(Node* curr_t)  // Рекурсия LTR
{
	if (curr_t == NULL) return;
	printLTR(curr_t->l);
	cout << curr_t->val << "";
	printLTR(curr_t->r);
}


void printItrTLR(Node* root) // Итератор TLR
{
	Stack<Node*> st;
	st.Push(root);
	while (!st.IsEmpty())
	{
		Node* curr_t = st.Top();
		st.Pop();
		cout << curr_t->val << "";
		if (curr_t->r != NULL)
			st.Push(curr_t->r);
		if (curr_t->l != NULL)
			st.Push(curr_t->l);
	}
}

void printItrLTR(Node* root) // Итераторационный LTR
{
	Stack<Node*> st;

	while (root != NULL || st.IsEmpty()==0)
	{
		if (root != NULL)
		{
			st.Push(root);
			root = root->l;
		}
		else
		{
			root = st.Pop(); 
			cout << root->val <<"";
			root = root->r;
		}
	}
}

class Itr {
	Stack <Node*> st;
	Node* root;
	int HasNext;
public:
	Itr(Node* _root) : st(100)
	{
		root = _root;
		HasNext = 1;
	}
	bool hasNext()
	{
		return HasNext;
	}
	int next()
	{
		int tmp = 0;
		while (root != NULL)
		{
			st.Push(root);
			root = root->l;
		}
		if (st.IsEmpty())
			HasNext = 0;
		else 
		{
			root = st.Pop();
			tmp = root->val;
			root = root->r;
		}
		return tmp;
	}
};


int main()
{
	setlocale(LC_ALL, "RUS");

	Node* p1 = new Node(4);
	Node* p2 = new Node(6);
	Node* p3 = new Node(3);
	Node* p4 = new Node(5, NULL, p2);
	Node* p5 = new Node(2, p1, p4);
	Node* p6 = new Node(1, p5, p3);

	Node* root = p6;

	
	printTLR(root);                // Рекурсия TLR
	    cout <<" Рекурсия TLR"<<"\n";

	printLTR(root);                // Рекурсия LTR
		cout <<" Рекурсия LTR"<< "\n"; 

		printItrTLR(root);         // Итерационный TLR
		cout << " Итерационный TLR" << "\n";

		printItrLTR(root);         // Итерационный LTR
		cout << " Итерационный LTR" << "\n";

		Itr i(root);               // Итератор LTR
		while (i.hasNext())
		{
			int a = i.next();
			if (a)
				cout << a << "";
		}
		cout <<" Итератор LTR" << "\n";

	return 0;
}