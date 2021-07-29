#include <iostream>
#include <string>
#include <thread>

#include "StateMachine.h"
#include "StateMachineTimer.h"
#include "MessagingSystems.h"

void StateMachine::hibernating() {
	removed_flag = 0;
	std::cout << "<<<---------- Hibernating state ---------->>>" << std::endl;
	buzzer = 0;
	wake = 0;
	t_removed.stopTimer();
	t_inform.stopTimer();
	t_inform.startTimer();
	while (!removed_flag) {
		if (t_inform.checkTimer() > 10000) {
			currentState = INFORMING;
			break;
		}
	}
}

void StateMachine::waking() {
	removed_flag = 0;
	std::cout << "<<<---------- Wake up state ---------->>>" << std::endl;
	buzzer = 1;
	t_removed.startTimer();
	std::cout << "Buzzer" << buzzer << std::endl;

	//check if the time since entering is greater than 10s
	while (!removed_flag) {
		if (t_removed.checkTimer() > 1000) {
			currentState = ALERTING;
			break;
		}
	}

}

void StateMachine::alerting() {
	removed_flag = 0;
	std::cout << "<<<---------- Alerting state ---------->>>" << std::endl;
	// wake up the system
	wake = 1;
	messageSystem.SendAlertMessage();
	messageSystem.SendBatteryMessage();
	while (!removed_flag) {
		if (t_removed.checkTimer() > 10000) {
			currentState = HIBERNATING;
			break;
		}
	}
}

void StateMachine::informing() {
	removed_flag = 0;
	std::cout << "<<<---------- Informing state ---------->>>" << std::endl;
	// wake up the system
	wake = 1;

	messageSystem.SendBatteryMessage();
	messageSystem.InformingAboutAlert();
	while (!removed_flag) {
		if (t_inform.checkTimer() > 12000) {
			currentState = HIBERNATING;
			break;
		}
	}
}


void StateMachine::RemoveObjectFromPlatform() {
	while (true) {
		while (!removed_flag) {
			std::cin >> nextSelectRemoval;
			//case input from user is not an integer
			while (std::cin.fail()) {
				std::cout << "Error, write an integer" << std::endl;
				std::cin.clear();
				std::cin.ignore(256, '\n');
				std::cin >> nextSelectRemoval;
			}
			if (nextSelectRemoval != selectRemoval) {
				switch (nextSelectRemoval) {
				case REMOVED:
					selectRemoval = nextSelectRemoval;
					currentState = WAKING;
					std::cout << "You removed the Life Belt" << std::endl;
					removed_flag = 1;
					break;
				case ATTACHED:
					selectRemoval = nextSelectRemoval;
					currentState = HIBERNATING;
					std::cout << "You attached the Life Belt" << std::endl;
					removed_flag = 1;
					break;
				default:
					std::cout << "You can only attach or remove the Life Belt - write only numbers between 0 and 1" << std::endl;
					break;
				}
			}
			else {
				switch (nextSelectRemoval) {
				case REMOVED:
					std::cout << "You have to attach the LifeBelt back to it's position before you decide to remove it again." << std::endl;
					std::cout << "Press 0 to attach the LifeBelt." << std::endl;
					break;
				case ATTACHED:
					std::cout << "You have to remove the LifeBelt from it's position before you can attach it again." << std::endl;
					std::cout << "Press 1 to remove the LifeBelt." << std::endl;
					break;
				default:
					std::cout << "You can only attach or remove the Life Belt - write only numbers between 0 and 1" << std::endl;
					break;
				}
			}
		}
	}
}

void StateMachine::StartMachine() {
	messageSystem.IntroMessage();
	std::thread checkIfObjectRemoved = std::thread(&StateMachine::RemoveObjectFromPlatform, this);

	for (int i = 0; i < 15; i++) {
		//state diagram
		switch (currentState) {
		case HIBERNATING:
			hibernating();
			break;
		case WAKING:
			waking();
			break;
		case ALERTING:
			alerting();
			break;
		case INFORMING:
			informing();
			break;
		default:
			std::cout << "Error! Invalid State Detected." << std::endl;
			break;
		}
	}

	checkIfObjectRemoved.join();
	std::cin.get();

}
