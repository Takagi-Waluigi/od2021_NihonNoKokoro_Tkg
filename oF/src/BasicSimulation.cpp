#include "BasicSimulation.h"

void BasicSimulation::setup()
{
	tester.setup();

	gui.setup();

	angleX.set("angleX", 0, -30, 30);
	angleZ.set("angleZ", 0, -30, 30);

	gui.add(angleX);
	gui.add(angleZ);

}

void BasicSimulation::drawSimulationViewer(bool automatic)
{
	cam.begin();

	int fieldSize = 500;

	if (automatic)
	{
		auto outputAngle = angleCalculator();
		angleX = outputAngle.x;
		angleZ = outputAngle.y;
	}

	ofPushMatrix();
	ofSetColor(128);

	ofRotateXDeg(90);
	ofDrawRectangle(-fieldSize * 0.5, -fieldSize * 0.5, 50, fieldSize, fieldSize);

	ofPopMatrix();

	ofPushMatrix();
	ofSetColor(255);

	ofRotateXDeg(90 + angleX);
	ofRotateYDeg(angleZ);

	ofDrawRectangle(-fieldSize * 0.5, -fieldSize * 0.5, fieldSize, fieldSize);

	ofPopMatrix();

	ofDrawBox(-fieldSize * 0.5, -20, 0, 20, 40, 20);
	ofDrawBox(0, -20, fieldSize * 0.5, 20, 40, 20);
	ofDrawBox(0, -20, 0, 20, 40, 20);

	cam.end();

	ofDrawBitmapString("servo angle X: " + ofToString(tester.calcAngle(angleX, 3.0)), ofGetWidth() * 0.5, 30);
	ofDrawBitmapString("servo angle Z: " + ofToString(tester.calcAngle(angleZ, 3.0)), ofGetWidth() * 0.5, 45);
	gui.draw();

}

ofVec2f BasicSimulation::angleCalculator()
{
	ofVec2f angle;

	angle.x = 20 * cos(ofGetElapsedTimef());
	angle.y = 20 * sin(ofGetElapsedTimef());

	return angle;
}