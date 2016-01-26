/*
 * Pacman.h
 *
 *  Created on: 14/01/2016
 *      Author: alberto
 */

#ifndef PACMAN_H_
#define PACMAN_H_

#include <Ogre.h>
#include "GraphVertex.h"
#include "GraphEdge.h"
#include <OIS/OIS.h>
#include "Graph.h"
#include "InfoGame.h"

const float EPSILON = 0.03;

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

class Pacman
{
	public:
		Pacman(Ogre::Vector3 pos = Ogre::Vector3(0, 0.62, 0), EN_ST_PACMAN st = ST_NORMAL) {
			_speed = 0;
			_direction = NONE_PATH;
		}
		void setPosition(Ogre::Vector3 pos);
		void setPosition(float x, float y,  float z);
		Ogre::Vector3 getPosition();

		void setLastVertex(GraphVertex* v);
		GraphVertex *getLastVertex();

		bool isIntoVertex(GraphVertex* v);

		void setSpeed(float s);
		float getSpeed();

		void move(const int k);

		Ogre::SceneNode* getNode();
		void setNode(Ogre::SceneNode*);


	private:
		EN_ST_PACMAN  _status;
		GraphVertex* _lastVertex;
		Ogre::SceneNode*	_nodePacman;
		float _speed;
		int _direction;

};

#endif /* PACMAN_H_ */
