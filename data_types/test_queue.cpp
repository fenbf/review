#include <iostream>

#include "queue.h"

using namespace std;

int main(int argc, const char **argv)
{
	Queue<int> q;
	q.enqueue(0);
	q.enqueue(1);
	q.enqueue(2);
	
	while (q.isEmpty() == false)
		cout << q.dequeue() << ", ";
	cout << endl;
	
	return 0;
}