#pragma once
#include "ofMain.h"
#include "ofxGui.h"
#include "AngleTester.h"
#include "OscCommunicator.h"

class Pathfinder
{
public:
	void setup();
	void update();
	void draw(bool guiEnable);
	void drawAngleSimulation();
	void keyPressed(int key);
	ofVec3f curveCalc(int patternID, float theta, float valueA);
	ofVec3f curveCalc(int patternID, float theta, float valueA, float valueB);
	ofVec3f curveCalc(int patternID, float theta, float valueA, float valueB, float valueC);
	ofVec3f curveCalc(int patternID, float theta, float valueA, float valueB, float valueC, float valueD);
	ofVec3f curveCalc(int patternID, float theta, float valueA, float valueB, float valueC, float valueD, float valueE);


	ofxPanel gui, guiB;

	const int numSplit = 10;

	ofParameter<int> mode;
	ofParameter<int> interval;
	ofParameter<float> offset;
	ofParameter<float> values[5];
	ofParameter<float> randomRange;
	ofParameter<ofVec2f> lookingAngle;


	bool initFlag;

	ofVec3f agentPos, agentVel;
	ofVec3f pos;
	int counter = 0;

	bool reachFlag;
	bool firstFlag;
	bool isChanged;

	vector<ofVec3f> targetPos;
	vector<ofVec3f> bufferPos;

	AngleTester tester;

	ofVec3f plateAngle;

	OscCommunicator osc;

};

