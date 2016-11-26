#pragma once
#include "SFMLText.h"
#include <chrono>

class TimeLeft : public SFMLText{

public:
	TimeLeft(int remainingTime);
	std::chrono::high_resolution_clock::time_point start_time;
	int& get_remTime(){return remTime;};
	void decreaseTime();

private:
	int remTime;

};
