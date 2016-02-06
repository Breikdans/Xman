#include "PowerControlTimer.h"


void PowerControlTimer::setSecondsLeft(int seconds) {
			_seconds = seconds;
			if (!_started)
				start();
}

int PowerControlTimer::getSecondsLeft() { return _seconds; }

void PowerControlTimer::run ()
{
			while(true) {
				IceUtil::ThreadControl::sleep( IceUtil::Time::seconds(1));
				if (_seconds>=0) {
					_seconds--;
					std::cout << "PoweControlTimer  left " << _seconds << " seconds " << std::endl;
				}

				if (_seconds==0) {
					std::cout << "PoweControlTimer finished " << std::endl;
					try {
						PlayState::getSingleton().getPacman().transformBallUnPower();
						PlayState::getSingleton().getRed().transformNormal();
						PlayState::getSingleton().getPink().transformNormal();
						PlayState::getSingleton().getBlue().transformNormal();
						PlayState::getSingleton().getOrange().transformNormal();
					} catch(...) {
						std::cout << "PowerControlTime -> Err no se ha encontrado al pacman" << std::endl;
					}
				}

			}
};

