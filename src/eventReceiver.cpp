#include "eventReceiver.h"

EventReceiver::EventReceiver() {
	for(u32 i = 0; i < KEY_KEY_CODES_COUNT; i++) {
		KeyIsDown[i] = false;
	}
}

bool EventReceiver::OnEvent(const SEvent &event) {
	if(event.EventType == irr::EET_KEY_INPUT_EVENT) {
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
	}
	return false;
}

const bool EventReceiver::IsKeyDown(EKEY_CODE keyCode) {
	return KeyIsDown[keyCode];
}
