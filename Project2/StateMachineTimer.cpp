#include "StateMachineTimer.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <ctime>
#include <string>


std::string StateMachineTimer::recordTime() {
	time_t ltime;
	time(&ltime);
	struct tm* gt = ::gmtime(&ltime);
	char* tmp = ::asctime(gt);
	std::string output(tmp);
	return output;
}

void StateMachineTimer::startTimer() {
	if (stop) {
		stop = 0;
		start = std::chrono::high_resolution_clock::now();
	}
}

void StateMachineTimer::stopTimer() {
	stop = 1;
}

float StateMachineTimer::checkTimer() {
	auto now = std::chrono::high_resolution_clock::now();
	if (!stop) {
		duration = now - start;
		float ms = duration.count() * 1000.0f;
		//std::cout << "Timer is " << ms << " ms." << std::endl;
		return ms;
	}
	else {
		//std::cout << "Timer stopped." << std::endl;
		return 0;
	}
}
