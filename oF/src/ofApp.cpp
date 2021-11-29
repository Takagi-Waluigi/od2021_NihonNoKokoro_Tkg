#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0);

	angleTester.setup();
	simulator.setup();
	pathfinder.setup();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	switch (mode)
	{
	case 0:
		angleTester.draw();
		break;

	case 1:
		angleTester.drawRevisedv2(21, 35, 93, 8 * sin(ofGetElapsedTimef()));

		ofDrawBitmapString(ofToString(angleTester.calcAngleRevisedv2(21, 35, 93, 8 * sin(ofGetElapsedTimef()))), ofGetWidth() * 0.5, 45);
		break;

	case 2:
		simulator.drawSimulationViewer(false);
		break;

	case 3:
		simulator.drawSimulationViewer(true);
		break;

	case 4:
		pathfinder.draw(true);
		break;

	case 5:
		pathfinder.drawAngleSimulation();
		break;


	}


	ofDrawBitmapString("press 0/1/2 to switch modes", 30, ofGetHeight() - 30);
	

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key)
	{
	case '0':
		mode = 0;
		break;


	case '1':
		mode = 1;
		break;

	case '2':
		mode = 2;
		break;

	case '3':
		mode = 3;

		break;

	case '4':
		mode = 4;
		break;

	case '5':
		mode = 5;
		break;



	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	pathfinder.keyPressed(key);
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
