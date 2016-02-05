#ifndef IntroState_H
#define IntroState_H

#include <Ogre.h>
#include <OIS/OIS.h>
#include <iterator>
#include <map>
#include "TrackManager.h"
#include "SoundFXManager.h"
#include "GameState.h"

typedef struct
{
	unsigned int iPuntos;
	std::string sJugador;
}STR_Record;

#define MAX_PLAYER_RECORDS		10

class IntroState : public Ogre::Singleton<IntroState>, public GameState
{
	public:
		IntroState() {}
		~IntroState();

		void enter ();
		void exit ();
		void pause ();
		void resume ();

		void keyPressed (const OIS::KeyEvent &e);
		void keyReleased (const OIS::KeyEvent &e);

		void mouseMoved (const OIS::MouseEvent &e);
		void mousePressed (const OIS::MouseEvent &e, OIS::MouseButtonID id);
		void mouseReleased (const OIS::MouseEvent &e, OIS::MouseButtonID id);

		bool frameStarted (const Ogre::FrameEvent& evt);
		bool frameEnded (const Ogre::FrameEvent& evt);

		std::multimap<unsigned int, std::string> gameRecords;

		// Heredados de Ogre::Singleton.
		static IntroState& getSingleton ();
		static IntroState* getSingletonPtr ();

		TrackPtr 	getMenuTrackPtr () 			{ return _mainMenuTrack; }
		TrackPtr 	getMainThemeTrackPtr () 	{ return _pacmanSirenLoop; }

		SoundFXPtr 	getBeginningFXPtr () 		{ return _pacmanBeginningEffect; }
		SoundFXPtr 	getChompFXPtr () 			{ return _pacmanChompEffect; }
		SoundFXPtr 	getDeathFXPtr () 			{ return _pacmanDeathEffect; }
		SoundFXPtr 	getEatFruitFXPtr () 		{ return _pacmanEatFruitEffect; }
		SoundFXPtr 	getEatGhostFXPtr () 		{ return _pacmanEatGhostEffect; }
		SoundFXPtr 	getExtraPacFXPtr () 		{ return _pacmanExtraPacEffect; }
		SoundFXPtr 	getInterFXPtr () 			{ return _pacmanInterEffect; }

	protected:
		Ogre::Root* 				_root;
		Ogre::SceneManager* 		_sceneMgr;
		Ogre::Viewport* 			_viewport;
		Ogre::Camera* 				_mainCamera;
		Ogre::Camera*     			_firstPersonCamera;
		Ogre::Camera* 				_rotatingCamera;
		Ogre::OverlayManager* 		_overlayManager;

		// Manejadores del sonido.
		TrackManager* 				_TrackManager;
		SoundFXManager* 			_SoundFXManager;

		TrackPtr 					_mainMenuTrack;				// puntero inteligente
		TrackPtr 					_pacmanSirenLoop;			// puntero inteligente

		SoundFXPtr 					_pacmanBeginningEffect;		// puntero inteligente
		SoundFXPtr 					_pacmanChompEffect;			// puntero inteligente
		SoundFXPtr 					_pacmanDeathEffect;			// puntero inteligente
		SoundFXPtr 					_pacmanEatFruitEffect;		// puntero inteligente
		SoundFXPtr					_pacmanEatGhostEffect;		// puntero inteligente
		SoundFXPtr 					_pacmanExtraPacEffect;		// puntero inteligente
		SoundFXPtr					_pacmanInterEffect;			// puntero inteligente


		void createOverlay();
		void createOverlayMousePointer();
		void locateOverlayMousePointer(const int, const int);
		void loadResources();
		void createCegui();
		void initSDL();

		void loadRecordsFile();
		void fillRecordsFile();
		void showRecordsFile();

		bool _exitGame;
};

#endif
