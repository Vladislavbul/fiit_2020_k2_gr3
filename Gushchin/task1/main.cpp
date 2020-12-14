#include <iostream>
#include "stack.h"

using namespace std;

struct Node
{
	int val;
	Node* l, * r;

	Node(int _val = 0, Node* _l = NULL, Node* _r = NULL):
		val(_val), l(_l), r(_r) {}
};

void printRec(Node* currTop)
{
	if (currTop == NULL) return;

	//LTR

	printRec(currTop->l);
	cout << currTop->val << " ";
	printRec(currTop->r);
}

void printItr(Node* root)
{
	Stack<Node*> st(100);

	//LTR

	Node* currNode = root;
	
	while (currNode != NULL || !st.isEmpty())
	{
		while (currNode != NULL)
		{
			st.push(currNode);
			currNode = currNode->l;
		}

		currNode = st.front();
		st.pop();
		cout << currNode->val << " ";
		
		currNode = currNode->r;
	}
}

class Itr
{
	Stack<Node*> st;
	Node* currNode;
public:

	Itr(Node* root):
		st(100)
	{
		
		currNode = root;
	}

	bool hasNext()
	{
		return (currNode != NULL || !st.isEmpty());
	}

	int next()
	{
		while (currNode != NULL)
		{
			st.push(currNode);
			currNode = currNode->l;
		}

		currNode = st.front();
		st.pop();
		int val = currNode->val;

		currNode = currNode->r;
		
		return val;
	}
};

int main()
{
	Node* p1 = new Node(4);
	Node* p2 = new Node(7);
	Node* p3 = new Node(8);
	Node* p4 = new Node(6);
	Node* p5 = new Node(5, p2, p3);
	Node* p6 = new Node(2, p1, p5);
	Node* p7 = new Node(3, NULL, p4);
	Node* p8 = new Node(1, p6, p7);

	Node* root = p8;

	printRec(root);
	cout << endl;
	printItr(root);
	cout << endl;
	
	Itr iter(root);

	while (iter.hasNext())
		cout << iter.next() << " ";

	cout << endl;

	return 0;
}