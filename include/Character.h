/*
 * Character.h
 *
 *  Created on: 14/01/2016
 *      Author: Jose
 */

#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <Ogre.h>
#include "GraphVertex.h"
#include "GraphEdge.h"
#include <OIS/OIS.h>
#include "Graph.h"
#include "InfoGame.h"

const float EPSILON = 0.03f;

typedef enum
{
	ST_NORMAL = 0,		// Pacman: Normal
	ST_POWERED,			// Pacman: Power!
	ST_CHASE,			// Ghost:  Perseguir
	ST_SCATTER,			// Ghost:  Dispersarse cada uno a su esquina
	ST_SCARED,			// Ghost:  Asustado!
}EN_ST_CHARACTER;

class Character
{
	public:
		Character(EN_ST_CHARACTER st = ST_NORMAL, GraphVertex* lv = 0, Ogre::SceneNode* n = 0, float s = 0.3f, int d = NONE_PATH);
		Character(const Character& C);
		Character& operator= (const Character &C);
		~Character();

		void setPosition(Ogre::Vector3 pos);
		void setPosition(float x, float y,  float z);
		Ogre::Vector3 getPosition();

		void setLastVertex(GraphVertex* v);
		GraphVertex *getLastVertex() const;

		bool isIntoVertex(GraphVertex* v);

		void setSpeed(float s);
		float getSpeed();


		Ogre::SceneNode* getNode();
		void setNode(Ogre::SceneNode*);

		int getDirection(void) const;

	protected:
		EN_ST_CHARACTER  	_status;
		GraphVertex* 		_lastVertex;
		Ogre::SceneNode*	_node;
		float 				_speed;
		int 				_direction;
};

#endif /* CHARACTER_H_ */
