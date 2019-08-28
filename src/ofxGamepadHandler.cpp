#include "ofxGamepadHandler.h"

#ifdef USE_OIS
using namespace OIS;
InputManager* oisInputManager;
class tempPad {
public:
	tempPad(JoyStick* s) {
		stick=s;
		handled=false;
	};
	JoyStick* stick;
	bool handled;
};
#endif

ofxGamepadHandler::ofxGamepadHandler():hasHotplug(false),hotplugNext(0) {
	ofAddListener(ofEvents().update, this, &ofxGamepadHandler::update);
	ofAddListener(ofEvents().exit, this, &ofxGamepadHandler::exit);
	updatePadList();
	gamepads.insert(gamepads.end(), gamepadsNew.begin(), gamepadsNew.end());
	gamepadsNew.clear();
}

ofxGamepadHandler::~ofxGamepadHandler() {
	waitForThread();
}

ofxGamepadHandler& ofxGamepadHandler::get() {
	static ofxGamepadHandler singleton;
	return singleton;
}

void ofxGamepadHandler::enableHotplug(int interval) {
	hasHotplug=true;
	hotplugInterval=interval;
	startThread();
}

void ofxGamepadHandler::threadedFunction() {
	while(isThreadRunning()) {

		updatePadList();
		lock();

#ifdef USE_OIS
		gamepads = gamepadsNew;
#else
		if(gamepadsNew.size() > 0) {
			gamepads.insert(gamepads.end(), gamepadsNew.begin(), gamepadsNew.end());
		}
#endif
		unlock();

		gamepadsNew.clear();
		ofSleepMillis(hotplugInterval);
	}
}

void ofxGamepadHandler::updatePadList() {
#ifdef USE_OIS
	try {
		
		ParamList pl;
#if defined OIS_WIN32_PLATFORM
		// On Windows, a handle to the window needs to be passed to the input manager / OIS
		if (hWnd == 0)
		{
			HWND windowHandle = ofGetWin32Window();
			std::ostringstream wnd;
			wnd << (size_t)windowHandle;

			pl.insert(std::make_pair(std::string("WINDOW"), wnd.str()));
		}
#endif
		InputManager* inputManager=InputManager::createInputSystem(pl);

		gamepadList padsOld=gamepads;
		std::vector<tempPad> sticks;
		//gamepads.clear();

		int numPads = inputManager->getNumberOfDevices(OISJoyStick);
		for (int i = 0; i < numPads; i++)
		{
			JoyStick* js = (JoyStick*)inputManager->createInputObject(OISJoyStick, true);
			sticks.push_back(tempPad(js));
		}

		auto sIt = sticks.begin();
		while (sIt != sticks.end()) 
		{
			auto& s = *sIt;
			auto pIt = padsOld.begin();
			while (pIt != padsOld.end())
			{
				auto p = *pIt;
				if (s.stick->vendor() == p->name) 
				{
					p->updateJoystick(s.stick);
					gamepadsNew.push_back(p);
					padsOld.erase(pIt);
					s.handled = true;
					break;
				}
				++pIt;
			}
			++sIt;
		}

		sIt = sticks.begin();
		while(sIt!=sticks.end()) 
		{
			auto& s = *sIt;
			if (!s.handled)
			{
				gamepadsNew.push_back(std::make_shared<ofxGamepadOIS>(s.stick));
			}
			++sIt;
		}

		lock();
		if(oisInputManager != NULL) {
			oisInputManager->destroyInputSystem(oisInputManager);
		}
		unlock();

		oisInputManager = inputManager;
	} catch(OIS::Exception &ex) {
		ofLogError(__FUNCTION__) << "Exception raised on joystick creation: " << ex.eText;
	}
#elif defined(TARGET_LINUX)
	//check for joysticks
	ofFile file;
	for(int i=0; i<32; i++) {
		file.open("/dev/input/js"+ofToString(i));
		if(file.exists() && find(activeIDs.begin(), activeIDs.end(), i) == activeIDs.end()) {
			try {
				gamepadsNew.push_back(std::make_shared<ofxGamepadLinux>(file.getAbsolutePath()));
				activeIDs.push_back(i);
			} catch(std::exception& err) {
				ofLog(OF_LOG_ERROR, "could not create new gamepad");
			}
		}
	}
#else
	ofLogError(__FUNCTION__) << "Sorry, looks like your system is not supported...";
#endif
}

void ofxGamepadHandler::update(ofEventArgs &args) {
	update();
}

void ofxGamepadHandler::update() {
	lock();
	for (auto pad : gamepads)
	{
		pad->update();
	}
	unlock();
}

void ofxGamepadHandler::draw(int x, int y) {
	ofPushMatrix();
	ofTranslate(x, y);
	ofPoint offset(x, y);

		for (auto pad : gamepads)
		{
			pad->draw(offset.x, offset.y);
			offset.x += pad->drawSize.x + 20.0f;
		}
	}

	ofPopMatrix();
}

void ofxGamepadHandler::exit(ofEventArgs& arg)
{
	for (auto pad : gamepads)
	{
		pad->exit();
	}
}

std::shared_ptr<ofxGamepad> ofxGamepadHandler::getGamepad(int num)
{
	if (getNumPads() > num)
	{
		return gamepads[num];
	}
	ofLogWarning(__FUNCTION__) << "No gamepad at index " << num;
	return nullptr;
}

int ofxGamepadHandler::getNumPads() {
	return gamepads.size();
}
