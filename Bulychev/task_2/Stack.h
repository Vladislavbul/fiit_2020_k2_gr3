#pragma once
#include <iostream>

using namespace std;

const int MaxStackSize = 100;

template <class ValType>
class Stack
{
private:
	ValType* pStack; // ��������� �� ����
	int size; // ������
	int top; // ������� �����
public:
	Stack(int s = 10);// �����������
	Stack(const Stack& st); // ����������� �����������
	~Stack(); // ����������
	void Push(ValType e); // ���������� �������� � ����
	ValType Pop(); // ��������� �������� �������� � ��������� �� �����
	bool IsEmpty()const; // �������� �� ������� �����
};

template <class ValType>
Stack<ValType>::Stack(int s) // �����������
{
	if ((s < 1) || (s > MaxStackSize)) // ��������
	{
		throw "error: data is not correct";
	}
	size = s; // ���������������� ������ �����
	pStack = new ValType[size]; // �������� ������
	top = -1; // �������� -1 ������� � ���, ��� ���� ����
}

template <class ValType> // ����������� �����������
Stack<ValType>::Stack(const Stack<ValType>& st)
{
	size = st.size;
	top = st.top;
	pStack = new ValType[size]; // �������� ������ ��� ����� ����
	for (int i = 0; i < top; i++)
	{
		pStack[i] = st.pStack[i];
	}
}

template <class ValType>
Stack<ValType>::~Stack() // ����������
{
	delete[] pStack;
}

template <class ValType>
bool Stack <ValType>::IsEmpty() const // stack ����
{
	return (top == -1);
}

template <class ValType>
void Stack<ValType>::Push(ValType e) // ���������� �������� � ����
{
	top++;
	pStack[top] = e; // �������� ������� � ����
}

template <class ValType>
ValType Stack<ValType>::Pop() // ��������� �������� �������� � ��������� �� �����
{
	if (IsEmpty())
	{
		throw "error: stack is empty";
	}
	return pStack[top--];
}