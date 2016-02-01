#include "Character.h"

Character::Character(Ogre::Vector3 pos)
{
	_speed = 0;
	_direction = NONE_PATH;
}


void Character::setPosition(Ogre::Vector3 pos)
{
	_node->setPosition(pos.x,pos.y,pos.z);
}

void Character::setPosition(float x=0, float y=0, float z=0)
{
	_node->setPosition(x,y,z);
}

Ogre::Vector3 Character::getPosition()
{

	return _node->getPosition();

}

Ogre::SceneNode* Character::getNode()
{
	return _node;
}

void Character::setNode(Ogre::SceneNode* n)
{
	_node = n;
}

void Character::setLastVertex(GraphVertex *v)
{
	_lastVertex = v;
}

GraphVertex* Character::getLastVertex() const
{
	return _lastVertex;
}

float Character::getSpeed()
{
	return _speed;
}

void Character::setSpeed(float s)
{
	_speed = s;
}


bool Character::isIntoVertex(GraphVertex* v)
{

	bool result=false;

	// Pregunta si está cerca del mismo vértice
	float xDiff = std::abs(_node->getPosition().x - v->getPosition().x);
	float yDiff = std::abs(_node->getPosition().z - (-v->getPosition().y));



	if (xDiff <= EPSILON && yDiff <= EPSILON)
	{
		result = true;

		_lastVertex  = v;
	}

	if (result==false)
	{
		// En sus adyacentes
		vector<GraphEdge*> e = v->getEdges();
		vector<GraphEdge*>::iterator it;

		for(it = e.begin() ;it != e.end(); it++)
		{
			float xxDiff =std::abs(_node->getPosition().x - (*it)->getDestination()->getPosition().x);
			float yyDiff =std::abs(_node->getPosition().z - (-(*it)->getDestination()->getPosition().y));


			if (xxDiff <= EPSILON && yyDiff <= EPSILON)
			{
				_lastVertex = (*it)->getDestination();

				result = true;
			}
		}
	}

	return result;
}
