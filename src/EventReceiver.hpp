#include <irrlicht/irrlicht.h>

using namespace irr;

class EventReceiver : public IEventReceiver {
	public:
		EventReceiver();
		virtual bool OnEvent(const SEvent &event);
		virtual const bool IsKeyDown(EKEY_CODE keyCode);
	private:
		bool KeyIsDown[KEY_KEY_CODES_COUNT];
};
