#ifndef TRAINCROSSINGLIGHTS_H
#define TRAINCROSSINGLIGHTS_H

class TrainCrossingLights{
 private:
    bool trainWeight;
    int timer;
    int light;
 public:
    void trainWeightDetected();
    void notrainWeightDetected();
    void flash();
};


#endif // TRAINCROSSINGLIGHTS_H
