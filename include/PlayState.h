#ifndef PlayState_H
#define PlayState_H

#include <Ogre.h>
#include <OIS/OIS.h>
#include <OgreOverlaySystem.h>
#include <OgreOverlayElement.h>
#include <OgreOverlayManager.h>

#include "GameState.h"

typedef unsigned int uint32;
typedef unsigned short int usint16;


//#ifdef _DEBUG
	#define DEBUG_TRZ(x) x
//#else
//	#define DEBUG_TRZ(x)
//#endif

class PlayState : public Ogre::Singleton<PlayState>, public GameState
{
	public:
		PlayState () {}

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
		static PlayState& getSingleton ();
		static PlayState* getSingletonPtr ();

	protected:
		Ogre::Root* 			_root;
		Ogre::SceneManager* 	_sceneMgr;
		Ogre::RenderWindow* 	_renderWindow;
		Ogre::Viewport* 		_viewport;
		Ogre::Camera* 			_camera;
		Ogre::OverlayManager* 	_overlayManager;
		Ogre::RaySceneQuery *	_raySceneQuery;
		Ogre::Light* 			_light;

		void createScene();
		void createOverlay();
		void hideOverlay();
		void updateInfoOverlay();

		Ogre::Ray setRayQuery(int posx, int posy, uint32 mask);
		void getSelectedNode(uint32 mask, int &x, int &y, std::string &nodeName);

		void showExitMsgCegui();
		bool BotonSi(const CEGUI::EventArgs &e);
		bool BotonNo(const CEGUI::EventArgs &e);
		CEGUI::MouseButton convertMouseButton(OIS::MouseButtonID id);

		bool _exitGame;
};

#endif
