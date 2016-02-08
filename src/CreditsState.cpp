
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

bool CreditsState::frameEnded(const Ogre::FrameEvent& evt)
{
	if (_exitGame)
		return false;

	return true;
}

void CreditsState::keyPressed(const OIS::KeyEvent &e)
{
	// Tecla p --> Estado anterior.
	if (e.key == OIS::KC_P)
	{
		popState();
	}
}

void CreditsState::keyReleased(const OIS::KeyEvent &e) {}

//void CreditsState::isKeyDown(OIS::KeyCode key) const {}

void CreditsState::mouseMoved(const OIS::MouseEvent &e)
{
	// para igualar punteros de raton en posicion 0,0
	CEGUI::Vector2f mousePos = CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().getPosition();
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setPosition(CEGUI::Vector2f(e.state.X.abs,e.state.Y.abs));
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(mousePos.d_x/float(e.state.width), mousePos.d_y/float(e.state.height));
}

void CreditsState::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(convertMouseButton(id));
}

void CreditsState::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(convertMouseButton(id));
}

CreditsState* CreditsState::getSingletonPtr ()
{
	return msSingleton;
}

CreditsState& CreditsState::getSingleton ()
{ 
	assert(msSingleton);
	return *msSingleton;
}

void CreditsState::showCreditsMsgCegui()
{
	//Sheet
	CEGUI::Window* _ceguiSheet = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow","credits");

	//Config Window
	CEGUI::Window* endMsgCredits = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("credits.layout");

	endMsgCredits->getChild("lbl_jose")->setText("[font='major_shift-18'] Jose Martinez Cano");

	endMsgCredits->getChild("lbl_alberto")->setText("[font='major_shift-18'] Alberto Cerrada Jimenez");


	// OK
	CEGUI::Window* okButton = endMsgCredits->getChild("btn_ok");
	okButton->subscribeEvent( CEGUI::PushButton::EventClicked,
							  CEGUI::Event::Subscriber(&CreditsState::BotonOk, this));

	//Attaching buttons
	_ceguiSheet->addChild(endMsgCredits);
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(_ceguiSheet);

}

bool CreditsState::BotonOk(const CEGUI::EventArgs &e)
{
	popState();
	return true;
}

CEGUI::MouseButton CreditsState::convertMouseButton(OIS::MouseButtonID id)
{
	CEGUI::MouseButton ceguiId;
	switch(id)
	{
		case OIS::MB_Left:
			ceguiId = CEGUI::LeftButton;
			break;
		case OIS::MB_Right:
			ceguiId = CEGUI::RightButton;
			break;
		case OIS::MB_Middle:
			ceguiId = CEGUI::MiddleButton;
			break;
		default:
			ceguiId = CEGUI::LeftButton;
	}
	return ceguiId;
}

void CreditsState::exit()
{
	Ogre::Overlay *introOverlay = _overlayManager->getByName("credits");
	introOverlay->hide();

//	Ogre::Overlay *mousePointerOverlay = _overlayManager->getByName("mousePointer");
//		mousePointerOverlay->hide();

	_sceneMgr->clearScene();
	_root->getAutoCreatedWindow()->removeAllViewports();
}


void CreditsState::pause() {}

void CreditsState::resume() {}

bool CreditsState::frameStarted(const Ogre::FrameEvent& evt)
{
	return true;
}


