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
	//_root = Ogre::Root::getSingletonPtr();

	// Se recupera el gestor de escena y la cámara.
	//_sceneMgr 		= _root->getSceneManager("SceneManager");
	//_mainCamera 	= _sceneMgr->getCamera("mainCamera");
	//_viewport 		= _root->getAutoCreatedWindow()->addViewport(_mainCamera);

	// Metemos una luz ambiental, una luz que no tiene fuente de origen. Ilumina a todos los objetos
	//_sceneMgr->setAmbientLight(Ogre::ColourValue(1, 1, 1));

	//_mainCamera->setPosition(Ogre::Vector3(0, 50, (MAX_ROWS_GRID*CELL_WIDTH) * 2.3));	// posicionamos...
	//_mainCamera->lookAt(Ogre::Vector3(0, 0, (MAX_ROWS_GRID*CELL_WIDTH) / 2));			// enfocamos a 0,0,0
	//_mainCamera->setNearClipDistance(5);		// establecemos plano cercano del frustum
	//_mainCamera->setFarClipDistance(300);		// establecemos plano lejano del frustum

	// Creamos el plano de imagen (lienzo) asociado a la camara
	//_viewport->setBackgroundColour(Ogre::ColourValue(0.0,0.0,0.0));	// color de fondo del viewport(negro)
	//double width 	= _viewport->getActualWidth();		// recogemos ancho del viewport actual
	//double height 	= _viewport->getActualHeight();		// recogemos alto del viewport actual
	//_mainCamera->setAspectRatio(width / height);		// calculamos ratio (4:3 = 1,333 16:9 1,777)

	//_overlayManager = Ogre::OverlayManager::getSingletonPtr();

	// musica del menu
	//IntroState::getSingleton().getMenuTrackPtr()->play();

	//createOverlay();

	int currentLevel = InfoGame::getSingleton().getCurrentLevel();
	LoadLevel( InfoGame::getSingleton().getLevel(currentLevel) );

	_exitGame = false;
}

void LoadLevelState::LoadLevel(const LevelInfo &level)
{
	Scene scene;

	std::string f = level.getPathFolder();
	std::string m = level.getXmlFile();
	//std:://cout << m.c_str();
	std::string fileXML = f + m;
	//Importer::getSingleton().parseScene("output.xml",&scene);
	Importer::getSingleton().parseScene(fileXML.c_str(), &scene);

	InfoGame::getSingleton().setScene(scene);

	PlayState::getSingleton().getPacman().setSpeed(level.getPlayerSpeed());

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

