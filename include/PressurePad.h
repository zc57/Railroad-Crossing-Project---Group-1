#ifndef PRESSUREPAD_H
#define PRESSUREPAD_H


class PressurePad
{
public:
    void weightDetected();
	void noWeightDetected();
	void flash();

private:
    bool weight;
	int lightNS;
	int lightEW;
	int cwNS;
	int cwEW;
};

#endif // PRESSUREPAD_H
