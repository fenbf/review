#pragma once

template <typename T>
class List
{
public:
	struct Node
	{
		T data;
		Node *next;
		
		Node() { next = NULL; }
		Node(T data, Node *next) { this->data = data; this->next = next; }
	};
	
private:	
	Node *head;
	
public:
	List();
	~List();
	
	// inserts after the head int the beginning
	void insert(T data)
	{
		Node *n = new Node(data, head->next);
		head->next = n;
	}
	
	// reverses the list
	void reverse()
	{
		Node *t;
		Node *x = head->next;
		Node *r = NULL;
		while (x)
		{
			// save what is next
			t = x->next;
			// set the previous node
			x->next = r;
			// remember the previous node
			r = x;
			// go to next node
			x = t;
		}
		// set the head again
		head->next = r;
	}
	
	Node *begin() 
	{
		return head->next;
	}
};

///////////////////////////////////////////////////////////////////////////////
template <typename T> List<T>::List()
{
	head = new Node();

#ifdef DEBUG
	std::cout << "List::List, constructor" << std::endl;
#endif
}

///////////////////////////////////////////////////////////////////////////////
template <typename T> List<T>::~List()
{
	Node *x = head;
	Node *t;
	while (x)
	{
		t = x;
		x = x->next;
		delete t;
	}

#ifdef DEBUG
	std::cout << "List::~List, destructor" << std::endl;
#endif
}