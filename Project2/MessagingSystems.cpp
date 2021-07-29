#include "MessagingSystems.h"
#include "StateMachineTimer.h"

#include <iostream>

void MessagingSystems::InformingAboutAlert() {
	std::cout << " INFROMING ABOUT THE ALERT STATUS " << std::endl;
	std::cout << logger << std::endl;
}

void MessagingSystems::IntroMessage() {
	std::cout << "At any time you can remove an object from the platform with the press of 1" << std::endl;
	std::cout << "With the press of 0, you can put it back." << std::endl;
	std::cout << "You can't remove an object twice or put it back twice." << std::endl;
}

void MessagingSystems::SendAlertMessage(){
	std::cout << " SENDING ALERT MESSAGE " << std::endl;
	std::string timeVal = timer.recordTime();
	std::cout << timeVal << std::endl;
	logger.append(timeVal);
}

void MessagingSystems::SendBatteryMessage() {
	std::cout << " SENDING BATTERY MESSAGE " << std::endl;
}
