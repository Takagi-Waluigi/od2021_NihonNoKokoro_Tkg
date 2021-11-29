#include "OscCommunicator.h"

void OscCommunicator::setup()
{
    sender.setup(HOST, SEND_PORT);
    receiver.setup(RECIEVE_PORT);
}

void OscCommunicator::send(string message, float value)
{
    ofxOscMessage m;
    m.setAddress(message);
    m.addFloatArg(value);
    sender.sendMessage(m);

}

void OscCommunicator::send(string message, int value)
{
    ofxOscMessage m;
    m.setAddress(message);
    m.addIntArg(value);
    sender.sendMessage(m);

}

float OscCommunicator::receive(string message)
{
    float incomingValue = 0.0;

    while (receiver.hasWaitingMessages())
    {
        ofxOscMessage msg;
        receiver.getNextMessage(msg);

        if (msg.getAddress() == message)
        {
            cout << "receiver : success" << endl;
        }
    }
    return incomingValue;
}

void OscCommunicator::dumpOsc(ofxOscMessage m)
{
    string msg_string;
    msg_string = m.getAddress();
    for (int i = 0; i < m.getNumArgs(); i++) {
        msg_string += " ";
        if (m.getArgType(i) == OFXOSC_TYPE_INT32)
            msg_string += ofToString(m.getArgAsInt32(i));
        else if (m.getArgType(i) == OFXOSC_TYPE_FLOAT)
            msg_string += ofToString(m.getArgAsFloat(i));
        else if (m.getArgType(i) == OFXOSC_TYPE_STRING)
            msg_string += m.getArgAsString(i);
    }

    cout << msg_string << endl;

}

void OscCommunicator::checkReceivedMsg()
{
    while (receiver.hasWaitingMessages())
    {
        ofxOscMessage msg;
        receiver.getNextMessage(msg);

        dumpOsc(msg);
    }
}