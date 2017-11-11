#ifndef TRAINBAR_H
#define TRAINBAR_H

class TrainBar
{
private:
	int id;
	bool lowered;
public:
    TrainBar();
    TrainBar(int);
	void lowerBar();
	void raiseBar();
	bool getStatus();
	int getID();
};

#endif // TRAINBAR_H
