#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);

	sender.setup(RPI4_IP, SEND_PORT);
	reciever.setup(RECIEVE_PORT);

	gui.setup();
	enableSend.set("enable send", false);
	drawMode.set("draw pattern", 1, 0, 10);
	separate.set("n sepate", 10, 1, 100);

	gui.add(enableSend);
	gui.add(drawMode);
	gui.add(separate);

	status = 0;
	currentID = 0;

	ofSetBackgroundColor(0);

	
}

//--------------------------------------------------------------
void ofApp::update(){
	
	int n = 0;
	switch (drawMode)
	{

	//01.Circle
	case 0:
		path.clear();
		n = separate;

		for (int i = 0; i < n; i ++)
		{
			ofVec3f pos;
			pos.x = (200 + (acceleration.x * 5) + (acceleration.z * 5)) * cos( i * (TWO_PI / n));
			pos.y = (200 + (acceleration.y * 5) + (acceleration.z * 5)) * sin(i * (TWO_PI / n));
			pos.z = 0;

			pos = barrier(pos);
			path.push_back(pos);
		}

		break;

	//02.SimpleLine
	case 1:
		path.clear();
		path.push_back(ofVec3f(-100, 0));
		path.push_back(ofVec3f(100, 0));

		break;

	//03.Point
	case 2:
		path.clear();
		path.push_back(ofVec3f(0., 0));

		break;

	//04.SimpleRectangle
	case 3:
		path.clear();
		float rectRadius = (reciever.hasWaitingMessages()) ? 100 :  sqrt(acceleration.x * acceleration.x + acceleration.y * acceleration.y + acceleration.z * acceleration.z)* 50 + 100;
		path.push_back(ofVec3f(-rectRadius, -rectRadius));
		path.push_back(ofVec3f(-rectRadius,  rectRadius));
		path.push_back(ofVec3f(  rectRadius, rectRadius));
		path.push_back(ofVec3f(  rectRadius, -rectRadius));

		break;

	}
	
    while (reciever.hasWaitingMessages())
    {
        ofxOscMessage msg;
        reciever.getNextMessage(msg);
		if (msg.getAddress() == "/status")
		{
			status = msg.getArgAsInt(0);
			
			cout << "status: " << status << endl;
		}

		if (msg.getAddress() == "/acc/x") acceleration.x = msg.getArgAsFloat(0);
		if (msg.getAddress() == "/acc/y") acceleration.y = msg.getArgAsFloat(0);
		if (msg.getAddress() == "/acc/z") acceleration.z = msg.getArgAsFloat(0);
    }

	if (status == 1 && (_status != status))
	{
		currentID++;
	}

	if (enableSend)
	{
		if (enableSend != _enableSend)
		{
			ofVec3f nextPath = ofVec3f(0, 0, 0);
			ofxOscMessage m;

			m.setAddress("/path/x");
			m.addFloatArg(nextPath.x);
			sender.sendMessage(m);

			m.setAddress("/path/y");
			m.addFloatArg(nextPath.y);
			sender.sendMessage(m);
		}

		if (status == 1)
		{
			ofVec3f nextPath = path[currentID % path.size()];
			ofxOscMessage m;

			m.setAddress("/path/x");
			m.addFloatArg(nextPath.x);
			sender.sendMessage(m);

			m.setAddress("/path/y");
			m.addFloatArg(nextPath.y);
			sender.sendMessage(m);

		}
	}


	_status = status;
	_enableSend = enableSend;
}

ofVec3f ofApp::barrier(ofVec3f inputPos)
{
	if (inputPos.x > ofGetWidth() * 0.45) inputPos.x = ofGetWidth() * 0.45;
	if (inputPos.x < -ofGetWidth() * 0.45) inputPos.x = -ofGetWidth() * 0.45;

	if (inputPos.y > ofGetHeight() * 0.45) inputPos.x = ofGetHeight() * 0.45;
	if (inputPos.y < -ofGetHeight() * 0.45) inputPos.x = -ofGetHeight() * 0.45;

	return inputPos;

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(255);
	ofDrawBitmapString("Client IP: " + ofToString(RPI4_IP), ofGetWidth() * 0.75, 15);
	ofDrawBitmapString("Server IP: " + ofToString(WIN_IP), ofGetWidth() * 0.75, 30);
	ofDrawBitmapString("Client Port: " + ofToString(SEND_PORT), ofGetWidth() * 0.75, 45);
	ofDrawBitmapString("Server Port: " + ofToString(RECIEVE_PORT), ofGetWidth() * 0.75, 60);
	ofDrawBitmapString("Acceleration X: " + ofToString(acceleration.x), ofGetWidth() * 0.75, 75);
	ofDrawBitmapString("Acceleration Y: " + ofToString(acceleration.y), ofGetWidth() * 0.75, 90);
	ofDrawBitmapString("Acceleration Z: " + ofToString(acceleration.z), ofGetWidth() * 0.75, 105);
	ofDrawBitmapString("Agent Status: " + ofToString(status), ofGetWidth() * 0.75, 120);

	gui.draw();

	ofPushMatrix();
	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
	ofNoFill();
	for (auto p :path)
	{
		ofSetColor(255);
		ofDrawCircle(p, 10);
	}

	ofSetColor(255, 0, 0);
	ofDrawCircle(path[currentID % path.size()], 15);

	ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
