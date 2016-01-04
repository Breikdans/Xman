#ifndef LoadLevelState_H
#define LoadLevelState_H

#include <Ogre.h>
#include <OIS/OIS.h>
#include <iterator>
#include <map>
#include "TrackManager.h"
#include "SoundFXManager.h"
#include "GameState.h"


class LoadLevelState : public Ogre::Singleton<LoadLevelState>, public GameState
{
	public:
		LoadLevelState() {}

		void enter ();
		void exit ();
		void pause ();
		void resume ();

		void keyPressed (const OIS::KeyEvent &e);
		void keyReleased (const OIS::KeyEvent &e);

		void mouseMoved (const OIS::MouseEvent &e);
		void mousePressed (const OIS::MouseEvent &e, OIS::MouseButtonID id);
		void mouseReleased (const OIS::MouseEvent &e, OIS::MouseButtonID id);

		void locateOverlayMousePointer(const int, const int);

		bool frameStarted (const Ogre::FrameEvent& evt);
		bool frameEnded (const Ogre::FrameEvent& evt);

		// Heredados de Ogre::Singleton.
		static LoadLevelState& getSingleton ();
		static LoadLevelState* getSingletonPtr ();

		protected:
		Ogre::Root* 						_root;
		Ogre::SceneManager* 		_sceneMgr;
		Ogre::Viewport* 				_viewport;
		Ogre::Camera* 					_mainCamera;
		Ogre::Camera*     				_firstPersonCamera;
		Ogre::Camera* 					_rotatingCamera;
		Ogre::OverlayManager* 	_overlayManager;


		void createOverlay();

		bool _exitGame;
};

#endif
