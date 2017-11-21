#ifndef TRAIN_H
#define TRAIN_H

#include "Actor.h"
#include "TrainDetector.h"

class Train : public Actor {
public:
    int length;
    int enterAfter;
    TrainDetector *detectorIn, *detectorOut;

    Train() {};
    Train(int enterAfterSeconds, int l, TrainDetector &detIn, TrainDetector &detOut);
    void update(int s);
    void remove();
private:
    int hitIntersectionAt;
};

#endif // TRAIN_H
