#include "PowerControlTimer.h"


void PowerControlTimer::setSecondsLeft(int seconds) {
			_seconds = seconds;
			if (!_started)
				start();
}

int PowerControlTimer::getSecondsLeft() { return _seconds; }

void PowerControlTimer::run ()
{
	while(true)
	{
		IceUtil::ThreadControl::sleep( IceUtil::Time::seconds(1));
		if (_seconds>=0)
		{
			_seconds--;
			std::cout << "PoweControlTimer  left " << _seconds << " seconds " << std::endl;
		}

		if (_seconds==0)
		{
			std::cout << "PoweControlTimer finished " << std::endl;
			try {
				if(PlayState::getSingleton().getRed().getStatus()==ST_SCARED)
					PlayState::getSingleton().getRed().transformNormal();

				if(PlayState::getSingleton().getPink().getStatus()==ST_SCARED)
					PlayState::getSingleton().getPink().transformNormal();

				if(PlayState::getSingleton().getBlue().getStatus()==ST_SCARED)
					PlayState::getSingleton().getBlue().transformNormal();

				if(PlayState::getSingleton().getOrange().getStatus()==ST_SCARED)
					PlayState::getSingleton().getOrange().transformNormal();
			} catch(...) {
				std::cout << "PowerControlTime -> Err no se ha encontrado al pacman" << std::endl;
			}
		}
	}
};

