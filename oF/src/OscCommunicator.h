#pragma once
#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOsc.h"

#define SEND_PORT 5005
#define RECIEVE_PORT 8003
#define HOST "127.0.0.1"

class OscCommunicator
{
public:
	void setup();
	void send(string message, float value);
	void send(string message, int value);
	float receive(string message);
	void dumpOsc(ofxOscMessage m);
	void checkReceivedMsg();
	ofxOscSender sender;
	ofxOscReceiver receiver;
};

