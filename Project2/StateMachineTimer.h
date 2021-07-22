#pragma once

#include <chrono>
#include <thread>
#include <iostream>

class StateMachineTimer
{
private:
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<float> duration;
	bool stop = 1;

public:
	void startTimer();
	void stopTimer();
	float checkTimer();
};

