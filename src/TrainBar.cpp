#include <iostream>
#include "TrainBar.h"
using namespace std;

void TrainBar::lowerBar() {
    lowered = true;
    cout << "Bar lowered\n";
}
void TrainBar::raiseBar() {
    lowered = false;
    cout << "Bar raised\n";
}
