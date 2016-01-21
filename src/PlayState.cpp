#include <iostream>
#include <cstdio>
//#include <boost/asio.hpp>
//#include <boost/bind.hpp>
//#include <boost/date_time/posix_time/posix_time.hpp>
#include "IntroState.h"
#include "MenuState.h"
#include "PlayState.h"
//#include "PauseState.h"
//#include "EndGameState.h"
#include "InfoGame.h"

template<> PlayState* Ogre::Singleton<PlayState>::msSingleton = 0;

void PlayState::enter ()
{
	_root = Ogre::Root::getSingletonPtr();

	// Se recupera el gestor de escena y la cámara.
	_sceneMgr 		= _root->getSceneManager("SceneManager");
	_renderWindow 	= _root->getAutoCreatedWindow();
	_camera	= _sceneMgr->getCamera("mainCamera");
	_viewport 		= _renderWindow->addViewport(_camera);


	// Metemos una luz ambiental, una luz que no tiene fuente de origen. Ilumina a todos los objetos
	_sceneMgr->setAmbientLight(Ogre::ColourValue(1, 1, 1));

	//_sceneMgr->addRenderQueueListener(new Ogre::OverlaySystem());	// consulta de rayos
	locateMainCamera();
	_camera->setNearClipDistance(5);				// establecemos plano cercano del frustum
	_camera->setFarClipDistance(300);				// establecemos plano lejano del frustum;

	// Creamos el plano de imagen (lienzo) asociado a la camara
	_viewport->setBackgroundColour(Ogre::ColourValue(0.0,0.0,0.0));	// color de fondo del viewport(negro)
	double width = _viewport->getActualWidth();						// recogemos ancho del viewport actual
	double height = _viewport->getActualHeight();					// recogemos alto del viewport actual
	_camera->setAspectRatio(width / height);						// calculamos ratio (4:3 = 1,333 16:9 1,777)

	_overlayManager = Ogre::OverlayManager::getSingletonPtr();

	// musica del juego
//	IntroState::getSingleton().getMainThemeTrackPtr()->play();


	createScene();		// creamos la escena
	//createOverlay();	// creamos el overlay


	// Creamos nuestra query de rayos
	//_raySceneQuery = _sceneMgr->createRayQuery(Ogre::Ray());

	_exitGame 		= false;
}

/**
 * Coloca la camara en la posicion del primer frame que venga con la misma en el xml.
 * Cada nivel vendrá con su cámara principal colocada donde quiera que sea.
 */
void PlayState::locateMainCamera() {

	Camera *cam = InfoGame::getSingleton().getScene()->getCamera("mainCamera");
	Frame frame = cam->getFrame(0);
	float x = frame.getPosition().x;
	float y = frame.getPosition().z;
	float z = -frame.getPosition().y;

	_camera->setPosition(Ogre::Vector3(x,y,z));	// posicionamos...
	_camera->lookAt(Ogre::Vector3(0, 0, 0));		// enfocamos a 0,0,0

}

void PlayState::exit ()
{
	// paramos musica del juego
	//IntroState::getSingleton().getMainThemeTrackPtr()->stop();

	//_sceneMgr->destroyQuery(_raySceneQuery);
	// si lo descomentamos se elimina la escena y las particulas del fuego se quedan paradas...
//	_sceneMgr->clearScene();
//	_root->getAutoCreatedWindow()->removeAllViewports();
}

void PlayState::pause()
{
	// PAUSAR MP3 no funciona con SDL2
	// paramos musica del juego porque el Pause de SDL no esta funcionando bien con MP3
	//IntroState::getSingleton().getMainThemeTrackPtr()->stop();
}

void PlayState::resume()
{
	// continuamos musica del juego
	//IntroState::getSingleton().getMainThemeTrackPtr()->play();
}

bool PlayState::frameStarted(const Ogre::FrameEvent& evt)
{

	// movimiento de camara luego quitar
//	Ogre::Vector3 vt(0,0,0);	Ogre::Real tSpeed = 1.0;
//	if(InputManager::getSingleton().getKeyboard()->isKeyDown(OIS::KC_UP))		vt+=Ogre::Vector3(0,0,-1);
//	if(InputManager::getSingleton().getKeyboard()->isKeyDown(OIS::KC_DOWN))		vt+=Ogre::Vector3(0,0,1);
//	if(InputManager::getSingleton().getKeyboard()->isKeyDown(OIS::KC_LEFT))		vt+=Ogre::Vector3(-1,0,0);
//	if(InputManager::getSingleton().getKeyboard()->isKeyDown(OIS::KC_RIGHT))	vt+=Ogre::Vector3(1,0,0);
//	_camera->moveRelative(vt * 0.1 * tSpeed);

	return true;
}

bool PlayState::frameEnded(const Ogre::FrameEvent& evt)
{
	if (_exitGame)
		return false;

	return true;
}

void PlayState::keyPressed(const OIS::KeyEvent &e)
{
//DEBUG_TRZ(std::cout << __FILE__ << " " << __func__ << " KEY PRESSED: " << e.key << std::endl;)
//
//	// Tecla p --> PauseState.
//	if (e.key == OIS::KC_P)
//	{
////		pushState(PauseState::getSingletonPtr());
//	}
//	else if(e.key == OIS::KC_ESCAPE)
//	{
//		showExitMsgCegui();
//	}

//#ifdef _DEBUG
	// movimiento de camara luego quitar
//#endif

}

void PlayState::keyReleased(const OIS::KeyEvent &e)
{
//DEBUG_TRZ(std::cout << __FILE__ << " " << __func__ << " KEY RELEASED: " << e.key << std::endl;)
}

void PlayState::mouseMoved(const OIS::MouseEvent &e)
{
	// Gestion del overlay (CURSOR)-----------------------------
	// posiciones del puntero del raton en pixeles
	int posx = e.state.X.abs;
	int posy = e.state.Y.abs;

	locateOverlayMousePointer(posx,posy);
//	locateCeguiMousePointer(posx,posy);

//	CEGUI::Vector2f mousePos = CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().getPosition();
//	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setPosition(CEGUI::Vector2f(e.state.X.abs,e.state.Y.abs));
//	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(mousePos.d_x/float(e.state.width), mousePos.d_y/float(e.state.height));

}

void PlayState::locateOverlayMousePointer(int x,int y)
{
	Ogre::OverlayElement *oe;
	oe = _overlayManager->getOverlayElement("panelMousePointer");
	oe->setLeft(x); oe->setTop(y);

}


void PlayState::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	//CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(convertMouseButton(id));
}

void PlayState::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	//CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(convertMouseButton(id));
}

PlayState* PlayState::getSingletonPtr ()
{
	return msSingleton;
}

PlayState& PlayState::getSingleton ()
{ 
	assert(msSingleton);
	return *msSingleton;
}

void PlayState::createScene()
{
	// Crea la entidad y el nodo de escena principal
	Ogre::Entity *stageMap =_sceneMgr->createEntity("entStageMap",InfoGame::getSingleton().getCurrentMeshFile());
	Ogre::SceneNode* 	mainNode = _sceneMgr->createSceneNode("nodStageMap");
	mainNode->attachObject(stageMap);
	_sceneMgr->getRootSceneNode()->addChild(mainNode);

	// Pintar bolas
	std::vector<SceneBall*> balls = InfoGame::getSingleton().getScene()->getBalls();
	std::vector<SceneBall*>::iterator it;
	for (it = balls.begin(); it != balls.end(); ++it)
	{

			SceneBall* b = (*it);
			float x = b->getPosition().x;
			float y = b->getPosition().z;
			float z = -b->getPosition().y;

			std::stringstream nodeName;
			nodeName << "ball_" << b->getIndex();
			Ogre::Entity *entBall =_sceneMgr->createEntity(nodeName.str(),"ball.mesh");

			Ogre::SceneNode* ballNode = _sceneMgr->createSceneNode(nodeName.str());
			ballNode->setPosition(x,y,z);
			ballNode->attachObject(entBall);
			mainNode->addChild(ballNode);

	}
}


Ogre::Ray PlayState::setRayQuery(int posx, int posy, uint32 mask)
{
	Ogre::Ray rayMouse = _camera->getCameraToViewportRay(posx/float(_renderWindow->getWidth()),
												   	     posy/float(_renderWindow->getHeight()));
	_raySceneQuery->setRay(rayMouse);
	_raySceneQuery->setSortByDistance(true);
	_raySceneQuery->setQueryMask(mask);
	return (rayMouse);
}

void PlayState::getSelectedNode(uint32 mask,			///< ENTRADA. Mascara de objetos a enviar a la query
								int &x,					///< ENTRADA/SALIDA. E: Pixels en X del raton para el rayo. S: X del nodo en coordenadas grid
								int &y,					///< ENTRADA/SALIDA. E: Pixels en Y del raton para el rayo. S: X del nodo en coordenadas grid
								std::string &nodeName	///< SALIDA. Nombre del nodo seleccionado
								)
{
//	setRayQuery(x, y, mask);			// establecemos query...
//	Ogre::RaySceneQueryResult &result = _raySceneQuery->execute();
//	Ogre::RaySceneQueryResult::iterator it;
//	it = result.begin();
//	if (it != result.end())	// recogemos la primera ocurrencia de la query
//	{
//		int xtemp=0,ytemp=0,i_st=-1;
//
//		nodeName = it->movable->getParentSceneNode()->getName();	// cogemos el nombre del nodo seleccionado con el rayo
//		i_st = std::sscanf(nodeName.c_str(),"%*[^0-9]%d%*[^0-9]%d",&xtemp, &ytemp);
//		if(i_st == 2)
//		{
//			x=xtemp, y=ytemp;
//		}
//	}
}

void PlayState::createOverlay()
{

	_overlayManager = Ogre::OverlayManager::getSingletonPtr();

//	Ogre::Overlay *overlay_cpu = _overlayManager->getByName("panel_cpu");
//	overlay_cpu->show();
//	Ogre::Overlay *overlay_player = _overlayManager->getByName("panel_player");
//	overlay_player->show();
}

void PlayState::hideOverlay()
{
	//_overlayManager = Ogre::OverlayManager::getSingletonPtr();
//	Ogre::Overlay *overlay_cpu = _overlayManager->getByName("panel_cpu");
//	overlay_cpu->hide();
//	Ogre::Overlay *overlay_player = _overlayManager->getByName("panel_player");
//	overlay_player->hide();
}

void PlayState::showExitMsgCegui()
{
//	//Sheet
//	CEGUI::Window* _ceguiSheet = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow","salir");
//
//	//Config Window
//	CEGUI::Window* exitMsg = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("salir.layout");
//
//	exitMsg->getChild("lbl_salir")->setText("[font='major_shift-18'] Abandonar Partida?");
//
//	// OK
//	CEGUI::Window* siButton = exitMsg->getChild("btn_si");
//	siButton->subscribeEvent( CEGUI::PushButton::EventClicked,
//							  CEGUI::Event::Subscriber(&PlayState::BotonSi, this));
//
//	CEGUI::Window* noButton = exitMsg->getChild("btn_no");
//	noButton->subscribeEvent( CEGUI::PushButton::EventClicked,
//							  CEGUI::Event::Subscriber(&PlayState::BotonNo, this));
//
//	//Attaching buttons
//	_ceguiSheet->addChild(exitMsg);
//	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(_ceguiSheet);
//
//	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().show();
}

bool PlayState::BotonSi(const CEGUI::EventArgs &e)
{
//	hideOverlay();
//	CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->hide();
//	_sceneMgr->clearScene();
//	_root->getAutoCreatedWindow()->removeAllViewports();
//
//	changeState(MenuState::getSingletonPtr());
	return true;
}

bool PlayState::BotonNo(const CEGUI::EventArgs &e)
{
//	CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->hide();
//	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().hide();

	return true;
}

CEGUI::MouseButton PlayState::convertMouseButton(OIS::MouseButtonID id)
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
