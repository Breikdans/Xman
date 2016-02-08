#include "PlayState.h"
#include "DeathState.h"
#include "IntroState.h"

class MusicDeathTimer : public IceUtil::Thread
{
	private:
		int _seconds;
	public:
		MusicDeathTimer ()
		{
			_seconds=2;
		};
		virtual void run ()
		{
			Character::setMove(false);
			IceUtil::ThreadControl::sleep(IceUtil::Time::milliSeconds(500));
		    IntroState::getSingleton().getDeathFXPtr()->play();
			while(_seconds>0)
			{
				IceUtil::ThreadControl::sleep(IceUtil::Time::milliSeconds(1000));
				_seconds--;
			}
			Character::setMove(true);
			//	if(InfoGame::getSingleton().getLifes() == 0)
			//		changeState(EndState::getSingletonPtr());
			//	else
//				{
					IntroState::getSingleton().getMainThemeTrackPtr()->play();
					DeathState::getSingleton().changeState(PlayState::getSingletonPtr());

//				}
//			DeathState::getSingleton().changeState(PlayState::getSingletonPtr());
		};
};
