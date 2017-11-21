#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#include "PressurePad.h"
#include "TrainDetector.h"
#include "TrainCrossingLights.h"
#include "TrafficLight.h"
#include "TrainBar.h"
#include "CrosswalkLight.h"
#include "Actor.h"
#include "Pedestrian.h"
#include "Train.h"
#include "Car.h"

int main () {
    int trainEnterAfter = 0;
    int trainLength = 0;
    int trainDetectorInDistance = 0;
    int trainDetectorOutDistance = 0;

    ifstream inFile;
    inFile.open("config.txt");
    if (!inFile) {
        cerr << "No file found";
        exit(1);
    }
    string line;
    while (inFile >> line) {
        string key = line.substr(0,line.find('='));
        string value = line.substr(line.find('=')+1,line.length());
        if (key == "trainEnterAfter")
            trainEnterAfter = stoi(value);
        if (key == "trainLength")
            trainLength = stoi(value);
        if (key == "trainDetectorOutDistance")
            trainDetectorOutDistance = stoi(value);
        if (key == "trainDetectorInDistance")
            trainDetectorInDistance = stoi(value);
    }
    inFile.close();

    // Train Bars
    vector<TrainBar> trainBars(0);
    TrainBar tb1(1), tb2(2), tb3(3), tb4(4), tb5(5), tb6(6);
	trainBars.push_back(tb1);
	trainBars.push_back(tb2);
	trainBars.push_back(tb3);
	trainBars.push_back(tb4);
	trainBars.push_back(tb5);
	trainBars.push_back(tb6);

// Lights
	// Crosswalk Lights
	vector<CrosswalkLight> crosswalkLights(0);
	CrosswalkLight crossLight1 = CrosswalkLight(true, 1);
	CrosswalkLight crossLight2 = CrosswalkLight(true, 2);
	CrosswalkLight crossLight3 = CrosswalkLight(true, 3);
	CrosswalkLight crossLight4 = CrosswalkLight(true, 4);
	CrosswalkLight crossLight5 = CrosswalkLight(true, 5);
	CrosswalkLight crossLight6 = CrosswalkLight(true, 6);
	CrosswalkLight crossLight7 = CrosswalkLight(true, 7);
	CrosswalkLight crossLight8 = CrosswalkLight(true, 8);
	crosswalkLights.push_back(crossLight1);
	crosswalkLights.push_back(crossLight2);
	crosswalkLights.push_back(crossLight3);
	crosswalkLights.push_back(crossLight4);
	crosswalkLights.push_back(crossLight5);
	crosswalkLights.push_back(crossLight6);
	crosswalkLights.push_back(crossLight7);
	crosswalkLights.push_back(crossLight8);

    // Train Crossing Lights
	vector<TrainCrossingLights> trainLights(0);
	TrainCrossingLights tcl;
	trainLights.push_back(tcl);

	// Traffic Lights
	vector<TrafficLight> trafficLights(0);
	TrafficLight tfn = TrafficLight("N");
	TrafficLight tfs = TrafficLight("S");
	TrafficLight tfe = TrafficLight("E");
	TrafficLight tfw = TrafficLight("W");
	trafficLights.push_back(tfn);
	trafficLights.push_back(tfs);
	trafficLights.push_back(tfe);
	trafficLights.push_back(tfw);

    // Light Controller
	LightController lc(crosswalkLights, trainLights);


// Detectors
	// Train Detectors
	TrainDetector trainIn(true, trainDetectorInDistance, trainBars, lc);
	TrainDetector trainOut(false, trainDetectorOutDistance, trainBars, lc);

// Actors
    // Train
	Train train = Train(trainEnterAfter, trainLength, trainIn, trainOut);

	// Pedestrians
    vector<Pedestrian*> pedestrians(0);
    pedestrians.push_back(new Pedestrian(4, crossLight1));
    pedestrians.push_back(new Pedestrian(2, crossLight2));

    // Cars
    vector<Car*> cars(0);
    //cars.push_back(new Car());

	int s = 0; //Steps/Seconds
	bool intersectionActive = true;
    while (intersectionActive) {
        cout << " STEP " << s << " (seconds)" << endl;
        train.update(s);
        for (Pedestrian *pedest : pedestrians) {
            pedest->update(s);
        }
        cout << "Train Detector (In) : " << trainIn.getLightstatus() << endl;
        cout << "Train Detector (Out): " << trainOut.getLightstatus() << endl;
        cout << "Train Bars: ";
        for (TrainBar tb : trainBars) {
            cout << tb.getID() << "[" << (tb.getStatus() ? "-" : "/") << "] ";
            //cout << "Train Bar " << tb.getID() << ": " << (tb.getStatus() ? "Lowered" : "Raised") << endl;
        }
        cout << endl;
        cout << "Crosswalk Lights: ";
        for (CrosswalkLight cl : crosswalkLights) {
            cout << cl.getIdentifier() << " " << (cl.getStatus() ? "W" : "X") << " | ";
            //cout << "Crosswalk Light " << cl.getIdentifier() << ": " << (cl.getStatus() ? "Walk" : "Stop") << endl;
        }
        cout << endl;
        for (TrainCrossingLights tcl : trainLights) {
            cout << "Train Crossing Light: " << (tcl.getStatus() ? "Flashing" : "Off") << endl;
        }
        cout << "Traffic Lights: ";
        for (TrafficLight tl : trafficLights) {
            cout << "[" << tl.getID() << ": " << tl.getStatusString() << "] ";
        }
        cout << endl;
        intersectionActive = false;
        cout << "- In Intersection: " << endl;
        try {
            int numTrainsInIntersection = 0;
            if (train.isActive) {
                if (train.inIntersection) {
                    cout << "| Train" << endl;
                    numTrainsInIntersection++;
                }
                intersectionActive = true;
            }

            int numPedestInIntersection = 0;
            for (Pedestrian *pedest : pedestrians) {
                if (pedest->isActive && pedest->inIntersection) {
                    cout << "| Pedestrian" << endl;
                    numPedestInIntersection++;
                    intersectionActive = true;
                }
            }

            if (numTrainsInIntersection > 0 && numPedestInIntersection > 0) {
                throw("Train collided with Pedestrian");
            }

            cout << endl;
        } catch (const char* msg) {
            cerr << msg << endl;
            intersectionActive = false;
        }

        s += 1;
        cout << "Press (Enter) to proceed)";
        cin.get();
    }
	return 0;
}
