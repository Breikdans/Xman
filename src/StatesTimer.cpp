/*
 * statesTimer.cpp
 *
 *  Created on: 07/02/2016
 *      Author: jose
 */

#include "StatesTimer.h"
#include "Ghost.h"

StatesTimer::StatesTimer()
{
	_seconds=0;
	_running=false;
}

StatesTimer::~StatesTimer(){}

void StatesTimer::run() {
	while(true) {
		IceUtil::ThreadControl::sleep( IceUtil::Time::seconds(1));
		if(_running) {
			execTimer();
		}
	}
}

void StatesTimer::execTimer() {
	std::cout << "Soy el timer del fantasma " << std::endl;
}

void stopTimer() {

}
void runTimer() {

}









