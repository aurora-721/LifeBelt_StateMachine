#include "StateMachine.h"
#include "MessagingSystems.h"

#include <iostream>


int main() {
	StateMachine stateMachine;
	stateMachine.StartMachine();


	std::cin.get();
	return 0;
}