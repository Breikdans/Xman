#ifndef DeathState_H
#define DeathState_H

#include <Ogre.h>
#include <OIS/OIS.h>

#include "GameState.h"
#include "PlayState.h"

class MusicDeathTimer;

class DeathState : public Ogre::Singleton<DeathState>, public GameState
{
	public:
		DeathState() {}

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

		// Heredados de Ogre::Singleton.
		static DeathState& getSingleton ();
		static DeathState* getSingletonPtr ();

	protected:
			bool _exitGame;
			MusicDeathTimer *_musicDeathTimer;
};





#endif
