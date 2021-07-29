#pragma once
#include "StateMachineTimer.h"
#include <string>

class MessagingSystems
{
private:
	StateMachineTimer timer;
	std::string logger = "";
public:
	void InformingAboutAlert();
	void IntroMessage();
	void SendAlertMessage();
	void SendBatteryMessage();
};

