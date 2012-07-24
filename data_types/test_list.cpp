#include <iostream>

#include "list.h"

using namespace std;

int main(int argc, const char **argv)
{
	List<int> list;
	list.insert(0);
	list.insert(1);
	list.insert(2);
	list.insert(3);
	
	List<int>::Node *x = list.begin();
	while (x)
	{
		cout << x->data << ", ";
		x = x->next;
	}
	cout << endl;
	
	list.reverse();
	
	x = list.begin();
	while (x)
	{
		cout << x->data << ", ";
		x = x->next;
	}
	cout << endl;
	
	return 0;
}