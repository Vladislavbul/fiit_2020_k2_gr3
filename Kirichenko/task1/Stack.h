#pragma once
#include <string>

const int MAX_SIZE = 1000;

template <class T>
class Stack
{
	T* stc;
	int Size;
	int Index;
public:
	Stack(int _size);
	Stack(const Stack& st);
	~Stack();
	void push(T elem);
	bool isFull();
	bool isEmpty();
	T pop();
	void obr(Stack& st);
};

template <class T>
Stack<T>::Stack(int _size) : Size(_size)
{
	Index = -1;
	stc = new T[Size];
}

template <class T>
Stack<T>::Stack(const Stack& st)
{
	Size = st.Size;
	Index = st.Index;
	stc = new T[Size];
	for (int i = 0; i < Size; i++)
		stc[i] = st.stc[i];
}

template <class T>
Stack<T>::~Stack()
{
	delete[] stc;
}
template <class T>
bool Stack<T>::isFull()
{
	return(Index == Size - 1);
}

template <class T>
bool Stack<T>::isEmpty()
{
	return(Index == -1);
}
template <class T>
void Stack<T>::push(T elem)
{
	if (isFull()) throw (" Stack Full");
	Index++;
	stc[Index] = elem;
}
template <class T>
T Stack<T>::pop()
{
	if (isEmpty()) throw "Empty";
	return stc[Index--];
}

template <class T>
void Stack<T>::obr(Stack& st)
{
	Stack tmp(st);
	while (!st.isEmpty())
		st.pop();
	while (!tmp.isEmpty())
		st.push(tmp.pop());
}