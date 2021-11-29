#pragma once
#include "ofMain.h"
#include "ofxGui.h"
class AngleTester
{
public:
	void setup();
	void draw();
	void drawRevised(float a, float b, float l, float anglePlate);
	void drawRevisedv2(float a, float b, float l, float anglePlate);
	float calcAngle(float inputAngle, float ar);
	float calcAngleRevised(float a, float b, float l, float anglePlate);
	float calcAngleRevisedv2(float a, float b, float l, float anglePlate);

	ofxPanel gui;
	ofParameter<float> lengthRatio;
	ofParameter<float> angle;
	ofParameter<float> angleRatio;
};

