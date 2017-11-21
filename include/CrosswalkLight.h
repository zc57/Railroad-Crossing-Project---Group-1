//
//  CrosswalkLights.h
//  cs324_project
//
//  Created by Robert Atkins on 11/14/17.
//  Copyright © 2017 Robert Atkins. All rights reserved.
//

#ifndef CrosswalkLights_h
#define CrosswalkLights_h

class CrosswalkLight {
public:
    CrosswalkLight();
    CrosswalkLight(bool statusArg, int identifierArg);

    int getIdentifier();
    void setIdentifier(int newIdentifier);

    void setStatus(bool newStatus);
    void operator =(bool newStatus);

    bool getStatus();

private:
    int identifier;
    bool status; // True = walk; False = Do not walk

};

#endif /* CrosswalkLights_h */
