#pragma once
#include <iostream>

using namespace std;

const int MAX = 100;

template <class ValType>
class Stack
{
private:
	ValType* pStack;
	int size;
	int top;
public:
	Stack(int s = 10);
	Stack(const Stack& st);
	~Stack();

	void Push(ValType e);
	ValType Pop();
	ValType Top();
	void Deltop();

	bool IsEmpty()const;
	bool IsFull()const;
};


template <class ValType>
Stack<ValType>::Stack(int s)
{
	if ((s < 1) || (s > MAX))
		throw -1;
	size = s;
	pStack = new ValType[size];
	top = -1;
}

template <class ValType>
Stack<ValType>::Stack(const Stack<ValType>& st)
{
	size = st.size;
	top = st.top;
	pStack = new ValType[size];
	for (int i = 0; i < top; i++)
		pStack[i] = st.pStack[i];
}

template <class ValType>
Stack<ValType>::~Stack()
{
	delete[] pStack;
}

template <class ValType>
bool Stack <ValType>::IsEmpty() const
{
	return (top == -1);
}

template <class ValType>
bool Stack <ValType>::IsFull() const
{
	return (top == size - 1);
}

template <class ValType>
void Stack<ValType>::Push(ValType e)
{
	if (IsFull())
		throw -1;
	top++;
	pStack[top] = e;
}

template <class ValType>
ValType Stack<ValType>::Pop()
{
	if (IsEmpty())
		throw -1;
	return pStack[top--];
}

template <class ValType>
ValType Stack<ValType>::Top()
{
	if (IsEmpty())
		throw -1;
	return pStack[top];
}

template <class ValType>
void Stack<ValType>::Deltop()
{
	if (IsEmpty())
		throw -1;
	top--;
}