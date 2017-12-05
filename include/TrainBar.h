#ifndef TRAINBAR_H
#define TRAINBAR_H

class TrainBar
{
public:
    TrainBar();
    TrainBar(int);
	void lowerBar();
	void raiseBar();
	bool getStatus();
	int getID();

private:
	int id;
	bool lowered;
};

#endif // TRAINBAR_H
