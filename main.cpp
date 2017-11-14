#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#include "PressurePad.h"
#include "TrainDetector.h"
#include "TrainCrossingLights.h"
#include "TrainBar.h"

class Actor {
public:
    string name;
    bool inIntersection;
    bool isActive;

    void update(int) {};
    void remove() {};
};

class Train : Actor {
public:
    int length;
    int enterAfter;
    bool isActive;
    TrainDetector *detectorIn, *detectorOut;

    Train() {};
    Train(int enterAfterSeconds, int l, TrainDetector &detIn, TrainDetector &detOut) {
        isActive = true;
        inIntersection = false;
        length = l;
        enterAfter = enterAfterSeconds;
        detectorIn = &detIn;
        detectorOut = &detOut;
    }
    void update(int s) {
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

    vector<TrainBar> trainBars(0);
    TrainBar tb1(1), tb2(2), tb3(3), tb4(4), tb5(5), tb6(6);
	trainBars.push_back(tb1);
	trainBars.push_back(tb2);
	trainBars.push_back(tb3);
	trainBars.push_back(tb4);
	trainBars.push_back(tb5);
	trainBars.push_back(tb6);

	TrainDetector trainIn(true, trainDetectorInDistance, trainBars);
	TrainDetector trainOut(false, trainDetectorOutDistance, trainBars);

	Train train = Train(trainEnterAfter, trainLength, trainIn, trainOut);

	int s = 0; //Seconds
    while (train.isActive) {
        cout << " STEP " << s << endl;
        train.update(s);
        cout << "Train Detector (In) : " << trainIn.getLightstatus() << endl;
        cout << "Train Detector (Out): " << trainOut.getLightstatus() << endl;
        for (TrainBar tb : trainBars) {
            cout << "Train Bar " << tb.getID() << ": " << (tb.getStatus() ? "Lowered" : "Raised") << endl;
        }
        s += 1;
        cout << "Press (Enter) to proceed)";
        cin.get();
    }
	return 0;
}
