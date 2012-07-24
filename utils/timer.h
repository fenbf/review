#pragma once

#define START_TIMER(msg) { Timer __startTimer__(msg);
#define END_TIMER }

class Timer
{
private:
	clock_t mStart;
	std::string mMsg;
public:
	Timer(const std::string &msg) : mMsg(msg) { mStart = clock(); }
	~Timer() 
	{
		clock_t timeEnd = clock();
		double elapsed = double(timeEnd-mStart)/CLOCKS_PER_SEC;	
		std::cout << mMsg  << ", elapsed: " << elapsed << " sec" << std::endl;	
	}
};