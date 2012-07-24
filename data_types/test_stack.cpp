#include <iostream>

#include "stack.h"

using namespace std;

int main(int argc, const char **argv)
{
	Stack<int> stack;
	stack.push(0);
	stack.push(1);
	stack.push(2);
	
	while (stack.isEmpty() == false)
		cout << stack.pop() << ", ";
	cout << endl;
	
	return 0;
}