#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <iomanip>
#include <ctime>

#include "timer.h"

using namespace std;

struct Data
{
	int a, b, c;
	float f;
	Data(int v) : a(v), b(v), c(v) { f = (float)(a + b + c); }
};

int main(/*int argc, const char **argv*/)
{
	vector<Data> vec;
	deque<Data> deq;
	
	START_TIMER("vector");
		for (int i = 0; i < 1000000; ++i)
			vec.push_back(i);
	END_TIMER;
	
	START_TIMER("copy to deque");
		deq.resize(vec.size(), Data(0));
		copy(vec.begin(), vec.end(), deq.begin());
	END_TIMER;
	
	cout << endl << "vector --- " << endl;
	START_TIMER("iterator");
		int a, b = 0;
		vector<Data>::iterator it = vec.begin();
		while (it != vec.end())
		{
			a = it->a;
			//it->b = 0;
			b += a;
			++it;
		}
	END_TIMER;
	
	START_TIMER("const_iterator");
		int a, b = 0;
		vector<Data>::const_iterator it = vec.begin();
		while (it != vec.end())
		{
			a = it->a;
			// it->b = 0; cannot!
			b += a;
			++it;
		}
	END_TIMER;
	
	cout << endl << "deque --- " << endl;
	START_TIMER("iterator");
		int a, b = 0;
		deque<Data>::iterator it = deq.begin();
		while (it != deq.end())
		{
			a = it->a;
			//it->b = 0;
			b += a;
			++it;
		}
	END_TIMER;
	
	START_TIMER("const_iterator");
		int a, b = 0;
		deque<Data>::const_iterator it = deq.begin();
		while (it != deq.end())
		{
			a = it->a;
			// it->b = 0; cannot!
			b += a;
			++it;
		}
	END_TIMER;
	
	return 0;
}