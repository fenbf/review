#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <ctime>

#include "timer.h"

using namespace std;

template <class Iterator>
void printAll(Iterator start, Iterator end)
{
	for (Iterator i = start; i != end; ++i)
	{
		cout << (*i) << ", ";
	}
	cout << endl;
}

template <class Iterator, class Iterator2>
bool compare(Iterator start1, Iterator end1, Iterator2 start2, Iterator2 end2)
{
	Iterator2 j = start2;
	for (Iterator i = start1; i != end1; ++i)
	{
		// second container was too short?
		if (j == end2)
			return false;
		
		if (!((*i) == (*j)))
			return false;
		
		j++;
	}
	return true;
}

template <class Iterator>
void bubbleSort(Iterator start, Iterator end)
{
	for (Iterator i = start; i != end-1; ++i)
	{
		for (Iterator j = end-1; j != i; --j)
		{
			if ((*j) < (*(j-1)))
				swap((*(j-1)), (*j)); 
		}
	}
} 

template <class Iterator>
void selectionSort(Iterator start, Iterator end)
{
	Iterator m;
	for (Iterator i = start; i != end-1; ++i)
	{
		m = i;
		for (Iterator j = i+1; j != end; ++j)
		{
			if ((*j) < (*m)) 
				m = j;
		}
		swap(*m, *i);
	}
}

template <class Iterator>
void insertionSort(Iterator start, Iterator end)
{
	// find min and put it in the beginning
	Iterator m = start;
	for (Iterator i = start+1; i != end; ++i)
	{
		if ((*i) < (*m)) 
			m = i;
	}
	swap(*m, *start);
	
	// insertion
	Iterator j;	
	for (Iterator i = start+2; i != end; ++i)
	{
		typename iterator_traits<Iterator>::value_type temp = (*i);
		j = i;
		while (temp < (*(j-1)))
		{
			*j = *(j-1);
			j--;
		}
		*j = temp;
	}
}

struct Data
{
	int key;
	int value;
	Data(int k, int v) { key = k; value = v; }
	
	friend bool operator < (const Data &x, const Data &y)
	{
		return x.key < y.key;
	}
	
	friend bool operator == (const Data &x, const Data &y)
	{
		return x.key == y.key;
	}
	
	friend ostream & operator<< (ostream &stream, const Data &s) 
	{
		return stream << "(" << s.key << ", " << s.value << ")";
	}
};

int main(int argc, const char **argv)
{
	typedef vector<Data> container;
	const int NUM = argc > 1 ? atoi(argv[1]) : 1000;
	const int MAX_KEY = NUM*2;
	srand(time(NULL));
	
	cout << "NUM ELEMENTS: " << NUM << endl;
	
	container orginal;
	for (int i = 0; i < NUM; ++i)
		orginal.push_back(Data(rand()%MAX_KEY, i));
	
	container stlVec(orginal);	
	START_TIMER("stl sort");
		sort(stlVec.begin(), stlVec.end());
	END_TIMER;
	
	//printAll(stlVec.begin(), stlVec.end());
	
	container tempVec(stlVec);
	START_TIMER("my bubble sort");
		bubbleSort(tempVec.begin(), tempVec.end());
	END_TIMER;
	
	container tempVec2(orginal);
	START_TIMER("my selection sort");
		selectionSort(tempVec2.begin(), tempVec2.end());
	END_TIMER;
	
	container tempVec3(orginal);
	START_TIMER("my insertion sort");
		insertionSort(tempVec3.begin(), tempVec3.end());
	END_TIMER;
	
	//printAll(tempVec3.begin(), tempVec3.end());
	
	cout << "comparing results... " << endl;
	if (compare(stlVec.begin(), stlVec.end(), tempVec.begin(), tempVec.end()) &&
	    compare(stlVec.begin(), stlVec.end(), tempVec2.begin(), tempVec2.end()) &&
		compare(stlVec.begin(), stlVec.end(), tempVec3.begin(), tempVec3.end()))
		cout << "OK!" << endl;
	else
		cout << "Wrong!" << endl;
	
	return 0;
}