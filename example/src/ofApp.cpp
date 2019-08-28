#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowTitle("ofApp");
	ofBackground(0,0,0);

	ofSetFrameRate(120);
	ofSetLogLevel(OF_LOG_VERBOSE);

	ofxGamepadHandler::get().enableHotplug();
	
	// Add event listeners if a gamepad is connected.
	if (ofxGamepadHandler::get().getNumPads() > 0)
	{
		auto gamepad = ofxGamepadHandler::get().getGamepad(0);
		ofAddListener(gamepad->onAxisChanged, this, &ofApp::axisChanged);
		ofAddListener(gamepad->onButtonPressed, this, &ofApp::buttonPressed);
		ofAddListener(gamepad->onButtonReleased, this, &ofApp::buttonReleased);
		ofAddListener(gamepad->onPovChanged, this, &ofApp::povChanged);
	}
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofxGamepadHandler::get().draw(10,10);
}

//--------------------------------------------------------------

void ofApp::axisChanged(ofxGamepadAxisEvent& e)
{
	ofLogNotice(__FUNCTION__) << "Axis " << e.axis << " Value " << ofToString(e.value);
}

void ofApp::buttonPressed(ofxGamepadButtonEvent& e)
{
	ofLogNotice(__FUNCTION__) << "Button " << e.button << " Pressed";
}

void ofApp::buttonReleased(ofxGamepadButtonEvent& e)
{
	ofLogNotice(__FUNCTION__) << "Button " << e.button << " Released";
}

void ofApp::povChanged(ofxGamepadPovEvent& e)
{
	ofLogNotice(__FUNCTION__) << "POV " << e.pov << " Value " << ofToString(e.value);
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}



