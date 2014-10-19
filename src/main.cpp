#include <iostream>
#include <irrlicht.h>
#include "driverChoice.h"
#include "eventReceiver.h"

using namespace irr;

enum {
	ID_IsNotPickable = 0,
	IDFlag_IsPickable = 1 << 0,
	IDFlag_IsHighlightable = 1 << 1
};

int main() {
	// Choose driver
	video::E_DRIVER_TYPE driverType = driverChoiceConsole();
	if(driverType == video::EDT_COUNT) return 1;

	EventReceiver eventReceiver;

	IrrlichtDevice *device = createDevice(driverType, core::dimension2d<u32>(1280, 720), 32, true, false, false, &eventReceiver);
	if(device == 0) return 1;

	video::IVideoDriver *driver = device->getVideoDriver();
	scene::ISceneManager *smgr = device->getSceneManager();
	gui::IGUIEnvironment *guienv = device->getGUIEnvironment();

	guienv->addStaticText(L"Use WASD to move\nUse SPACE to jump\nUse Left Shift to crouch\nUse ESC to exit", core::rect<s32>(30, 30, 120, 75), false, false, 0, -1, true);

	device->getFileSystem()->addFileArchive("../res/map-20kdm2.pk3");
	scene::IAnimatedMesh *mapmesh = smgr->getMesh("20kdm2.bsp");
	scene::IMeshSceneNode *mapnode = 0;

	if(mapmesh) {
		mapnode = smgr->addOctreeSceneNode(mapmesh->getMesh(0), 0, IDFlag_IsPickable);
	}
	scene::ITriangleSelector *tselector = 0;
	if(mapnode) {
		mapnode->setPosition(core::vector3df(-1350, -130, -1400));
		tselector = smgr->createOctreeTriangleSelector(mapnode->getMesh(), mapnode, 128);
		mapnode->setTriangleSelector(tselector);
	}

	// Setup new keys
	SKeyMap keyMap[6];
	keyMap[0].Action = EKA_MOVE_FORWARD;
	keyMap[0].KeyCode = KEY_KEY_W;
	keyMap[1].Action = EKA_MOVE_BACKWARD;
	keyMap[1].KeyCode = KEY_KEY_S;
	keyMap[2].Action = EKA_STRAFE_LEFT;
	keyMap[2].KeyCode = KEY_KEY_A;
	keyMap[3].Action = EKA_STRAFE_RIGHT;
	keyMap[3].KeyCode = KEY_KEY_D;
	keyMap[4].Action = EKA_JUMP_UP;
	keyMap[4].KeyCode = KEY_SPACE;
	keyMap[5].Action = EKA_CROUCH;
	keyMap[5].KeyCode = KEY_LSHIFT;

	scene::ICameraSceneNode *cam = smgr->addCameraSceneNodeFPS(0, 100.0f, .3f, ID_IsNotPickable, keyMap, 6, true, 3.0f);
	cam->setPosition(core::vector3df(50, 50, -60));
	cam->setTarget(core::vector3df(-70, 30, -60));

	if(tselector) {
		scene::ISceneNodeAnimator *sanim = smgr->createCollisionResponseAnimator(tselector, cam, core::vector3df(30, 50, 30), core::vector3df(0, -10, 0), core::vector3df(0, 30, 0));
		tselector->drop();
		cam->addAnimator(sanim);
		sanim->drop();
	}
	device->getCursorControl()->setVisible(false);

	int lastFPS = -1;

	while(device->run()) {
		driver->beginScene(true, true, video::SColor(0, 255, 101, 255));
		smgr->drawAll();
		guienv->drawAll();
		driver->endScene();
		if(eventReceiver.IsKeyDown(KEY_ESCAPE)) {
			device->closeDevice();
		}

		int fps = driver->getFPS();

		if(lastFPS != fps) {
			std::cout << "FPS: " << fps << std::endl;
			lastFPS = fps;
		}
	}

	device->drop();
	return 0;
}
