#include "EventReceiver.hpp"

// Initialize
EventReceiver::EventReceiver() {
	// Set all keys to false, because none of them are pressed
	for(u32 i = 0; i < KEY_KEY_CODES_COUNT; i++) {
		KeyIsDown[i] = false;
	}
}

bool EventReceiver::OnEvent(const SEvent &event) {
	// If the input event is a key press
	if(event.EventType == irr::EET_KEY_INPUT_EVENT) {
		// Set our keyIsDown variable to the event one
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
	}
	return false;
}

const bool EventReceiver::IsKeyDown(EKEY_CODE keyCode) {
	// Return if the key is down
	return KeyIsDown[keyCode];
}
