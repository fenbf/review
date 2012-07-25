#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <iomanip>
#include <ctime>
#include <memory>
#include "boost/smart_ptr/shared_ptr.hpp"

#include "timer.h"

using namespace std;



int main(/*int argc, const char **argv*/)
{
	boost::shared_ptr<int> p(new int(42));
	cout << *p << endl;
	
	std::unique_ptr<int> p2(new int(32));
	cout << *p2 << endl;
	
	return 0;
}