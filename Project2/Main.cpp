/*
T_REMOVED - time from being removed
LW - time from the ending of the last infoming state


*/


#include <iostream>
#include <string>

#include "StateMachineTimer.h"


class StateMachine {
private:
	enum LifeBeltStateMachine {
		HIBERNATING, WAKING, ALERTING, INFORMING
	};

	enum RemovedStatus {
		REMOVED = 1, ATTACHED = 0
	};
	
	bool buzzer = 0;
	bool wake = 0;
	   
	//Initial LifeBelt Machine state is HIBERNATING. Update upon state change.
	LifeBeltStateMachine currentState = HIBERNATING;
	RemovedStatus removed = ATTACHED;
	StateMachineTimer t_removed, t_inform;

	void hibernating() {
		std::cout << "<<<---------- Hibernating state ---------->>>" << std::endl;
		buzzer = 0;
		wake = 0;
		t_removed.stopTimer();
		t_inform.stopTimer();
		t_inform.startTimer();

		std::cout << "Remove object from the platform?" << std::endl;
		int selectRemoval;
		std::cin >> selectRemoval;
		std::cout << selectRemoval << std::endl;

		switch (selectRemoval) {
		case REMOVED:
			currentState = WAKING;
			std::cout << "going to the next state" << std::endl;
			break;
		case ATTACHED:
			currentState = HIBERNATING;
			break;
		default:
			currentState = HIBERNATING;
			break;
		}
	}

	void waking() {
		std::cout << "<<<---------- Wake up state ---------->>>" << std::endl;
		buzzer = 1;
		t_removed.startTimer();
		std::cout << "Buzzer" << buzzer << std::endl;

		//check if the time since entering is greater than 10s
		if (t_removed.checkTimer() > 1000) {
			currentState = ALERTING;
		}
	}

	void alerting() {
		std::cout << "<<<---------- Alerting state ---------->>>" << std::endl;
		// wake up the system
		wake = 1;
		std::cout << " SENDING ALERT MESSAGE " << std::endl;
		std::cout << " SENDING BATTERY MESSAGE " << std::endl;
		if (t_removed.checkTimer() > 1000) {
			currentState = HIBERNATING;
		}
	}

	void informing() {
		std::cout << "<<<---------- Informing state ---------->>>" << std::endl;
		// wake up the system
		wake = 1;
		std::cout << " SENDING ALERT MESSAGE " << std::endl;
		std::cout << " SENDING BATTERY MESSAGE " << std::endl;
		if (t_removed.checkTimer() > 1000) {
			currentState = HIBERNATING;
		}
	}

public:
	void StartMachine() {
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

			std::cin.get();
		}
	}
};

int main() {

	StateMachine stateMachine;
	stateMachine.StartMachine();

	std::cin.get();
	return 0;
}