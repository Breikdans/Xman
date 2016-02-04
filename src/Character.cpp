#include "Character.h"

Character::Character(EN_ST_CHARACTER st, GraphVertex* lv, Ogre::SceneNode* n, float s, int d) : _status(st),
																							    _lastVertex(lv),
																							    _node(n),
																							    _speed(s),
																							    _direction(d) {}

Character::Character(const Character& C)
{
	*this = C;
}

Character& Character::operator= (const Character &C)
{
	_status 	= C._status;
	_speed		= C._speed;
	_direction	= C._direction;
//	_lastVertex = new GraphVertex;	// no creamos uno, ya que el puntero se usa para apuntar al que nos pasen (un vertex del grafo)
	_lastVertex = C._lastVertex;
//	_node		= new Ogre::SceneNode(C._node);
	if (_node)
		delete _node;
	_node		= new Ogre::SceneNode(*C._node);
	*(_node) 	= *(C._node);

	return *this;
}

Character::~Character()
{
	// este no le liberamos, ya que el _lastVertex nos le pasan del grafo, el es el que lo tendra que liberar
//	if(_lastVertex)
//		delete _lastVertex;

	if(_node)
		delete _node;
}

void Character::setPosition(Ogre::Vector3 pos)
{
	_node->setPosition(pos.x,pos.y,pos.z);
}

void Character::setPosition(float x=0, float y=0, float z=0)
{
	_node->setPosition(x,y,z);
}

Ogre::Vector3 Character::getPosition() const
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

float Character::getSpeed()
{
	return _speed;
}

void Character::setSpeed(float s)
{
	_speed = s;
}

int Character::getDirection(void) const
{
	return _direction;
}

bool Character::isIntoVertex(GraphVertex* v)
{
	const float EPSILON = 0.03f;

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
