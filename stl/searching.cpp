#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <memory>
#include <vector>
#include <map>
#include <unordered_map>
#include <array>

#include "timer.h"

using namespace std;

int main(const int argc, const char **argv)
{
	srand(time(NULL));
	const int NUM_KEYS = argc > 1 ? atoi(argv[1]) : 1000;
	const int MAX_KEY_LEN = argc > 1 ? atoi(argv[2]) : 100;
	
	//
	// build strng keys
	//
	vector<std::string> stringKeys(NUM_KEYS);
	vector<char> tempKey(MAX_KEY_LEN);
	for (auto &k : stringKeys)
	{
		for (unsigned int i = 0; i < tempKey.size()-1; ++i)
			tempKey[i] = (char)(32+rand()%96);
		tempKey[tempKey.size()-1] = '\0';
		k = string(&tempKey[0]);
	}
	
	/*
	for (auto k : stringKeys)
		cout << k << endl;
	*/
	
	// create a map:
	map<string, int> map;
	START_TIMER("map creation");
		for (auto k : stringKeys)
		{
			map[k] = 0;
		}
	END_TIMER;
	
	// create a map:
	unordered_map<string, int> umap;
	START_TIMER("unordered_map creation");
		for (auto k : stringKeys)
		{
			umap[k] = 0;
		}
	END_TIMER;
	
	START_TIMER("map updates");
		for (auto k : stringKeys)
		{
			map[k]++;
		}
	END_TIMER;
	
	START_TIMER("unordered_map updates");
		for (auto k : stringKeys)
		{
			umap[k]++;
		}
	END_TIMER;
	
	return 0;
}