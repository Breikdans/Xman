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
		Pacman(Ogre::Vector3 pos = Ogre::Vector3(0,0,0)) : Character(pos) {
			//cout << "NO ME LO CREO " << endl;
		}

		void move(const int k, Ogre::Real deltaT);

};

#endif /* PACMAN_H_ */
