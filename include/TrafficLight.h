#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <string>
using std::string;

class TrafficLight
{
public:
    TrafficLight();
    TrafficLight(string);
    void setLight(int);
    int getStatus();
    string getStatusString();
    string getID();

private:
    int light;
    string id;
};

#endif // TRAFFICLIGHT_H
