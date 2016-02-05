/*
 * Pacman.h
 *
 *  Created on: 14/01/2016
 *      Author: alberto
 */

#ifndef PACMAN_H_
#define PACMAN_H_

#include "Character.h"
#include <IceUtil/Thread.h>
#include <IceUtil/Mutex.h>
#include "PowerControlTimer.h"

class PowerControlTimer;

class Pacman : public Character
{
	public:
		Pacman();
		void move(const int key, Ogre::Real deltaT);
		GraphVertex* getClosestAdjacentVertex() const;
		GraphVertex* getLastVertex() const;
		void setDirection(int D);
		PowerControlTimer* getTimer();
		void transformBallUnPower();
	private:
		void DebugPacmanLastVertex();
		void eatBall();
		void eatBallPower();
		void transformBallPower();

		void clearBall();
		PowerControlTimer* _timer;

};

#endif /* PACMAN_H_ */
