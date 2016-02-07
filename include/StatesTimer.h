/*
 * statesTimer.h
 *
 *  Created on: 07/02/2016
 *      Author: jose
 */

#include <IceUtil/Thread.h>
#ifndef STATESTIMER_H_
#define STATESTIMER_H_

#include <IceUtil/Mutex.h>
#include <string.h>
#include "PlayState.h"
#include "Pacman.h"
#include "Ghost.h"

class Ghost;

class StatesTimer : public IceUtil::Thread
{
	private:
		float _seconds;
		string _name;
	public:
		StatesTimer();
		~StatesTimer();
		void setSecondsLeft(int seconds);
		void changeStatus(EN_ST_CHARACTER s);
		 void DoChangeState(Ghost &g,  EN_ST_CHARACTER s);
		void setName(string name);
		void DoActionTimer(Ghost &g);
		void stopTimer();
		void runTimer();
		void execTimer();

		int getSecondsLeft();
		virtual void run ();
};

#endif /* STATESTIMER_H_ */
