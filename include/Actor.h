#ifndef ACTOR_H
#define ACTOR_H

#include <string>
using std::string;

class Actor {
public:
    string name;
    bool inIntersection;
    bool isActive;
    virtual void update(int) = 0;
    virtual void remove() = 0;
};

#endif // ACTOR_H
