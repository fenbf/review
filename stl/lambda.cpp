#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <deque>
#include <iomanip>
#include <ctime>
#include <memory>
#include <iterator>
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
	
	//for (int i : vec)
	//		cout << i << ", ";
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, ", "));
	cout << endl;
	
	return 0;
}