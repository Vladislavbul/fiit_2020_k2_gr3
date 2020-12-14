#pragma once
#include "Node.h"
#include <iostream>

using namespace std;

class BinaryTree
{
private:
	Node* root;
public:
	BinaryTree(Node* root_ = nullptr) : root(root_) {};

	Node* searchMin(Node* root); // ����� ������������ ��������
	Node* searchNext(Node* curr); // ����� ���������� ��������
	static Node* searchNode(Node* root, int key_); // ����� �������� �� �����

	static void insertNode(Node* root, Node* node);
	void removeNode(Node* z);

	Node* getRoot() const;

	static void print(const Node* root);
	friend ostream& operator<<(ostream& out, const BinaryTree& tree);
};