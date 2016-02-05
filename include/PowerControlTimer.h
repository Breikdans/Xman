#ifndef POWERCONTROLTIMER_H_
#define POWERCONTROLTIMER_H_

#include <IceUtil/Thread.h>
#include <IceUtil/Mutex.h>
#include <string.h>
#include "PlayState.h"
#include "Pacman.h"

class PowerControlTimer : public IceUtil::Thread
{
	private:
		int _seconds;
		string _name;
	public:
		PowerControlTimer() {
			_seconds = 0;
		}
		void setSecondsLeft(int seconds);
		void setName(string name);

		int getSecondsLeft();
		virtual void run ();
};

#endif /* POWERCONTROLTIMER_H_ */
