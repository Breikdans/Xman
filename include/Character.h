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

typedef enum
{
	ST_HOME = 0,		// Ghost:  En casa
	ST_SCATTER,			// Ghost:  Dispersarse cada uno a su esquina
	ST_CHASE,			// Ghost:  Perseguir
	ST_SCARED,			// Ghost:  Asustado!
	ST_DEAD,				// Personaje Muerto!
}EN_ST_CHARACTER;

class Character
{
	public:
		Character(std::string na = "", EN_ST_CHARACTER st = ST_HOME, GraphVertex* lv = 0, Ogre::SceneNode* n = 0,
					float s = 0.3f,
					float sd = 7.0f,
				  int d = NONE_PATH, int fd = DOWN_PATH);
		Character(const Character& C);
		Character& operator= (const Character &C);
		~Character();

		void setPosition(Ogre::Vector3 pos);
		void setPosition(float x, float y,  float z);
		Ogre::Vector3 getPosition() const;

		void setLastVertex(GraphVertex* v);
		virtual GraphVertex *getLastVertex() const = 0;
		void setHomeVertex(GraphVertex* n);
		GraphVertex* getHomeVertex() const;

		bool isIntoVertex(GraphVertex* v);
		bool isIntoVertexTotal(GraphVertex* v);

		void setSpeed(float s);
		float getSpeed();
		float getSpeedDead();
		float getSpeedWalk();

		EN_ST_CHARACTER getStatus(void) const;
		void setStatus(EN_ST_CHARACTER st);

		Ogre::SceneNode* getNode();
		void setNode(Ogre::SceneNode*);

		int getDirection(void) const;
		void setDirection(int D);

		int getFaceDirection(void) const;
		void setFaceDirection(int D);

		static void setMove(bool M);
		static bool getMove(void);

		void setName(std::string name);
		std::string getName(void) const;
	protected:
		std::string			_name;
		EN_ST_CHARACTER  	_status;
		GraphVertex* 		_lastVertex;
		GraphVertex*		_homeVertex;
		Ogre::SceneNode*	_node;
		float 				_speed;
		float 				_speedWalk;
		float 				_speedDead;
		int 				_direction;
		int					_faceDirection;

		static bool 		_move;

		void teleport(GraphVertex* v);
};

#endif /* CHARACTER_H_ */
