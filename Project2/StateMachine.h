#pragma once
#include <iostream>
#include <string>

#include "StateMachineTimer.h"
#include "MessagingSystems.h"


class StateMachine {
private:
	enum LifeBeltStateMachine {
		HIBERNATING, WAKING, ALERTING, INFORMING
	};

	enum RemovedStatus {
		REMOVED = 1, ATTACHED = 0
	};

	bool removed_flag = 0;

	bool buzzer = 0;
	bool wake = 0;
	int selectRemoval = 0;	//by default the device is attached
	int nextSelectRemoval = 0;

	//Initial LifeBelt Machine state is HIBERNATING. Update upon state change.
	LifeBeltStateMachine currentState = HIBERNATING;
	RemovedStatus removed = ATTACHED;
	StateMachineTimer t_removed, t_inform;
	// t_removed - time from being removed
	// t_inform - time from the ending of the last infoming state
	MessagingSystems messageSystem;

	void hibernating();
	void waking();
	void alerting();
	void informing();
	void RemoveObjectFromPlatform();

public:
	void StartMachine();
};

