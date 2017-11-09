#ifndef TRAINDETECTOR_H
#define TRAINDETECTOR_H


class TrainDetector
{
public:
    TrainDetector(bool incoming);
	bool isIncoming();
	void detect();
	bool getStatus();
	void setRed();
	int getLightstatus();

private:
	bool incoming;
	bool status; //Move to a Controller object
	int light;
};

#endif // TRAINDETECTOR_H
