#include <iostream>
#include "Stack.h"
using namespace std;

struct Node 
{
	int val;
	Node * l;
	Node * r;
	Node (int _val= 0.0,
	Node * _l = NULL,
	Node * _r=NULL): 
		val(_val), l(_l), r(_r){}
	
};

void print(Node* curr_t) 
{
	if (curr_t == NULL) return;
	print(curr_t->l);
	cout << curr_t->val << " ";
	print(curr_t->r);
}

void printItr(Node * root)
{
	Stack<Node*> s(50);
	while (true) {
		
		while (root != NULL) 
		{
			s.push(root);
			root = root->l;
		}
	
		if (s.isEmpty()) {
			return;
		}
		root = s.pop();
		cout<< root->val << " ";
		root = root->r;
	}
}

class Itr {
	Stack <Node*> s;
	Node * root;
	int hN;
public:
	Itr(Node* _root) :
		s(50)
	{
		root = _root;
		hN = 1;
	}
	bool hasNext()
	{
		
		return hN;
	}
	int next()
	{
		int tmp = 0;
		while (root != NULL)
		{
			s.push(root);
			root = root->l;
		}

		if (s.isEmpty())  {
			hN = 0;
		}
		else {
			root = s.pop();
		 tmp = root->val;
			root = root->r;
		} 
		return tmp;
	}
};

int main() 
{
	Node * p1 = new Node(4);
	Node * p2 = new Node(6);
	Node * p3 = new Node(3);
	Node * p4 = new Node(5, NULL, p2);
	Node * p5 = new Node(2, p1, p4);
	Node * p6 = new Node(1, p5, p3);
	Node * root = p6;
	print(root);
	cout << "\n";
	printItr(root);
	cout << "\n";
	Itr i(root);
	while (i.hasNext())
	{
		int tmp = i.next();
		if(tmp)
			cout << tmp << " ";
	}
	cout << "\n";
	system("pause");
	return 0;
	
 }