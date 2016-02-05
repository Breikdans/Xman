#include "PlayState.h"
#include "DeathState.h"

template<> DeathState* Ogre::Singleton<DeathState>::msSingleton = 0;

void DeathState::enter ()
{
	//_root = Ogre::Root::getSingletonPtr();

	// Se recupera el gestor de escena y la cámara.
//	_sceneMgr = _root->getSceneManager("SceneManager");
//	_camera = _sceneMgr->getCamera("mainCamera");
//	_viewport = _root->getAutoCreatedWindow()->getViewport(0);
//
//	_viewport->setBackgroundColour(Ogre::ColourValue(0.0, 1.0, 0.0));

	// musica del menu
	//IntroState::getSingleton().getMenuTrackPtr()->play();

	//_overlayManager = Ogre::OverlayManager::getSingletonPtr();
//	Ogre::Overlay *overlay_player = _overlayManager->getByName("panel_pause");
//	overlay_player->show();


	_exitGame = false;
}

void DeathState::exit ()
{
	// paramos musica del menu
	//IntroState::getSingleton().getMenuTrackPtr()->stop();

//	Ogre::Overlay *overlay_player = _overlayManager->getByName("panel_pause");
//	overlay_player->hide();
}

void DeathState::pause () {}

void DeathState::resume () {}

bool DeathState::frameStarted(const Ogre::FrameEvent& evt)
{
	return true;
}

bool DeathState::frameEnded(const Ogre::FrameEvent& evt)
{
	if (_exitGame)
		return false;

	return true;
}

void DeathState::keyPressed(const OIS::KeyEvent &e) {}

void DeathState::keyReleased(const OIS::KeyEvent &e) {}

void DeathState::mouseMoved(const OIS::MouseEvent &e)
{
}

void DeathState::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{

}

void DeathState::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id) {}

DeathState* DeathState::getSingletonPtr ()
{
	return msSingleton;
}

DeathState& DeathState::getSingleton ()
{ 
	assert(msSingleton);
	return *msSingleton;
}

