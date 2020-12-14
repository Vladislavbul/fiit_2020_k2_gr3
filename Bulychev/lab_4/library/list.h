#include <iostream>

template <class T>
struct Node
{
	T data;
	Node<T>* next = 0;
	Node(T d) : data(d) {};
};

template <class T>
class List
{
	Node<T>* head = 0;

public:
	List();
	List(const List& l);
	Node<T>* getheadptr() { return head; };
	T getHead() { return head->data; };
	bool isEmpty() { if (head == 0) return true; return false; };
	Node<T>* getTail();
	int getSize();
	int getIndex(Node<T> N);
	void pushBack(T data);
	T pop();
	void insert(int index, T data);
	void remove(int index);
	void printAll();
	List<T>& operator=(const List<T>& list);

	~List();
};

template <class T>
List<T>::List()
{
}

template <class T>
List<T>::List(const List<T> & l)
{
	if (l.head == 0)
	{
		head = 0;
		return;
	}
	Node<T>* temp = l.head;
	while (temp->next)
	{
		pushBack(temp->data);
		temp = temp->next;
	}
	pushBack(temp->data);
}

template <class T>
int List<T>::getSize()
{
	int size = 0;
	if (head == 0)
	{
		return size;
	}
	Node<T>* temp = head;
	while (temp)
	{
		size++;
		temp = temp->next;
	}
	return size;
}

template<class T>
int List<T>::getIndex(Node<T> N)
{
	int index = 0;
	if (head == 0)
	{
		return index;
	}
	Node<T>* temp = head;
	while (!(temp->data == N.data))
	{
		index++;
		temp = temp->next;
	}
	return index;
}

template <class T>
Node<T> * List<T>::getTail()
{
	if (head == 0)
	{
		return 0;
	}
	Node<T>* temp = head;
	while (temp->next)
	{
		temp = temp->next;
	}
	return temp;
}

template <class T>
void List<T>::pushBack(T data)
{
	Node<T>* temp = getTail();
	if (temp == 0)
	{
		head = new Node<T>(data);
		return;
	}
	temp->next = new Node<T>(data);
}

template<class T>
T List<T>::pop()
{
	Node<T>* temp = head;
	head = temp->next;
	return temp->data;
}

template <class T>
void List<T>::insert(int index, T data)
{
	if (index > getSize() || index < 0)
	{
		throw - 1;
	}
	Node<T>* temp = head;
	Node<T>* tmp;
	if (index == 0)
	{
		head = new Node<T>(data);
		head->next = temp;
	}
	else
	{
		for (int i = 0; i < index - 1; i++)
			temp = temp->next;
		tmp = temp->next;
		temp->next = new Node<T>(data);
		temp->next->next = tmp;
	}
}

template <class T>
void List<T>::remove(int index)
{
	if (index >= getSize() || index < 0)
	{
		throw - 1;
	}
	Node<T>* temp = head;
	Node<T>* tmp;
	if (index == 0)
	{
		head = head->next;
		return;
	}
	for (int i = 0; i < index - 1; i++)
		temp = temp->next;
	tmp = temp->next->next;
	temp->next = tmp;
}

template <class T>
void List<T>::printAll()
{
	if (head == 0)
	{
		throw - 1;
	}
	Node<T>* temp = head;
	while (temp->next)
	{
		std::cout << temp->data << std::endl;
		temp = temp->next;
	}
	std::cout << temp->data << std::endl;
	std::cout << std::endl;
}

template<class T>
List<T>& List<T>::operator=(const List<T>& list)
{
	if (this == &list)
	{
		return *this;
	}
	Node<T>* temp = list.head;
	while (!this->isEmpty())
	{
		this->pop();
	}
	if (list.head == 0)
	{
		return *this;
	}
	while (temp->next)
	{
		this->pushBack(temp->data);
		temp = temp->next;
	}
	this->pushBack(temp->data);
	return *this;
}

template <class T>
List<T>::~List()
{
	if (head == 0)
	{
		return;
	}

	Node<T>* temp = 0;

	while (head->next)
	{
		temp = head;
		head = head->next;
		delete temp;
	}
	delete head;
}