#include "IntroState.h"
#include "MenuState.h"
#include "LoadLevelState.h"

#include <IceUtil/Thread.h>
#include <IceUtil/Mutex.h>

class rotateCameraThread : public IceUtil::Thread
{
	private:
		Ogre::Camera* _camera;
		Camera* _rotatingCamera;
		unsigned int _currentFrame;
		std::vector<Frame*> _frames;
	public:
		rotateCameraThread (Ogre::Camera *camera, Camera* rotatingCamera)
		{
			_camera = camera;
			_rotatingCamera = rotatingCamera;
			_currentFrame = 0;
			_frames = _rotatingCamera->getPath();
		};
		virtual void run ()
		{
			while(MenuState::getSingleton().getExitMenu() == false)
			{
				Frame F = _rotatingCamera->getFrame(_currentFrame);

				// Cambio de coordenadas BLENDER -> OGRE
				float x = F.getPosition().x;
				float y = F.getPosition().z;
				float z = -F.getPosition().y;
//
//				float qx = F.getRotation().x;
//				float qy = F.getRotation().y;
//				float qz = F.getRotation().z;
//				float qw = F.getRotation().w;


				Ogre::Vector3 V(x,y,z);
//				Ogre::Quaternion Q(qx,qy,qz,qw);
				IceUtil::ThreadControl::sleep( IceUtil::Time::milliSeconds(1000/_rotatingCamera->getFPS()) );



				_camera->setPosition(V);
				_camera->lookAt(0, 0, 0);
				//_camera->setOrientation(Q);

				if (_currentFrame<_frames.size()-1)
				{
					_currentFrame ++;
				}
				else
				{
					_currentFrame = 0;
				}

			}
		};
};

template<> MenuState* Ogre::Singleton<MenuState>::msSingleton = 0;


void MenuState::createRotatingCameraThread()
{
	IceUtil::ThreadPtr t = new rotateCameraThread(_rotatingCamera, _scn->getCamera("rotatingCamera"));
	t->start();
}

void MenuState::enter ()
{

	_root = Ogre::Root::getSingletonPtr();

	// Se recupera el gestor de escena y la cámara.
	_sceneMgr 			= _root->getSceneManager("SceneManager");
	_rotatingCamera 	= _sceneMgr->getCamera("rotatingCamera");
	_renderWindow 		= _root->getAutoCreatedWindow();


	// Metemos una luz ambiental, una luz que no tiene fuente de origen. Ilumina a todos los objetos
	_sceneMgr->setAmbientLight(Ogre::ColourValue(1, 1, 1));

	_rotatingCamera->setPosition(Ogre::Vector3(0, 15, 10));	// posicionamos...
	_rotatingCamera->lookAt(Ogre::Vector3(0, 0, 0));// enfocamos a 0,0,0
	_rotatingCamera->setNearClipDistance(5);		// establecemos plano cercano del frustum
	_rotatingCamera->setFarClipDistance(10000);		// establecemos plano lejano del frustum

	_viewport 		= _renderWindow->addViewport(_rotatingCamera);
	// Creamos el plano de imagen (lienzo) asociado a la camara
	//_viewport->setBackgroundColour(Ogre::ColourValue(0.0,0.0,0.0));	// color de fondo del viewport(negro)
	double width = _viewport->getActualWidth();		// recogemos ancho del viewport actual
	double height = _viewport->getActualHeight();	// recogemos alto del viewport actual
	_rotatingCamera->setAspectRatio(width / height);		// calculamos ratio (4:3 = 1,333 16:9 1,777)

	_overlayManager = Ogre::OverlayManager::getSingletonPtr();

	// musica del menu
	//IntroState::getSingleton().getMenuTrackPtr()->play();

	_scn = new Scene();
	createScene();
	//createOverlay();
	showMenuCegui();
	_exitGame = false;
	_exitMenu = false;
	createRotatingCameraThread();
}


void MenuState::createScene()
{
	Ogre::Light* light;

	// Establecemos sombra
	_sceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
	// Creamos la luz
	light = _sceneMgr->createLight("Light1");
	light->setType(Ogre::Light::LT_DIRECTIONAL);
	light->setDirection(Ogre::Vector3(2,-1,0));
	_sceneMgr->getRootSceneNode()->attachObject(light);

	// creamos nodos de escena para tablero
	Ogre::SceneNode* wallsNode = _sceneMgr->createSceneNode("wallsNode");

	// crea entidades 3d
	Ogre::Entity* entWall = _sceneMgr->createEntity("walls", "walls.mesh");
	wallsNode->attachObject(entWall);
	//wallsNode->pitch(Ogre::Degree(90));


	// Creamos estructura de grafos.....
	// del root cuelga el nodo_water... y de ahi los tableros CPU y Player
	_sceneMgr->getRootSceneNode()->addChild(wallsNode);

	Importer::getSingleton().parseScene("./media/levels/level1/output.xml",_scn);
//	Importer::getSingleton().parseScene("./media/levels/level1/output.xml",_scn);

}

void MenuState::createOverlay()
{
	unsigned int width, height, depth;
	int left, top;

	Ogre::Overlay *overlay = _overlayManager->getByName("menu");
	_root->getAutoCreatedWindow()->getMetrics(width, height, depth, left, top);

	overlay->setScale(((float(width) / 100) / 1024) * 100, ((float(height) / 100) / 768) * 100);
	overlay->show();
}

void MenuState::exit ()
{
	_exitMenu = true;
	// musica del menu STOP
	IntroState::getSingleton().getMenuTrackPtr()->stop();

	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().hide();
	CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->hide();
	Ogre::Overlay *overlay = _overlayManager->getByName("menu");
	overlay->hide();
	_sceneMgr->clearScene();
	_root->getAutoCreatedWindow()->removeAllViewports();
	delete _scn;
}

void MenuState::pause() {}

void MenuState::resume()
{
//	showMenuCegui();
}

bool MenuState::frameStarted(const Ogre::FrameEvent& evt)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectTimePulse(evt.timeSinceLastFrame);

	return true;
}

bool MenuState::frameEnded(const Ogre::FrameEvent& evt)
{
	if (_exitGame)
	{
		exit();
		return false;
	}

	return true;
}

void MenuState::keyPressed(const OIS::KeyEvent &e)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(static_cast<CEGUI::Key::Scan>(e.key));
	CEGUI::System::getSingleton().getDefaultGUIContext().injectChar(e.text);
}

void MenuState::keyReleased(const OIS::KeyEvent &e)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(static_cast<CEGUI::Key::Scan>(e.key));

	if (e.key == OIS::KC_ESCAPE)
	{
		_exitGame = true;
	}
}

//void MenuState::isKeyDown(OIS::KeyCode key) const {}

void MenuState::mouseMoved(const OIS::MouseEvent &e)
{
	// Gestion del overlay (CURSOR)-----------------------------
	// posiciones del puntero del raton en pixeles
	int posx = e.state.X.abs;
	int posy = e.state.Y.abs;

	locateOverlayMousePointer(posx,posy);
	locateCeguiMousePointer(posx,posy);
}

void MenuState::locateOverlayMousePointer(int x,int y)
{
	Ogre::OverlayElement *oe;
	oe = _overlayManager->getOverlayElement("panelMousePointer");
	oe->setLeft(x); oe->setTop(y);
}

void MenuState::locateCeguiMousePointer(int x, int y)
{
	int width = InputManager::getSingleton().getMouse()->getMouseState().width;
	int height = InputManager::getSingleton().getMouse()->getMouseState().height;
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setPosition(CEGUI::Vector2f(x,y));
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(x/float(width),y/float(height));
}

bool MenuState::getExitMenu() const
{
	return _exitMenu;
}

void MenuState::setExitMenu(bool exit)
{
	_exitMenu = exit;
}


void MenuState::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(convertMouseButton(id));
}

void MenuState::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(convertMouseButton(id));
}

MenuState* MenuState::getSingletonPtr ()
{
	return msSingleton;
}

MenuState& MenuState::getSingleton ()
{
	assert(msSingleton);
	return *msSingleton;
}

CEGUI::MouseButton MenuState::convertMouseButton(OIS::MouseButtonID id)
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

void MenuState::showMenuCegui()
{
	//Sheet
	CEGUI::Window* _ceguiSheet = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow","menu_principal");


	//Config Window
	CEGUI::Window* menuWin = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("menu_principal.layout");

	// NEW GAME
	CEGUI::Window* newGameButton = menuWin->getChild("btn_new_game");
	newGameButton->subscribeEvent( CEGUI::PushButton::EventClicked,
							   	   CEGUI::Event::Subscriber(&MenuState::newGame, this));
	// RECORDS
	CEGUI::Window* recordsButton = menuWin->getChild("btn_records");
	recordsButton->subscribeEvent( CEGUI::PushButton::EventClicked,
							   	   CEGUI::Event::Subscriber(&MenuState::records, this));

	// CREDITS
	CEGUI::Window* creditsButton = menuWin->getChild("btn_credits");
	creditsButton->subscribeEvent( CEGUI::PushButton::EventClicked,
							   	   CEGUI::Event::Subscriber(&MenuState::credits, this));
	// QUIT
	CEGUI::Window* exitButton = menuWin->getChild("btn_quit");
	exitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
							   CEGUI::Event::Subscriber(&MenuState::quit, this));

	//Attaching buttons
	_ceguiSheet->addChild(menuWin);
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(_ceguiSheet);

	int posx = InputManager::getSingleton().getMouse()->getMouseState().X.abs;
	int posy = InputManager::getSingleton().getMouse()->getMouseState().Y.abs;
	locateCeguiMousePointer(posx,posy);
}

bool MenuState::newGame(const CEGUI::EventArgs &e)
{
	changeState(LoadLevelState::getSingletonPtr());
	return true;
}

bool MenuState::records(const CEGUI::EventArgs &e)
{
	//pushState(RecordsState::getSingletonPtr());
	return true;
}

bool MenuState::credits(const CEGUI::EventArgs &e)
{
	//pushState(CreditsState::getSingletonPtr());
	return true;
}

bool MenuState::quit(const CEGUI::EventArgs &e)
{
	_exitGame = true;
	return true;
}

