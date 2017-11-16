#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#include "PressurePad.h"
#include "TrainDetector.h"
#include "TrainCrossingLights.h"
#include "TrainBar.h"
#include "CrosswalkLight.h"

class Actor {
public:
    string name;
    bool inIntersection;
    bool isActive;
    virtual void update(int) = 0;
    virtual void remove() = 0;
};

class Pedestrian : public Actor {
public:
    CrosswalkLight destinationLight;
    int lengthToClear;

    Pedestrian() {};
    Pedestrian(int len, CrosswalkLight &destLight) {
        name = "Pedestrian";
        isActive = true;
        inIntersection = false;
        lengthToClear = len;
        destinationLight = &destLight;
        hitIntersectionAt = 0;
    }

    void update(int s) {
        if (!isActive) return;
        if (!inIntersection && destinationLight.getStatus()) {
            cout << "* Pedestrian entered intersection" << endl;
            inIntersection = true;
            hitIntersectionAt = s;
        } else if (s == hitIntersectionAt + lengthToClear) {
            cout << "* Pedestrian exited intersection" << endl;
            inIntersection = false;
            remove();
        }
    }

    void remove() {
        isActive = false;
    }

private:
    int hitIntersectionAt;
};

class Train : public Actor {
public:
    int length;
    int enterAfter;
    TrainDetector *detectorIn, *detectorOut;

    Train() {};
    Train(int enterAfterSeconds, int l, TrainDetector &detIn, TrainDetector &detOut) {
        name = "Train";
        isActive = true;
        inIntersection = false;
        length = l;
        enterAfter = enterAfterSeconds;
        detectorIn = &detIn;
        detectorOut = &detOut;
    }

    void update(int s) {
        if (!isActive) return;
        if (s == enterAfter) {
            detectorIn->detect();
        } else if (s == enterAfter + detectorIn->distance) {
            cout << "* Train entered Intersection" << endl;
            inIntersection = true;
            hitIntersectionAt = s;
        } else if (s == hitIntersectionAt + length) {
            detectorOut->detect();
            detectorIn->resetStatus();
            inIntersection = false;
            remove();
        }
    }

    void remove() {
        isActive = false;
    }
private:
    int hitIntersectionAt;
};

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

	LightController lc(crosswalkLights);

	// Train Detectors
	TrainDetector trainIn(true, trainDetectorInDistance, trainBars, lc);
	TrainDetector trainOut(false, trainDetectorOutDistance, trainBars, lc);

    // Train
	Train train = Train(trainEnterAfter, trainLength, trainIn, trainOut);

	// Pedestrians
    vector<Pedestrian*> pedestrians(0);
    pedestrians.push_back(new Pedestrian(4, crossLight1));
    pedestrians.push_back(new Pedestrian(2, crossLight2));

	int s = 0; //Seconds
	bool intersectionActive = true;
    while (intersectionActive) {
        cout << " STEP " << s << endl;
        train.update(s);
        for (Pedestrian *pedest : pedestrians) {
            pedest->update(s);
        }
        cout << "Train Detector (In) : " << trainIn.getLightstatus() << endl;
        cout << "Train Detector (Out): " << trainOut.getLightstatus() << endl;
        for (TrainBar tb : trainBars) {
            cout << "Train Bar " << tb.getID() << ": " << (tb.getStatus() ? "Lowered" : "Raised") << endl;
        }
        for (CrosswalkLight cl : crosswalkLights) {
            cout << "Crosswalk Light " << cl.getIdentifier() << ": " << (cl.getStatus() ? "Walk" : "Stop") << endl;
        }
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
