#include <iostream>
#include <irrlicht/irrlicht.h>
#include <irrlicht/driverChoice.h>
#include "EventReceiver.hpp"

using namespace irr;

int main() {
	// Choose driver
	video::E_DRIVER_TYPE driverType = driverChoiceConsole();
	if(driverType == video::EDT_COUNT) return 1;

	// Create eventReceiver variable
	EventReceiver eventReceiver;

	// Create the device we'll be using
	IrrlichtDevice *device = createDevice(driverType, core::dimension2d<u32>(800, 600), 32, false, false, false, &eventReceiver);
	if(device == 0) return 1;

	// Create other variables we'll need
	video::IVideoDriver *driver = device->getVideoDriver();
	scene::ISceneManager *smgr = device->getSceneManager();
	gui::IGUIEnvironment *guienv = device->getGUIEnvironment();

	// Add text to game
	guienv->addStaticText(L"Use WASD to move\nUse SPACE to jump\nUse R to reset\nUse ESC or Q to exit", core::rect<s32>(30, 30, 120, 72), false, false, 0, -1, true);

	// Load map
	device->getFileSystem()->addFileArchive("assets/map-20kdm2.pk3");
	scene::IAnimatedMesh *mapmesh = smgr->getMesh("20kdm2.bsp");
	scene::IMeshSceneNode *mapnode = 0;

	if(mapmesh) {
		// Create map octree node
		mapnode = smgr->addOctreeSceneNode(mapmesh->getMesh(0), 0, -1, 2048);
	}
	// Create Triangle selector for collision
	scene::ITriangleSelector *tselector = 0;
	if(mapnode) {
		// Set map position
		mapnode->setPosition(core::vector3df(-1350, -130, -1400));
		// Define triangle selector
		tselector = smgr->createOctreeTriangleSelector(mapnode->getMesh(), mapnode, 128);
		// Set the mapnode's triangle selector
		mapnode->setTriangleSelector(tselector);
	}

	// Setup new keys (not using default)
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

	// Create camera
	scene::ICameraSceneNode *cam = smgr->addCameraSceneNodeFPS(0, 100.0f, .3f, -1, keyMap, sizeof(keyMap) / sizeof(*keyMap), true, 3.0f);
	cam->setPosition(core::vector3df(50, 50, -60));
	cam->setTarget(core::vector3df(-70, 30, -60));

	if(tselector) {
		scene::ISceneNodeAnimator *sanim = smgr->createCollisionResponseAnimator(tselector, cam, core::vector3df(30, 50, 30), core::vector3df(0, -10, 0), core::vector3df(0, 30, 0));
		tselector->drop();
		cam->addAnimator(sanim);
		sanim->drop();
	}
	// Hide cursor
	device->getCursorControl()->setVisible(false);

	int lastFPS = -1;

	while(device->run()) {
		// Begin the scene
		driver->beginScene(true, true, video::SColor(50, 50, 255, 255));
		// Draw
		smgr->drawAll();
		guienv->drawAll();
		// End the scene
		driver->endScene();
		// Check for ESC key
		if(eventReceiver.IsKeyDown(KEY_ESCAPE) || eventReceiver.IsKeyDown(KEY_KEY_Q)) {
			device->closeDevice();
		}
		if(eventReceiver.IsKeyDown(KEY_KEY_R)) {
			cam->setPosition(core::vector3df(50, 50, -60));
			cam->setTarget(core::vector3df(-70, 30, -60));
		}

		// Print FPS
		int fps = driver->getFPS();
		if(lastFPS != fps) {
			std::cout << "FPS: " << fps << std::endl;
			lastFPS = fps;
		}
	}

	// Drop the device and quit
	device->drop();
	return 0;
}
