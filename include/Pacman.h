/*
 * Pacman.h
 *
 *  Created on: 14/01/2016
 *      Author: alberto
 */

#ifndef PACMAN_H_
#define PACMAN_H_

#include "Character.h"

class Pacman : public Character
{
	public:
		void move(const int key, Ogre::Real deltaT);
		GraphVertex* getClosestAdjacentVertex() const;
		GraphVertex* getLastVertex() const;
		void setDirection(int D);
	private:
		void DebugPacmanLastVertex();
		void eatBall();
		void eatBallPower();
		void transformBallPower();
		void clearBall();
};

#endif /* PACMAN_H_ */
