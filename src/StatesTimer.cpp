/*
 * statesTimer.cpp
 *
 *  Created on: 07/02/2016
 *      Author: jose
 */

#include "StatesTimer.h"
#include "Character.h"
#include "Ghost.h"

StatesTimer::StatesTimer()
{
	_seconds=0;
	_running=false;
}

StatesTimer::~StatesTimer(){}

void StatesTimer::run() {
	while(true) {
		IceUtil::ThreadControl::sleep( IceUtil::Time::milliSeconds(1000));
		if (Character::getMove()==true) {
			if(_running==true) {
				execTimer();
			}
		}
	}
}

void StatesTimer::SetHome(Ghost &g) {
	_seconds = g.getTimeScatter();
	g.setStatus(ST_SCATTER);
	g.transformNormal();
	g.setDirection(NONE_PATH);
	g.setFaceDirection(DOWN_PATH);
	g.setLastVertex(g.getHomeVertex());
}

void StatesTimer::DoActionTimer(Ghost &g) {

	EN_ST_CHARACTER current = g.getStatus();
	_seconds--;
	if (_seconds<=0) {
		switch(current) {
		case ST_HOME:	// Vamos a SCATTER
			SetHome(g);
			break;
		case ST_CHASE:	// Vamos a SCATTER
			_seconds = g.getTimeScatter();
			g.setStatus(ST_SCATTER);
			g.transformNormal();
			break;
		case ST_SCARED:	// Vamos a SCATTER
			if (g.getStatus()!=ST_HOME && g.getStatus()!=ST_DEAD) {
				_seconds = g.getTimeScatter();
				g.setStatus(ST_SCATTER);
				g.transformNormal();
			}
			break;
		case ST_SCATTER:
			_seconds = g.getTimeScatter();
			g.setStatus(ST_CHASE);
			break;
		case ST_DEAD:
			g.transformDead();
			break;
		}
	}

	//std::cout << "Soy el timer del fantasma " <<  g.getName() << " y estoy "<< g.getStatus() << " por " << _seconds  << " segundos" << std::endl;
}

void StatesTimer::execTimer() {


	if (_name=="red"){
		DoActionTimer(PlayState::getSingleton().getRed());
	} else if(_name=="blue") {
		DoActionTimer(PlayState::getSingleton().getBlue());
	} else if(_name=="orange"){
		DoActionTimer(PlayState::getSingleton().getOrange());
	}else if(_name=="pink") {
		DoActionTimer(PlayState::getSingleton().getPink());
	}

}

void StatesTimer::changeStatus(EN_ST_CHARACTER s) {

	if (_name=="red"){
		DoChangeState(PlayState::getSingleton().getRed(),s);
	} else if(_name=="blue") {
		DoChangeState(PlayState::getSingleton().getBlue(),s);
	} else if(_name=="orange"){
		DoChangeState(PlayState::getSingleton().getOrange(),s);
	}else if(_name=="pink") {
		DoChangeState(PlayState::getSingleton().getPink(),s);
	}

}

void StatesTimer::DoChangeState(Ghost &g,  EN_ST_CHARACTER s) {
	switch(s) {
		case ST_HOME:	// Vamos a SCATTER
			SetHome(g);
			break;
		case ST_CHASE:
			_seconds = g.getTimeChase();
			g.transformNormal();
			g.setStatus(s);
			break;
		case ST_SCARED:	// Vamos a SCATTER
			if (g.getStatus()!=ST_HOME && g.getStatus()!=ST_DEAD)
			{
				_seconds = g.getTimeScared();
				g.transformScared();
				g.setStatus(s);
			}
			break;
		case ST_SCATTER:
			_seconds = g.getTimeScatter();
			g.transformNormal();
			g.setStatus(s);
			break;
		case ST_DEAD:
			g.transformDead();
			g.setStatus(s);
			break;
	}

	std::cout << " cambiar a estado. segundos " << _seconds << std::endl;
}

void StatesTimer::setName(string name) {
	_name = name;
}

void StatesTimer::setSecondsLeft(int seconds) {
	_seconds = seconds;
}

void StatesTimer::stopTimer() {
	_running=false;
}
void StatesTimer::runTimer() {
	_running=true;
}









