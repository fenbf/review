#pragma once

// the simple stack class using linked list
template <typename T>
class Stack
{
private:	
	struct Node
	{
		T data;
		Node *next;
		
		Node() { next = NULL; }
		Node(T d, Node *n) { data = d; next = n; }
	};
	
	Node *head;
public:
	Stack();
	~Stack();
	
	void push(T data);
	T pop();
	bool isEmpty() { return head == NULL; }
};

///////////////////////////////////////////////////////////////////////////////
template <typename T> Stack<T>::Stack()
{
	head = NULL;
	
#ifdef DEBUG
	std::cout << "Stack::Stack, constructor" << std::endl;
#endif
}

///////////////////////////////////////////////////////////////////////////////
template <typename T> Stack<T>::~Stack()
{
	while (isEmpty() == false)
		pop();
		
#ifdef DEBUG
	std::cout << "Stack::~Stack, destructor" << std::endl;
#endif
}

///////////////////////////////////////////////////////////////////////////////
template <typename T> void Stack<T>::push(T data)
{
	/*
	if (head == NULl)
	{
		head = new Node(data, NULL);
	}
	else
	{
		Node *t = new Node(data, head);
		head = t;
	}*/
	head = new Node(data, head);
}

///////////////////////////////////////////////////////////////////////////////
template <typename T> T Stack<T>::pop()
{
	if (head == NULL)
		return 0;
	else
	{
		T data = head->data;
		Node *t = head->next;
		delete head;
		head = t;
		return data;
	}
}