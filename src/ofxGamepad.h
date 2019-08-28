#ifndef OFXGAMEPAD_H
#define OFXGAMEPAD_H

#include "ofMain.h"
#include "ofxGamepadConfigs.h"

class ofxGamepad;

class ofxGamepadThreshold{
public:
	ofxGamepadThreshold(){
		min = max = 0.05;
	}
	float min;
	float max;
};

class ofxGamepadEvent
{
public:
	ofxGamepad* gamepad;
};

class ofxGamepadButtonEvent: public ofxGamepadEvent
{
public:
	int button;
	bool value;
};

class ofxGamepadAxisEvent: public ofxGamepadEvent
{
public:
	int axis;
	float value;
	float valueRel;
};

class ofxGamepadPovEvent: public ofxGamepadEvent
{
public:
	int pov;
	int value;
};

class ofxGamepad
{

public:
	ofxGamepad();
	~ofxGamepad();
	virtual void update() {};

	void buttonReleased(int button);
	void buttonPressed(int button);

	bool getButtonValue(int button);
	float getAxisValue(int axis);
	float getAxisValueU(int axis);
	int getPovValue(int pov);

	int getNumAxis();
	int getNumButtons();
	int getNumPovs();

	virtual void rumble(float level=1){};

	ofEvent<ofxGamepadAxisEvent> onAxisChanged;
	ofEvent<ofxGamepadButtonEvent> onButtonPressed;
	ofEvent<ofxGamepadButtonEvent> onButtonReleased;
	ofEvent<ofxGamepadPovEvent> onPovChanged;
	ofEvent<ofxGamepadEvent> onUnplug;

	void draw(int x, int y);
	virtual void exit(){};
	
	void disable();

	void setAxisThreshold(int axis, float thresh);
	void setAxisThreshold(int axis, float min, float max);

	ofPoint drawSize;
	string name;	
	int id;

	GAMEPAD_TYPE type;

protected:
	void axisChanged(int axis, int value);
	void buttonChanged(int button, bool value);
	void povChanged(int pov, int value);
	void setNumAxis(int amount);
	void setNumButtons(int amount);
	void setNumPovs(int amount);
	void setName(string name);

	int axisMinVal;
	int axisMaxVal;
	bool isDisabled;

private:
	static int curID;
	int numAxis;
	int numButtons;
	int numPovs;
	std::vector<bool> buttonValues;
	std::vector<float> axisValues;
	std::vector<int> povValues;
	std::map<int, ofxGamepadThreshold> axisThreshold;
};

#endif // OFXGAMEPAD_H
