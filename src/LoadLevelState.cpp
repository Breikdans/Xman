#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "IntroState.h"
#include "MenuState.h"
#include "LoadLevelState.h"
#include "InfoGame.h"
#include "Importer.h"
#include "LevelInfo.h"
#include "PlayState.h"

template<> LoadLevelState* Ogre::Singleton<LoadLevelState>::msSingleton = 0;

//28 X 31

void LoadLevelState::enter()
{
	int currentLevel = InfoGame::getSingleton().getCurrentLevel();
	LoadLevel( InfoGame::getSingleton().getLevel(currentLevel) );

	_exitGame = false;
}

void LoadLevelState::LoadLevel(const LevelInfo &level)
{
	Scene scene;

	std::string f = level.getPathFolder();
	std::string m = level.getXmlFile();
	std::string fileXML = f + m;

	Importer::getSingleton().parseScene(fileXML.c_str(), &scene);

	InfoGame::getSingleton().setScene(scene);

	PlayState::getSingleton().getPacman().setSpeed(level.getPlayerSpeed());
	PlayState::getSingleton().getRed().setSpeed(level.getPlayerSpeed());
	PlayState::getSingleton().getPink().setSpeed(level.getPinkGhostSpeed());
	PlayState::getSingleton().getBlue().setSpeed(level.getBlueGhostSpeed());
	PlayState::getSingleton().getOrange().setSpeed(level.getOrangeGhostSpeed());

	PlayState::getSingleton().getRed().setTimeChase(level.getPlayerSpeed());
	PlayState::getSingleton().getPink().setSpeed(level.getPinkGhostSpeed());
	PlayState::getSingleton().getBlue().setSpeed(level.getBlueGhostSpeed());
	PlayState::getSingleton().getOrange().setSpeed(level.getOrangeGhostSpeed());

	PlayState::getSingleton().getRed().setSpeed(level.getPlayerSpeed());
	PlayState::getSingleton().getPink().setSpeed(level.getPinkGhostSpeed());
	PlayState::getSingleton().getBlue().setSpeed(level.getBlueGhostSpeed());
	PlayState::getSingleton().getOrange().setSpeed(level.getOrangeGhostSpeed());

	PlayState::getSingleton().getRed().setSpeed(level.getPlayerSpeed());
	PlayState::getSingleton().getPink().setSpeed(level.getPinkGhostSpeed());
	PlayState::getSingleton().getBlue().setSpeed(level.getBlueGhostSpeed());
	PlayState::getSingleton().getOrange().setSpeed(level.getOrangeGhostSpeed());


	changeState(PlayState::getSingletonPtr());
}

void LoadLevelState::createOverlay()
{
//	//std:://cout<<"**CREANDO OVERLAY"<<std::endl;
//	unsigned int width, height, depth;
//	int left, top;
//
//	Ogre::Overlay *overlay = _overlayManager->getByName("intro");
//	_root->getAutoCreatedWindow()->getMetrics(width, height, depth, left, top);
//
//	overlay->setScale(((float(width) / 100) / 1024) * 100, ((float(height) / 100) / 768) * 100);
//	overlay->show();
}

void LoadLevelState::exit() {}

void LoadLevelState::pause() {}

void LoadLevelState::resume() {}

bool LoadLevelState::frameStarted(const Ogre::FrameEvent& evt)
{
	return true;
}

bool LoadLevelState::frameEnded(const Ogre::FrameEvent& evt)
{
	if (_exitGame)
		return false;

	return true;
}

void LoadLevelState::keyPressed(const OIS::KeyEvent &e)
{
//	if (e.key == OIS::KC_ESCAPE)
//	{
//		_exitGame = true;
//	}
}

void LoadLevelState::keyReleased(const OIS::KeyEvent &e ) {}


void LoadLevelState::mouseMoved(const OIS::MouseEvent &e) {}

void LoadLevelState::locateOverlayMousePointer(int x, int y) {}


void LoadLevelState::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id) {}

void LoadLevelState::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id) {}

LoadLevelState* LoadLevelState::getSingletonPtr()
{
	return msSingleton;
}

LoadLevelState & LoadLevelState::getSingleton ()
{
	assert(msSingleton);
	return *msSingleton;
}

