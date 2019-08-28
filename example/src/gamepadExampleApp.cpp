#include "gamepadExampleApp.h"

//--------------------------------------------------------------
void gamepadExampleApp::setup(){
	// Note: this name is also used in ofxGamepadHandler.cpp line 77 to get the window handle. Make sure they match!
	ofSetWindowTitle("gamepadExampleApp");
	ofBackground(0,0,0);

	ofSetFrameRate(120);
	ofSetLogLevel(OF_LOG_VERBOSE);

	//ofxGamepadHandler::get()->enableHotplug();	// Disabled
		
	//CHECK IF THERE EVEN IS A GAMEPAD CONNECTED
	if(ofxGamepadHandler::get()->getNumPads()>0){
			ofxGamepad* pad = ofxGamepadHandler::get()->getGamepad(0);
			ofAddListener(pad->onAxisChanged, this, &gamepadExampleApp::axisChanged);
			ofAddListener(pad->onButtonPressed, this, &gamepadExampleApp::buttonPressed);
			ofAddListener(pad->onButtonReleased, this, &gamepadExampleApp::buttonReleased);
			ofAddListener(pad->onPovChanged, this, &gamepadExampleApp::povChanged);
	}
}

//--------------------------------------------------------------
void gamepadExampleApp::update(){
}

//--------------------------------------------------------------
void gamepadExampleApp::draw(){
	ofxGamepadHandler::get()->draw(10,10);
}

//--------------------------------------------------------------

void gamepadExampleApp::axisChanged(ofxGamepadAxisEvent& e)
{
	cout << "AXIS " << e.axis << " VALUE " << ofToString(e.value) << endl;
}

void gamepadExampleApp::buttonPressed(ofxGamepadButtonEvent& e)
{
	cout << "BUTTON " << e.button << " PRESSED" << endl;
}

void gamepadExampleApp::buttonReleased(ofxGamepadButtonEvent& e)
{
	cout << "BUTTON " << e.button << " RELEASED" << endl;
}

void gamepadExampleApp::povChanged(ofxGamepadPovEvent &e)
{
	cout << "POV " << e.pov << " ";

	if( e.value & OIS::Pov::North ) //Going up
		std::cout << "North";
	else if( e.value & OIS::Pov::South ) //Going down
		std::cout << "South";

	if( e.value & OIS::Pov::East ) //Going right
		std::cout << "East";
	else if( e.value & OIS::Pov::West ) //Going left
		std::cout << "West";

	if( e.value == OIS::Pov::Centered ) //stopped/centered out
		std::cout << "Centered";

	cout << endl;
}

//--------------------------------------------------------------
void gamepadExampleApp::keyPressed(int key){

}

//--------------------------------------------------------------
void gamepadExampleApp::keyReleased(int key){

}

//--------------------------------------------------------------
void gamepadExampleApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void gamepadExampleApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void gamepadExampleApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void gamepadExampleApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void gamepadExampleApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void gamepadExampleApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void gamepadExampleApp::dragEvent(ofDragInfo dragInfo){ 

}



