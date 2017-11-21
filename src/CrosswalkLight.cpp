//
//  CrosswalkLights.cpp
//  cs324_project
//
//  Created by Robert Atkins on 11/14/17.
//  Copyright © 2017 Robert Atkins. All rights reserved.
//

#include <iostream>
using std::cout;
using std::endl;
#include "CrosswalkLight.h"

    // Constructors
CrosswalkLight::CrosswalkLight() : status(false), identifier(0) { }
CrosswalkLight::CrosswalkLight(bool statusArg, int identifierArg)
    : status(statusArg), identifier(identifierArg) { }

    // Identifier mutator and accessor
int CrosswalkLight::getIdentifier() { return identifier; }
void CrosswalkLight::setIdentifier(int newIdentifier) { identifier = newIdentifier; }

    // When the status is changed, output what the new status is.
    // True = Walk, False = Do not walk
void CrosswalkLight::setStatus(bool newStatus) {
    status = newStatus;
    if(newStatus) {
        cout << "* Crosswalk Status changed to: Walk" << endl;
    } else {
        cout << "* Crosswalk Status changed to: Stop" << endl;
    }
}

    // Overloaded = operator sets the crosswalk light's status using the
    // setStatus(newStatus) function so as to also print out light change
void CrosswalkLight::operator=(bool newStatus) { this->setStatus(newStatus); }

bool CrosswalkLight::getStatus() { return status; }
