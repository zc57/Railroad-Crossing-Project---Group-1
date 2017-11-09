#include <iostream>
#include "PressurePad.h"
#include "TrainDetector.h"
#include "TrainBar.h"
using namespace std;

int main () {
	PressurePad car, light;
	TrainDetector trainIn(true);
	TrainDetector trainOut(false);
	TrainBar tb;
	car.noWeightDetected(); //car is not in intersection
	car.weightDetected(); //car is in intersection, triggers sensor
	light.flash(); //signal was received and light changes accordingly
	trainIn.detect();
	trainIn.setRed();
	trainIn.getLightstatus();
	tb.lowerBar();
	trainOut.detect();
	trainOut.getLightstatus();
	light.flash();
	tb.raiseBar();
	cin.get();
	return 0;
}
