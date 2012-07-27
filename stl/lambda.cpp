#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <deque>
#include <iomanip>
#include <ctime>
#include <memory>
#include <algorithm>

using namespace std;


int main(/*int argc, const char **argv*/)
{
	vector<int> vec(10);
	for (int &i : vec)
	{
		i = rand()%100;
	}
	sort(vec.begin(), vec.end(), [](const int& a, const int& b) -> bool
	{
		return a > b;
	});
	
	for (int i : vec)
		cout << i << ", ";
	cout << endl;
	
	return 0;
}