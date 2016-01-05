#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "IntroState.h"
#include "MenuState.h"

template<> IntroState* Ogre::Singleton<IntroState>::msSingleton = 0;

//28 X 31

void IntroState::enter()
{
	initSDL();

	_root 		= Ogre::Root::getSingletonPtr();
	_sceneMgr 	= _root->createSceneManager(Ogre::ST_GENERIC, "SceneManager");
	_mainCamera 	= _sceneMgr->createCamera("mainCamera");
	_viewport 	= _root->getAutoCreatedWindow()->addViewport(_mainCamera);
	_viewport->setBackgroundColour(Ogre::ColourValue(0,0,0));

	_sceneMgr->addRenderQueueListener(new Ogre::OverlaySystem());	// consulta de rayos

	loadResources();

	_overlayManager = Ogre::OverlayManager::getSingletonPtr();
	createOverlay();	// creamos el overlay
	createOverlayMousePointer();	// creamos el overlay
	createCegui();
	loadRecordsFile();

	_TrackManager 			= new TrackManager;
	_SoundFXManager 		= new SoundFXManager;

	_mainMenuTrack			= _TrackManager->load("gameMenu.mp3","General");
	_gameThemeLoop			= _TrackManager->load("gameLoop.mp3","General");
//	_fireBangEffect 		= _SoundFXManager->load("fire.wav","General");
//	_cannonEffect			= _SoundFXManager->load("cannon.wav","General");
//	_waterExplosionEffect	= _SoundFXManager->load("water-explosion.wav","General");
//	_errorEffect			= _SoundFXManager->load("error.wav","General");
//	_finalExplosionEffect	= _SoundFXManager->load("final_explosion.wav","General");

	_exitGame 	= false;
}

void IntroState::initSDL ()
{
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		std::cerr << "SDL: Imposible inicializar Audio!!" << std::endl;
	}

	// Llamar a  SDL_Quit al terminar.
	atexit(SDL_Quit);

	// Inicializando SDL mixer...
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS, 4096) < 0)
	{
		std::cerr << "SDL: Imposible inicializar MIXER!!" << std::endl;
	}

	// Llamar a Mix_CloseAudio al terminar.
	atexit(Mix_CloseAudio);
}

void IntroState::createCegui()
{
	CEGUI::OgreRenderer::bootstrapSystem();
	CEGUI::Scheme::setDefaultResourceGroup("Schemes");
	CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
	CEGUI::Font::setDefaultResourceGroup("Fonts");
	CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");

	CEGUI::FontManager::getSingleton().createAll("*.font", "Fonts");
	CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
	CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultFont("DejaVuSans-12");
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");

}


void IntroState::createOverlayMousePointer()
{
		Ogre::Overlay *mousePointerOverlay = _overlayManager->getByName("mousePointer");
		mousePointerOverlay->show();
}

void IntroState::locateOverlayMousePointer(int x,int y) {
		Ogre::OverlayElement *oe;
		oe = _overlayManager->getOverlayElement("panelMousePointer");
		oe->setLeft(x); oe->setTop(y);
}

void IntroState::createOverlay()
{
	unsigned int width, height, depth;
	int left, top;

	Ogre::Overlay *introOverlay = _overlayManager->getByName("intro");
	_root->getAutoCreatedWindow()->getMetrics(width, height, depth, left, top);

	introOverlay->setScale(((float(width) / 100) / 1024) * 100, ((float(height) / 100) / 768) * 100);
	introOverlay->show();




}


void IntroState::exit()
{
//	Ogre::Overlay *introOverlay = _overlayManager->getByName("intro");
//	introOverlay->hide();

//	Ogre::Overlay *mousePointerOverlay = _overlayManager->getByName("mousePointer");
//		mousePointerOverlay->hide();

	_sceneMgr->clearScene();
	_root->getAutoCreatedWindow()->removeAllViewports();
}


void IntroState::pause() {}

void IntroState::resume() {}

bool IntroState::frameStarted(const Ogre::FrameEvent& evt)
{
	return true;
}

bool IntroState::frameEnded(const Ogre::FrameEvent& evt)
{
	if (_exitGame)
		return false;

	return true;
}

void IntroState::keyPressed(const OIS::KeyEvent &e)
{
	// Transición al siguiente estado. Cualquier tecla
	changeState(MenuState::getSingletonPtr());
}

void IntroState::keyReleased(const OIS::KeyEvent &e )
{
	if (e.key == OIS::KC_ESCAPE)
	{
		_exitGame = true;
	}
}


void IntroState::mouseMoved(const OIS::MouseEvent &e)
{
	// Gestion del overlay (CURSOR)-----------------------------
	// posiciones del puntero del raton en pixeles
	int posx = e.state.X.abs;
	int posy = e.state.Y.abs;

	locateOverlayMousePointer(posx,posy);
}

void IntroState::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	changeState(MenuState::getSingletonPtr());
}

void IntroState::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id) {}

IntroState* IntroState::getSingletonPtr()
{
	return msSingleton;
}

IntroState& IntroState::getSingleton ()
{
	assert(msSingleton);
	return *msSingleton;
}

void IntroState::loadResources()
{
	Ogre::ConfigFile cf;
	cf.load("resources.cfg");	// cargamos el fichero de recursos

//	ejemplo de resources.cfg:
//
//	[General]
//	FileSystem=media
//  Zip=media/celda.zip

	Ogre::ConfigFile::SectionIterator sI = cf.getSectionIterator();	// Iterador de SECCIONES []
	Ogre::String sectionstr;	// Guardara toda la cadena a parsear
	Ogre::String typestr;		// Guardara la Clave
	Ogre::String datastr;		// Guardara el Valor

	while (sI.hasMoreElements())// mientras haya secciones...
	{
		sectionstr = sI.peekNextKey();		// Cogemos nombre de la SECCION, sin avanzar ([General])
		Ogre::ConfigFile::SettingsMultiMap *settings = sI.getNext();// Lee linea para parsear
		Ogre::ConfigFile::SettingsMultiMap::iterator i;				// Iterador para Clave-Valor
		for (i = settings->begin(); i != settings->end(); ++i)
		{
			// cogemos Clave en typestr....Valor en datastr
			typestr = i->first;    datastr = i->second;
			// añadimos la localizacion del recurso, al gestor de recursos...
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation( datastr,		// Clave
																			typestr,		// Valor
																			sectionstr);	// Seccion
		}
	}

	// Decimos al gestor de recursos, que inicialice todos
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

}

void IntroState::fillRecordsFile()
{
	STR_Record str_record;

	std::ofstream file;

	file.open("records.txt");

	str_record.iPuntos = 0;
	str_record.sJugador = "CPU";

	for(int i = 0; i < MAX_PLAYER_RECORDS; i++)
	{
		file << str_record.iPuntos << "_" << str_record.sJugador << std::endl;
		gameRecords.insert(std::make_pair(str_record.iPuntos, str_record.sJugador));
	}

	file.close();
}

void IntroState::loadRecordsFile()
{
	STR_Record str_record;
	int puntos = 0;
	char player[50+1];
	std::ifstream file("records.txt");

	std::string line;

	if (file.is_open())
	{
		while(getline(file, line))
		{
			str_record.iPuntos = 0;
			str_record.sJugador = "";

			sscanf(line.c_str(),"%d_%[^\t\n]",&puntos, player);

			str_record.iPuntos = puntos; str_record.sJugador = player;
			gameRecords.insert(std::make_pair(str_record.iPuntos, str_record.sJugador));
		}

		file.close();
	}
	else
	{
		fillRecordsFile();
	}

	showRecordsFile();
}

void IntroState::showRecordsFile()
{

	std::multimap<unsigned int, std::string>::iterator it = gameRecords.begin();

	for (; it != gameRecords.end(); it++)
	{
		std::cout << " iPuntos: " << it->first << " Jugador: " << it->second << std::endl;
	}
	std::cout << __func__ << " gameRecords.size(): " << gameRecords.size() << std::endl;

}
