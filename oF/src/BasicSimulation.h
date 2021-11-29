#pragma once
#include "ofMain.h"
#include "ofxGui.h"
#include "AngleTester.h"


class BasicSimulation
{
public:
	void setup();
	void drawSimulationViewer(bool automatic);
	ofVec2f angleCalculator();

	AngleTester tester;
	ofxPanel gui;
	ofParameter<float> angleX;
	ofParameter<float> angleZ;

	ofEasyCam cam;
};

