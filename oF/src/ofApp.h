#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOsc.h"

#define SEND_PORT 8005
#define RPI4_IP "127.0.0.1"
#define RECIEVE_PORT 5006
#define WIN_IP "127.0.0.1"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofVec3f barrier(ofVec3f inputPos);

		ofxOscSender sender;
		ofxOscReceiver reciever;

		ofxPanel gui;
		ofParameter<bool> enableSend;
		bool _enableSend;
		ofParameter<int> drawMode;
		ofParameter<int> separate;
		int status;
		int _status;

		vector<ofVec3f> path;
		int currentID;

		int currentFrame = 0;
		int lastFrame = 0;

		ofVec3f acceleration;
};
