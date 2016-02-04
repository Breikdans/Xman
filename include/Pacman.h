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
	private:
		void DebugPacmanLastVertex();
};

#endif /* PACMAN_H_ */
