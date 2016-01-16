/*
 * Pacman.h
 *
 *  Created on: 14/01/2016
 *      Author: alberto
 */

#ifndef PACMAN_H_
#define PACMAN_H_

#include <Ogre.h>

typedef enum
{
	ST_CHASE = 0,		// Perseguir
	ST_SCATTER,			// Dispersarse cada uno a su esquina
	ST_SCARED,			// Asustado
}EN_ST_GHOSTS;

typedef enum
{
	ST_NORMAL = 0,		// Normal
	ST_POWERED			// Power!!
}EN_ST_PACMAN;

class Pacman : public Ogre::Singleton<Pacman>
{
	public:
		Pacman(Ogre::Vector3 pos = Ogre::Vector3(0, 0.62, 0), EN_ST_PACMAN st = EN_NORMAL);
	private:
		Ogre::Vector3 _position;
		EN_ST_PACMAN  _status;
};

#endif /* PACMAN_H_ */
