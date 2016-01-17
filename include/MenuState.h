#ifndef MenuState_H
#define MenuState_H

#include <Ogre.h>
#include <OIS/OIS.h>
#include <OgreOverlaySystem.h>
#include <OgreOverlayElement.h>
#include <OgreOverlayManager.h>
#include <CEGUI.h>
#include <RendererModules/Ogre/Renderer.h>

#include "Importer.h"
#include "Scene.h"
#include "GameState.h"

class MenuState : public Ogre::Singleton<MenuState>, public GameState
{
	public:
		MenuState () {}

		void enter ();
		void exit ();
		void pause ();
		void resume ();

		void keyPressed (const OIS::KeyEvent &e);
		void keyReleased (const OIS::KeyEvent &e);
//		void isKeyDown(OIS::KeyCode key) const;

		void mouseMoved (const OIS::MouseEvent &e);
		void mousePressed (const OIS::MouseEvent &e, OIS::MouseButtonID id);
		void mouseReleased (const OIS::MouseEvent &e, OIS::MouseButtonID id);

		bool frameStarted (const Ogre::FrameEvent& evt);
		bool frameEnded (const Ogre::FrameEvent& evt);

		void locateOverlayMousePointer(const int, const int);
		void locateCeguiMousePointer(const int, const int);

		bool getExitMenu() const;
		void setExitMenu(bool exit);

		// Heredados de Ogre::Singleton.
		static MenuState& getSingleton ();
		static MenuState* getSingletonPtr ();

	protected:
		Ogre::Root* 			_root;
		Ogre::SceneManager* 	_sceneMgr;
		Ogre::RenderWindow* 	_renderWindow;
		Ogre::Viewport* 		_viewport;
		Ogre::Camera*			_rotatingCamera;
		Ogre::OverlayManager* 	_overlayManager;
		Ogre::RaySceneQuery *	_raySceneQuery;
		Scene *_scn;

		bool _exitMenu;
		bool _exitGame;

		CEGUI::MouseButton convertMouseButton(OIS::MouseButtonID id);
		void showMenuCegui();
		void createOverlay();
		void createScene();
		void createRotatingCameraThread();

		// Funciones de tratamiento de botones de CEGUI
		bool quit(const CEGUI::EventArgs &e);
		bool newGame(const CEGUI::EventArgs &e);
		bool records(const CEGUI::EventArgs &e);
		bool credits(const CEGUI::EventArgs &e);

};

#endif
