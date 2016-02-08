
#include "PlayState.h"
#include "MenuState.h"
#include "CreditsState.h"

template<> CreditsState* Ogre::Singleton<CreditsState>::msSingleton = 0;

void CreditsState::enter ()
{
	_root				= Ogre::Root::getSingletonPtr();

	// Se recupera el gestor de escena y la cámara.
	_sceneMgr 			= _root->getSceneManager("SceneManager");
//	_rotatingCamera 	= _sceneMgr->getCamera("rotatingCamera");
//	_viewport 			= _root->getAutoCreatedWindow()->addViewport(_rotatingCamera);
//
//	_rotatingCamera->setPosition(Ogre::Vector3(0, 15, 10));	// posicionamos...
//	_rotatingCamera->lookAt(Ogre::Vector3(0, 0, 0));// enfocamos a 0,0,0
//	_rotatingCamera->setNearClipDistance(5);		// establecemos plano cercano del frustum
//	_rotatingCamera->setFarClipDistance(10000);		// establecemos plano lejano del frustum
//
//	_viewport 		= _renderWindow->addViewport(_rotatingCamera);
	_overlayManager = Ogre::OverlayManager::getSingletonPtr();

	//_scn = new Scene();
	//createScene();
	createOverlay();
	//showMenuCegui();
	_exitGame = false;
	//_exitMenu = false;
}

void CreditsState::createOverlay()
{
	unsigned int width, height, depth;
	int left, top;

	Ogre::Overlay *overlay = _overlayManager->getByName("credits");
	_root->getAutoCreatedWindow()->getMetrics(width, height, depth, left, top);

	overlay->setScale(((float(width) / 100) / 1024) * 100, ((float(height) / 100) / 768) * 100);
	overlay->show();
}

void CreditsState::locateOverlayMousePointer(int x,int y)
{
	Ogre::OverlayElement *oe;
	oe = _overlayManager->getOverlayElement("panelMousePointer");
	oe->setLeft(x); oe->setTop(y);
}

bool CreditsState::frameEnded(const Ogre::FrameEvent& evt)
{
	if (_exitGame)
		return false;

	return true;
}

void CreditsState::keyPressed(const OIS::KeyEvent &e) {}

void CreditsState::keyReleased(const OIS::KeyEvent &e) {}

void CreditsState::mouseMoved(const OIS::MouseEvent &e)
{
	// Gestion del overlay (CURSOR)-----------------------------
	// posiciones del puntero del raton en pixeles
	int posx = e.state.X.abs;
	int posy = e.state.Y.abs;

	locateOverlayMousePointer(posx,posy);
}

void CreditsState::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	popState();
}

void CreditsState::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id) {}

CreditsState* CreditsState::getSingletonPtr ()
{
	return msSingleton;
}

CreditsState& CreditsState::getSingleton ()
{ 
	assert(msSingleton);
	return *msSingleton;
}


void CreditsState::exit()
{
	Ogre::Overlay *introOverlay = _overlayManager->getByName("credits");
	introOverlay->hide();
}


void CreditsState::pause() {}

void CreditsState::resume() {}

bool CreditsState::frameStarted(const Ogre::FrameEvent& evt)
{
	return true;
}


