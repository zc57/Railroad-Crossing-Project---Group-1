#include "PressurePad.h"
#include <iostream>
using namespace std;

	void PressurePad::weightDetected() {
    	weight = true;
    	cout << "Car detected, signal sent" << endl;
	}
	void PressurePad::noWeightDetected() {
    	weight = false;
    	cout << "No car detected" << endl;
	}
	void PressurePad::flash() {
    	weight = true;
    	if (weight = true) {
        	lightNS, cwNS = 1; //green, walk
        	lightEW, cwEW = 0; // red, dont walk
        	cout << "Change light 1 & 2 to green, 3 & 4 to red" << endl;
        	cout << "North/south crosswalks can walk, east/west crosswalks must signal to not walk" << endl;
    	}
    	else {
        	cout << "No light change needed" << endl;
    	}
	}
