#ifndef PlayState_H
#define PlayState_H

#include <Ogre.h>
#include <OIS/OIS.h>
#include <OgreOverlaySystem.h>
#include <OgreOverlayElement.h>
#include <OgreOverlayManager.h>

#include <CEGUI.h>

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

class PlayState : public Ogre::Singleton<PlayState>, public GameState
{
	public:
		PlayState () {	};

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

		// Heredados de Ogre::Singleton.
		static PlayState& getSingleton ();
		static PlayState* getSingletonPtr ();

		void initCharacterPosition(GraphVertex* gVertex, std::string name, Character* character, Ogre::SceneNode* scNode);

		const Pacman& getPacman() const;
		Ogre::SceneManager* getSceneMgr();

		Pacman					_pacman;

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


		Ghost					_red;
		Ghost					_pink;
		Ghost					_blue;
		Ghost					_orange;

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

		void locateOverlayMousePointer(int x,int y);
		void locateCeguiMousePointer(int x, int y);
		void locateMainCamera();

		bool _exitGame;
};

#endif
