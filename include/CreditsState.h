#ifndef CreditsState_H
#define CreditsState_H

#include <Ogre.h>
#include <OIS/OIS.h>
#include <CEGUI.h>

#include "GameState.h"

class CreditsState : public Ogre::Singleton<CreditsState>, public GameState
{
	public:
		CreditsState() {}

		void enter ();
		void exit ();
		void pause ();
		void resume ();

		void keyPressed (const OIS::KeyEvent &e);
		void keyReleased (const OIS::KeyEvent &e);
//		void isKeyDown(OIS::KeyCode key) const;
		void createOverlay();

		void mouseMoved (const OIS::MouseEvent &e);
		void mousePressed (const OIS::MouseEvent &e, OIS::MouseButtonID id);
		void mouseReleased (const OIS::MouseEvent &e, OIS::MouseButtonID id);

		bool frameStarted (const Ogre::FrameEvent& evt);
		bool frameEnded (const Ogre::FrameEvent& evt);

		// Heredados de Ogre::Singleton.
		static CreditsState& getSingleton ();
		static CreditsState* getSingletonPtr ();

		void locateOverlayMousePointer(int x,int y);

	protected:
		Ogre::Root* 			_root;
		Ogre::SceneManager* 	_sceneMgr;
		Ogre::RenderWindow* 	_renderWindow;
		Ogre::Viewport* 		_viewport;
		Ogre::Camera*			_rotatingCamera;
		Ogre::OverlayManager* 	_overlayManager;
		Ogre::RaySceneQuery *	_raySceneQuery;


		bool _exitGame;

		CEGUI::MouseButton convertMouseButton(OIS::MouseButtonID id);
		void showCreditsMsgCegui();
		bool BotonOk(const CEGUI::EventArgs &e);
};

#endif
