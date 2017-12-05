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
    int secBetweenLights = 4;

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
        if (key == "secBetweenLights")
            secBetweenLights = stoi(value);
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
	CrosswalkLight crossLight1 = CrosswalkLight(false, 1);
	CrosswalkLight crossLight2 = CrosswalkLight(false, 2);
	CrosswalkLight crossLight3 = CrosswalkLight(false, 3);
	CrosswalkLight crossLight4 = CrosswalkLight(false, 4);
	CrosswalkLight crossLight5 = CrosswalkLight(false, 5);
	CrosswalkLight crossLight6 = CrosswalkLight(false, 6);
	CrosswalkLight crossLight7 = CrosswalkLight(false, 7);
	CrosswalkLight crossLight8 = CrosswalkLight(false, 8);
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
	LightController lc(crosswalkLights, trainLights, trafficLights, secBetweenLights);


// Detectors
	// Train Detectors
	TrainDetector trainIn(true, trainDetectorInDistance, trainBars, lc);
	TrainDetector trainOut(false, trainDetectorOutDistance, trainBars, lc);

// Actors
    // Train
	Train train = Train(trainEnterAfter, trainLength, trainIn, trainOut);

	// Pedestrians
    vector<Pedestrian*> pedestrians(0);
    pedestrians.push_back(new Pedestrian(4, &crosswalkLights.at(0)));
    pedestrians.push_back(new Pedestrian(2, &crosswalkLights.at(1)));

    // Cars
    vector<Car*> cars(0);
    cars.push_back(new Car(2, &trafficLights.at(0)));
    cars.push_back(new Car(2, &trafficLights.at(1)));
    cars.push_back(new Car(2, &trafficLights.at(2)));

	int s = 0; //Steps/Seconds
	bool intersectionActive = true;
    while (intersectionActive) {
        cout << " STEP " << s << " (seconds)" << endl;
        lc.update(s);
        train.update(s);
        for (Pedestrian *pedest : pedestrians) {
            pedest->update(s);
        }
        for (Car *car : cars) {
            car->update(s);
        }
        cout << "Train Detector (In) : " << trainIn.getLightstatus() << endl;
        cout << "Train Detector (Out): " << trainOut.getLightstatus() << endl;
        cout << "Train Bars: ";
        for (TrainBar tb : trainBars) {
            cout << tb.getID() << "[" << (tb.getStatus() ? "-" : "/") << "] ";
        }
        cout << endl;
        cout << "Crosswalk Lights: ";
        for (CrosswalkLight cl : crosswalkLights) {
            cout << cl.getIdentifier() << " " << (cl.getStatus() ? "W" : "X") << " | ";
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

            int numCarsInIntersection = 0;
            for (Car *car : cars) {
                if (car->isActive && car->inIntersection) {
                    cout << "| Car" << endl;
                    numCarsInIntersection++;
                    intersectionActive = true;
                }
                if (car->isActive) {
                    intersectionActive = true;
                }
            }

            if (numTrainsInIntersection > 0 && numPedestInIntersection > 0) {
                throw("Train collided with Pedestrian");
            }
            if (numCarsInIntersection > 0 && numPedestInIntersection > 0) {
                throw("Car collided with Pedestrian");
            }
            if (numCarsInIntersection > 0 && numTrainsInIntersection > 0) {
                throw("Train collided with Car");
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
