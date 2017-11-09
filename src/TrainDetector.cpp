#include <iostream>
#include "TrainDetector.h"
using namespace std;

	TrainDetector::TrainDetector(bool incoming) {
    	this->incoming = incoming;
	}
	bool TrainDetector::isIncoming() {
    	return incoming;
	}
	void TrainDetector::detect() {
    	status = incoming;
    	cout << "Status switched to: " << status << endl; //
	}
	bool TrainDetector::getStatus() { // Controller Object
    	return status;
	}
	void TrainDetector::setRed() {
    	incoming = true;
    	if (incoming = true) {
        	light = 0;
        	cout << "TRAIN DETECTED!! Set all lights to red, including crosswalks" << endl;
        	cout << "Lights should be set to: " << light << endl;
    	}
    	else {
        	light = 1;
    	}
	}
	int TrainDetector::getLightstatus() {
    	return light;
	}
