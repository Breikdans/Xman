#ifndef PlayState_H
#define PlayState_H

#include <iostream>
#include <cstdio>

#include <Ogre.h>
#include <OIS/OIS.h>
#include <OgreOverlaySystem.h>
#include <OgreOverlayElement.h>
#include <OgreOverlayManager.h>

#include <CEGUI.h>

//#include <boost/asio.hpp>
//#include <boost/bind.hpp>
//#include <boost/date_time/posix_time/posix_time.hpp>

#include "IntroState.h"
#include "MenuState.h"
#include "PauseState.h"
//#include "EndGameState.h"
#include "InfoGame.h"

#include "Pacman.h"
#include "GameState.h"
#include "Ghost.h"


typedef unsigned int uint32;
typedef unsigned short int usint16;



//#ifdef _DEBUG
	#define DEBUG_TRZ(x) x
//#else
//	#define DEBUG_TRZ(x)
//#endif

class musicInitTimer : public IceUtil::Thread
{
	private:
		int _seconds;
	public:
		musicInitTimer ()
		{
			_seconds=4;
		};
		virtual void run ()
		{
			Character::setMove(false);
		    IntroState::getSingleton().getBeginningFXPtr()->play();
			while(_seconds>0)
			{
					IceUtil::ThreadControl::sleep(IceUtil::Time::milliSeconds(1000));
					_seconds--;
			}

			Character::setMove(true);
			IntroState::getSingleton().getMainThemeTrackPtr()->play();
		};
};

class PlayState : public Ogre::Singleton<PlayState>, public GameState
{
	public:
		PlayState () {	};
		~PlayState() { };
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

		void updateInfoOverlay();

		// Heredados de Ogre::Singleton.
		static PlayState& getSingleton ();
		static PlayState* getSingletonPtr ();

		Pacman& getPacman();
		Ghost& getRed();
		Ghost& getPink();
		Ghost& getBlue();
		Ghost& getOrange();

		Ogre::SceneManager* getSceneMgr();
	protected:
		Ogre::Root* 			_root;
		Ogre::SceneManager* 	_sceneMgr;
		Ogre::RenderWindow* 	_renderWindow;
		Ogre::Viewport* 		_viewport;
		Ogre::Camera* 			_camera;
		Ogre::OverlayManager* 	_overlayManager;
		Ogre::RaySceneQuery *	_raySceneQuery;
		Ogre::Light* 			_light;


		int						_lastKeyPressed;

		Pacman					_pacman;
		Ghost					_red;
		Ghost					_pink;
		Ghost					_blue;
		Ghost					_orange;

		musicInitTimer*  _musicInitTimer;

		void InitGame();
		void createScene();
		void initNodeCharacter(GraphVertex* gVertex, std::string name, Character* character, Ogre::SceneNode* scNode);
		void startCharacters();
		void setInitialPosition(GraphVertex* gVertex, Character* character);
		void createOverlay();
		void hideOverlay();


		Ogre::Ray setRayQuery(int posx, int posy, uint32 mask);
		void getSelectedNode(uint32 mask, int &x, int &y, std::string &nodeName);

		void showExitMsgCegui();
		bool BotonSi(const CEGUI::EventArgs &e);
		bool BotonNo(const CEGUI::EventArgs &e);
		CEGUI::MouseButton convertMouseButton(OIS::MouseButtonID id);

		void locateOverlayMousePointer(int x,int y);
		void locateCeguiMousePointer(int x, int y);
		void locateMainCamera();

		bool _exitGame;
};

#endif
