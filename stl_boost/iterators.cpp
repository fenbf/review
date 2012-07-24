#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>

using namespace std;

#define START_TIMER(msg) { Timer __startTimer__(msg);
#define END_TIMER }

class Timer
{
private:
	clock_t mStart;
	string mMsg;
public:
	Timer(const string &msg) : mMsg(msg) { mStart = clock(); }
	~Timer() 
	{
		clock_t timeEnd = clock();
		double elapsed = double(timeEnd-mStart)/CLOCKS_PER_SEC;	
		cout << mMsg  << ", elapsed: " << elapsed << " sec" << endl;	
	}
};

struct Data
{
	int a, b, c;
	Data(int v) : a(v), b(v), c(v) { }
};

int main(/*int argc, const char **argv*/)
{
	vector<Data> vec;
	
	START_TIMER("vector");
		for (int i = 0; i < 10000000; ++i)
			vec.push_back(i);
	END_TIMER;
	
	START_TIMER("iterator");
		int a, b = 0;
		vector<Data>::iterator it = vec.begin();
		while (it != vec.end())
		{
			a = it->a;
			it->b = 0;
			b += a;
			++it;
		}
	END_TIMER;
	
	START_TIMER("iterator");
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
	
	return 0;
}