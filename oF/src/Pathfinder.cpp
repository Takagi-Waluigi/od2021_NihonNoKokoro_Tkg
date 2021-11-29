#include "Pathfinder.h"

void Pathfinder::setup()
{
	gui.setup();
	guiB.setup();


	mode.set("mode", 1, 1, 5);
	interval.set("interval", 74, 20, 100);
	offset.set("offset", 1.0, 0.0, 10.0);

	for (int i = 0; i < 5; i++)
	{
		values[i].set("value" + ofToString(i), 200, 0, 500);
	}

	randomRange.set("random range", 2.5, 0.0, 10.0);

	gui.add(mode);
	gui.add(interval);
	gui.add(offset);
	gui.add(randomRange);

	guiB.add(mode);
	guiB.add(interval);
	guiB.add(offset);
	guiB.add(randomRange);

	for (int i = 0; i < 5; i++)
	{
		gui.add(values[i]);
		guiB.add(values[i]);

	}

	firstFlag = true;

	tester.setup();
	osc.setup();

	lookingAngle.set("view angle", ofVec2f(-45, 0), ofVec2f(-360, -360), ofVec2f(360, 360));

	guiB.add(lookingAngle);


}

void Pathfinder::update()
{

	ofVec3f p, _p;

	targetPos.clear();

	switch (mode)
	{

	case 1:
		pos = curveCalc(mode, ofGetElapsedTimef(), values[0]);


		for (float theta = 0.0; theta < TWO_PI; theta += PI / 1000)
		{
			int n = int(theta / (PI / 1000));

			if (n % interval == 0)
			{
				p = curveCalc(mode, theta, values[0]);
				ofSetColor(128);
				ofDrawCircle(p, 7.0);

				targetPos.push_back(p);
			}

		}


		break;

	case 2:
		pos = curveCalc(mode, ofGetElapsedTimef() * 0.01, values[0], values[1], values[2], values[3], values[4]);

		for (float theta = 0.0; theta < TWO_PI; theta += PI / 1000)
		{
			int n = int(theta / (PI / 1000));

			if (n % interval == 0)
			{
				p = curveCalc(mode, theta, values[0], values[1], values[2], values[3], values[4]);
				ofSetColor(128);
				ofDrawCircle(p, 7.0);

				targetPos.push_back(p);
			}

		}
		break;

	case 3:
		pos = curveCalc(mode, ofGetElapsedTimef(), values[0], values[1]);

		for (float theta = 0.0; theta < TWO_PI; theta += PI / 1000)
		{
			int n = int(theta / (PI / 1000));

			if (n % interval == 0)
			{
				p = curveCalc(mode, theta, values[0], values[1]);
				ofSetColor(128);
				ofDrawCircle(p, 7.0);

				targetPos.push_back(p);
			}

		}
		break;


	case 4:
		pos = curveCalc(mode, ofGetElapsedTimef(), values[0]);

		for (float theta = 0.0; theta < TWO_PI; theta += PI / 1000)
		{
			int n = int(theta / (PI / 1000));

			if (n % interval == 0)
			{
				p = curveCalc(mode, theta, values[0]);
				ofSetColor(128);
				ofDrawCircle(p, 7.0);

				targetPos.push_back(p);
			}

		}
		break;

	}

	if (initFlag)
	{
		cout << "init" << endl;
		firstFlag = true;
		counter = 0;
		agentPos = ofVec3f(0, 0, 0);
		bufferPos.clear();
		initFlag = false;
	}

	if (firstFlag)
	{
		agentVel = (targetPos[0] - agentPos).normalize() * 1.0;
		firstFlag = false;
	}

	if (agentPos.distance(targetPos[counter % targetPos.size()]) < 1.5)
	{
		reachFlag = true;
	}

	if (reachFlag)
	{
		counter++;
		reachFlag = false;
	}

	agentVel = (targetPos[counter % targetPos.size()] - agentPos).normalize() * 1.0;

	float nRand = ofRandom(10);

	if (nRand < 2)
	{
		agentVel.x = ofRandom(-randomRange * 0.5, randomRange * 0.5);
		agentVel.y = ofRandom(-randomRange * 0.5, randomRange * 0.5);
	}

	agentPos += agentVel;
	bufferPos.push_back(agentPos);

	if (bufferPos.size() > 100000)
	{
		bufferPos.clear();
	}
}

void Pathfinder::draw(bool guiEnable)
{
	ofPushMatrix();

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	ofSetColor(128);
	ofDrawLine(-ofGetWidth() * 0.5, 0, ofGetWidth() * 0.5, 0);
	ofDrawLine(0, -ofGetHeight() * 0.5, 0, ofGetHeight() * 0.5);


	update();

	ofSetColor(255);


	ofSetColor(128);
	ofDrawCircle(agentPos, 12);
	ofDrawCircle(pos, 5);


	ofSetColor(255);
	if (bufferPos.size() > 1)
	{
		for (int i = 0; i < bufferPos.size() - 2; i++)
		{
			ofDrawLine(bufferPos[i], bufferPos[i + 1]);
		}
	}

	ofSetColor(255, 0, 0);
	ofDrawCircle(targetPos[counter % targetPos.size()], 10);
	
	ofPopMatrix();

	ofSetColor(255);

	if (guiEnable)
	{
		ofDrawBitmapString("id: " + ofToString(counter % targetPos.size()), ofGetWidth() * 0.5, 20);
		ofDrawBitmapString("target position: " + ofToString(targetPos[counter % targetPos.size()]), ofGetWidth() * 0.5, 35);
		ofDrawBitmapString("agent velocity: " + ofToString(agentVel), ofGetWidth() * 0.5, 50);

		ofDrawBitmapString("press space to initilize", 30, ofGetHeight() - 45);
	}
	else 
	{
		ofDrawBitmapString("id: " + ofToString(counter % targetPos.size()), 10, 30);
	ofDrawBitmapString("target position: " + ofToString(targetPos[counter % targetPos.size()]), 10, 50);
	ofDrawBitmapString("agent velocity: " + ofToString(agentVel), 10, 70);

	//ofDrawBitmapString("press space to initilize", 30, ofGetHeight() - 45);
	}
	

	if (guiEnable)
	{
		gui.draw();
	}
	
	
}

void Pathfinder::drawAngleSimulation()
{
	if (ofGetFrameNum() % 15 == 0)
	{
		plateAngle.z = (agentVel.normalize()).x * (7.50);
		plateAngle.x = (agentVel.normalize()).y * (-7.50);

		osc.send("/angle/x", plateAngle.z);
		osc.send("/angle/y", plateAngle.x);
		
		//cout << "sending value : " << plateAngle << endl;
	}
	
	osc.checkReceivedMsg();
	
	//Draw Line
	ofPushMatrix();
	ofTranslate(0, 0);
	ofScale(0.5);
	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
	
	draw(false);

	ofPopMatrix();

	//Draw velocityX to AngleZ
	ofPushMatrix();
	ofTranslate(0, ofGetHeight() * 0.5);
	ofScale(0.5);
	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
	ofSetColor(255);
	ofDrawBitmapString("angleZ: " + ofToString(plateAngle.z), 10, 30);
	ofDrawBitmapString("angle servo: " + ofToString(tester.calcAngleRevised(21, 35, 93, plateAngle.z)), 10, 55);
	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	ofVec3f viewerPosVelX;

	viewerPosVelX.x = 300 * cos(ofDegToRad(plateAngle.z));
	viewerPosVelX.y = 300 * sin(ofDegToRad(plateAngle.z));

	ofDrawLine(viewerPosVelX, -viewerPosVelX);

	ofSetColor(255);
	
	ofPopMatrix();

	//Draw velocityY to AngleX
	ofPushMatrix();
	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
	ofScale(0.5);
	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

	ofSetColor(255);
	ofDrawBitmapString("angleX: " + ofToString(plateAngle.x), 10, 30);
	ofDrawBitmapString("angle servo: " + ofToString(tester.calcAngleRevised(21, 35, 93, plateAngle.x)), 10, 55);
	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	ofVec3f viewerPosVelY;

	viewerPosVelY.x = 300 * cos(ofDegToRad(plateAngle.x));
	viewerPosVelY.y = 300 * sin(ofDegToRad(plateAngle.x));

	ofDrawLine(viewerPosVelY, -viewerPosVelY);

	ofPopMatrix();

	//Draw velocityY to AngleX
	ofPushMatrix();
	ofTranslate(ofGetWidth() * 0.5, 0);
	ofScale(0.5);
	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

	ofSetColor(255);
	ofDrawBitmapString("3D Simluation: " + ofToString(plateAngle.x), 10, 30);

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
	int fieldSize = 450;

	ofSetColor(255);

	ofPushMatrix();

	ofRotateX(90 + lookingAngle->x);
	ofRotateZ(lookingAngle->y);

	ofSetColor(128);
	ofDrawRectangle(-fieldSize * 0.5, -fieldSize * 0.5, fieldSize, fieldSize);

	ofRotateX(plateAngle.x);
	ofRotateY(plateAngle.z );

	ofSetColor(255);
	ofDrawRectangle(-fieldSize * 0.5, -fieldSize * 0.5, fieldSize, fieldSize);

	ofPopMatrix();
	ofPopMatrix();

	guiB.draw();

}

void Pathfinder::keyPressed(int key)
{
	if (key == ' ')
	{
		initFlag = true;
	}
}

ofVec3f Pathfinder::curveCalc(int patternID, float theta, float valueA, float valueB, float valueC, float valueD, float valueE)
{
	ofVec3f outputPos;

	switch (patternID)
	{
	case 1:
		outputPos.x = valueA * cos(theta);
		outputPos.y = valueA * sin(theta);
		break;

	case 2:
		outputPos.x = valueA * sin(valueC * theta - valueE);
		outputPos.y = valueB * sin(valueD * theta);
		break;

	case 3:
		outputPos.x = valueA * pow(cos(theta), 3);
		outputPos.y = valueB * pow(sin(theta), 3);
		break;

	case 4:
		float _theta = TWO_PI * sin(theta);
		outputPos.x = valueA * (cos(_theta) + _theta * sin(_theta));
		outputPos.y = valueA * (sin(_theta) - _theta * cos(_theta));

		break;


	}

	return outputPos;
}

ofVec3f Pathfinder::curveCalc(int patternID, float theta, float valueA, float valueB, float valueC, float valueD)
{
	return curveCalc(patternID, theta, valueA, valueB, valueC, valueD, 0);
}

ofVec3f Pathfinder::curveCalc(int patternID, float theta, float valueA, float valueB, float valueC)
{
	return curveCalc(patternID, theta, valueA, valueB, valueC, 0, 0);
}

ofVec3f Pathfinder::curveCalc(int patternID, float theta, float valueA, float valueB)
{
	return curveCalc(patternID, theta, valueA, valueB, 0, 0, 0);
}

ofVec3f Pathfinder::curveCalc(int patternID, float theta, float valueA)
{
	return curveCalc(patternID, theta, valueA, 0.0, 0, 0, 0);
}