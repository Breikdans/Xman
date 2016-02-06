#include "PlayState.h"
#include "DeathState.h"
#include "IntroState.h"
#include "MusicDeathTimer.h"

template<> DeathState* Ogre::Singleton<DeathState>::msSingleton = 0;

void DeathState::enter ()
{
	InfoGame::getSingleton().decLifes();

	_musicDeathTimer = new MusicDeathTimer();
	_musicDeathTimer->start();
	
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

void DeathState::keyPressed(const OIS::KeyEvent &e)
{
	if(e.key == OIS::KC_ESCAPE)
	{
		changeState(PlayState::getSingletonPtr());
	}

}

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

