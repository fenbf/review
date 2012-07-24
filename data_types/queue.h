#pragma once

// the simple queue class using linked list
template <typename T>
class Queue
{
private:	
	struct Node
	{
		T data;
		Node *next;
		
		Node() { next = NULL; }
		Node(T d, Node *n) { data = d; next = n; }
	};
	
	// take from head
	Node *head;
	// put at tail
	Node *tail;
public:
	Queue();
	~Queue();
	
	void enqueue(T data);
	T dequeue();
	bool isEmpty() { return head == NULL; }
};

///////////////////////////////////////////////////////////////////////////////
template <typename T> Queue<T>::Queue()
{
	head = NULL;
	tail = NULL;
	
#ifdef DEBUG
	std::cout << "Queue::Queue, constructor" << std::endl;
#endif
}

///////////////////////////////////////////////////////////////////////////////
template <typename T> Queue<T>::~Queue()
{
	while (isEmpty() == false)
		dequeue();
		
#ifdef DEBUG
	std::cout << "Queue::~Queue, destructor" << std::endl;
#endif
}

///////////////////////////////////////////////////////////////////////////////
template <typename T> void Queue<T>::enqueue(T data)
{
	if (head == NULL)
	{
		head = new Node(data, NULL);
		tail = head;
	}
	else
	{
		Node *t = new Node(data, NULL);
		tail->next = t;
		tail = t;
	}
}

///////////////////////////////////////////////////////////////////////////////
template <typename T> T Queue<T>::dequeue()
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