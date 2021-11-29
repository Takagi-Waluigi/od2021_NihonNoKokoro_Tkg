#include "AngleTester.h"

void AngleTester::setup()
{
	gui.setup();

	float initVal = 1.57894737;
	
	lengthRatio.set("length ratio", initVal , 0, 5);
	angleRatio.set("angle ratio", 3, 0, 5);
	angle.set("angle", 0, -30, 30);

	gui.add(lengthRatio);
	gui.add(angleRatio);
	gui.add(angle);
}

void AngleTester::draw()
{

	ofVec2f posA, posB, posC;	//リンクの各頂点の座標
	float thetaPlate, thetaA, thetaB, thetaC;	//各頂点における角度θ
	float a, b, c;	//各頂点の長さ
	float offset = 8.0; //描画上のオフセット
	int w = ofGetWidth();
	int h = ofGetHeight();

	lengthRatio = 1.57894737;
	thetaPlate = ofDegToRad(angle);

	a = 19.0;
	b = 30.0;

	ofSetColor(128);

	ofDrawLine(w * 0.25, h * 0.5, w * 0.75, h * 0.5);

	ofSetColor(255);

	posA.x = w * 0.5 * cos(thetaPlate) + w * 0.25;
	posA.y = w * 0.5 * sin(thetaPlate) + h * 0.50;

	posB.x = w * 0.75;
	posB.y = sqrt(double(a * a + b * b)) * offset + h * 0.50;

	thetaC = HALF_PI - thetaPlate * angleRatio;
    
	c = sqrt(a * a + b * b - 2 * a * b * cos(thetaC));

	float cosBvalue = (c * c + a * a - b * b) / (2 * c * a);
	thetaB = acos(cosBvalue);

	ofClamp(thetaB, 0, 180);

	float thetaBA = atan2(posA.y - posB.y, posA.x - posB.x);
	posC.x = posB.x - a * cos(thetaBA + thetaB) * offset;
	posC.y = posB.y + a * sin(thetaBA + thetaB) * offset;

	ofDrawLine(posA, posB);
	ofDrawLine(posB, posC);
	ofDrawLine(posC, posA);	
	ofDrawLine(w * 0.25, h * 0.5, posA.x, posA.y);

	ofNoFill();
	ofDrawCircle(posA, 20);
	ofDrawCircle(posB, 20);
	ofDrawCircle(posC, 20);
	ofDrawCircle(w * 0.25, h * 0.5, 20);

	gui.draw();

	ofDrawBitmapString("servo angle: " + ofToString(90 - ofRadToDeg(thetaBA + thetaB)), ofGetWidth() / 2, 30);

}

//a = 21, b = 35 l = 93
void AngleTester::drawRevised(float a, float b, float l, float anglePlate)
{
	ofVec2f posA, posB, posC, posZero;
	float thetaB, thetaH, _thetaH;
	float offset = 4.0;
	float c;
	float cosBvalue;
	float thetaPlate = ofDegToRad(anglePlate);
	int w = ofGetWidth();
	int h = ofGetHeight();

	ofPushMatrix();
	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
	ofScale(1.0, -1.0, 1.0);

	ofSetColor(128);
	ofDrawLine(-w * 0.5, 0, w * 0.5, 0);
	ofDrawLine(0, -w * 0.5, 0, w * 0.5);

	ofSetColor(255);
	posZero = ofVec2f(0, 0);

	posA.x = l * cos(thetaPlate);
	posA.y = l * sin(thetaPlate);

	posB.x = l;
	posB.y = -sqrt(b * b - a * a);

	c = ofDist(posA.x, posA.y, posB.x, posB.y);

	if (b - a < c && c < b + a)
	{
		cosBvalue = (a * a + c * c - b * b) / (2 * a * c);
		thetaB = acos(cosBvalue);
		_thetaH = atan2(posA.y - posB.y, posA.x - posB.x);
		thetaH = PI - (thetaB + _thetaH);

		posC.x = a * cos(thetaB + _thetaH);
		posC.y = a * sin(thetaB + _thetaH);
		posC += posB;

		ofDrawLine(posZero, posA * offset);
		ofDrawCircle(posA * offset, 20);

		ofDrawLine(posA * offset, posB * offset);
		ofDrawCircle(posB * offset, 20);

		ofDrawLine(posA * offset, posC * offset);
		ofDrawLine(posB * offset, posC * offset);
		ofDrawCircle(posC * offset, 20);

		ofDrawBitmapString("c: " + ofToString(c), 0, h * 0.5 -30);
		ofDrawBitmapString("angle B: " + ofToString(ofRadToDeg(thetaB)), 0, h * 0.5 - 45);
		ofDrawBitmapString("angle H': " + ofToString(ofRadToDeg(_thetaH)), 0, h * 0.5 - 60);
		ofDrawBitmapString("angle servo: " + ofToString(ofRadToDeg(thetaH) + 90), 0, h * 0.5 - 75);
		ofDrawBitmapString("angle servo: " + ofToString(calcAngleRevised(a, b, l, anglePlate)), 0, h * 0.5 - 75);
	}
	else 
	{
		ofDrawBitmapString("cannnot draw!!!", 0, -h * 0.5 + 30);
	}
	

	ofPopMatrix();

	


}

float AngleTester::calcAngle(float inputAngle, float ar)
{
	float outputAngle = 0.0;

	ofVec2f posA, posB, posC;	//リンクの各頂点の座標
	float thetaPlate, thetaB, thetaC;	//各頂点における角度θ
	float a, b, c;	//各頂点の長さ
	float offset = 8.0;
	int w = ofGetWidth();
	int h = ofGetHeight();

	thetaPlate = ofDegToRad(inputAngle);

	thetaC = HALF_PI - thetaPlate * ar;

	a = 19.0;
	b = 30.0;
	c = sqrt(a * a + b * b - 2 * a * b * cos(thetaC));

	posA.x = w * 0.5 * cos(thetaPlate) + w * 0.25;
	posA.y = w * 0.5 * sin(thetaPlate) + h * 0.50;

	posB.x = w * 0.75;
	posB.y = sqrt(double(a * a + b * b)) * offset + h * 0.50;

	float cosBvalue = (c * c + a * a - b * b) / (2 * c * a);
	thetaB = acos(cosBvalue);

	ofClamp(thetaB, 0, 180);

	float thetaBA = atan2(posA.y - posB.y, posA.x - posB.x);

	return outputAngle = 90 - ofRadToDeg(thetaBA + thetaB);
}

float AngleTester::calcAngleRevised(float a, float b, float l, float anglePlate)
{
	ofVec2f posA, posB, posC, posZero;
	float thetaB, thetaH, _thetaH;
	float c;
	float cosBvalue;
	float thetaPlate = ofDegToRad(anglePlate);
	posZero = ofVec2f(0, 0);

	posA.x = l * cos(thetaPlate);
	posA.y = l * sin(thetaPlate);

	posB.x = l;
	posB.y = -sqrt(b * b - a * a);

	c = ofDist(posA.x, posA.y, posB.x, posB.y);

	if (b - a < c && c < b + a)
	{
		cosBvalue = (a * a + c * c - b * b) / (2 * a * c);
		thetaB = acos(cosBvalue);
		_thetaH = atan2(posA.y - posB.y, posA.x - posB.x);
		thetaH = PI - (thetaB + _thetaH);

		return ofRadToDeg(thetaH) + 90;
	}
	else
	{
		return 0;
	}
}

void AngleTester::drawRevisedv2(float a, float b, float l, float anglePlate)
{
	ofVec2f posA, posB, posC, posZero;
	float thetaB, thetaH, _thetaH;
	float offset = 4.0;
	float c;
	float cosBvalue;
	float thetaPlate = ofDegToRad(anglePlate);
	int w = ofGetWidth();
	int h = ofGetHeight();
	float servoangle = 0.0;

	ofPushMatrix();
	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
	ofScale(1.0, -1.0, 1.0);

	ofSetColor(200);
	ofDrawLine(w * 0.5, 0, -w * 0.5, 0);
	ofDrawLine(0, h * 0.5, 0, -h * 0.5);
	
	ofSetColor(255);

	posA.x= l * cos(thetaPlate);
	posA.y = l * sin(thetaPlate);

	posB.x = l;
	posB.y = -sqrt(b * b - a * a);

	c = ofDist(posA.x, posA.y, posB.x, posB.y);

	cosBvalue = (a * a + c * c - b * b) / (2 * a * c);
	thetaB = acos(cosBvalue);
	_thetaH = atan2(posA.y - posB.y, posA.x - posB.x);

	posC.x = a * cos(_thetaH + thetaB);
	posC.y = a * sin(_thetaH + thetaB);

	posC += posB;

	ofDrawLine(posA * offset, posB * offset);
	ofDrawLine(posB * offset, posC * offset);
	ofDrawLine(posC * offset, posA * offset);
	ofDrawLine(posA * offset, ofVec2f(0, 0));

	ofDrawCircle(posA * offset, 20);
	ofDrawCircle(posB * offset, 20);
	ofDrawCircle(posC * offset, 20);

	servoangle = 270 - ofRadToDeg(_thetaH + thetaB);

	/*
	if (b - a < c && c < a + b)
	{
		cosBvalue = (a * a + c * c - b * b) / (2 * a * c);
		thetaB = acos(cosBvalue);
		_thetaH = atan2(posA.y - posB.y, posA.x - posB.x);

		posC.x = a * cos(_thetaH + thetaB);
		posC.y = a * sin(_thetaH + thetaB);

		posC += posB;

		ofDrawLine(posA * offset, posB * offset);
		ofDrawLine(posB * offset, posC * offset);
		ofDrawLine(posC * offset, posA * offset);
		ofDrawLine(posA * offset, ofVec2f(0, 0));

		ofDrawCircle(posA * offset, 20);
		ofDrawCircle(posB * offset, 20);
		ofDrawCircle(posC * offset, 20);

		servoangle = 270 - ofRadToDeg(_thetaH + thetaB);
	}
	*/
	ofPopMatrix();

	
	ofDrawBitmapString("servo angle: " + ofToString(servoangle), ofGetWidth() * 0.5, 30);

}

float AngleTester::calcAngleRevisedv2(float a, float b, float l, float anglePlate)
{
	ofVec2f posA, posB, posC, posZero;
	float thetaB, thetaH, _thetaH;
	float c;
	float cosBvalue;
	float thetaPlate = ofDegToRad(anglePlate);
	float servoangle = 0.0;

	posA.x = l * cos(thetaPlate);
	posA.y = l * sin(thetaPlate);

	posB.x = l;
	posB.y = -sqrt(b * b - a * a);

	c = ofDist(posA.x, posA.y, posB.x, posB.y);


	if (b - a < c && c < a + b)
	{
		cosBvalue = (a * a + c * c - b * b) / (2 * a * c);
		thetaB = acos(cosBvalue);
		_thetaH = atan2(posA.y - posB.y, posA.x - posB.x);
		servoangle = 270 - ofRadToDeg(_thetaH + thetaB);
	}

	return servoangle;

}