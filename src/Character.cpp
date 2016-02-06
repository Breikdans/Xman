#include "Character.h"

bool Character::_move = true;

Character::Character(EN_ST_CHARACTER st, GraphVertex* lv, Ogre::SceneNode* n, float s, int d, int fd) : _status(st),
																										_lastVertex(lv),
																										_node(n),
																										_speed(s),
																										_direction(d),
																										_faceDirection(fd) {}

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

Ogre::SceneNode* Character::getNodeHome()
{
	return _nodeHome;
}

void Character::setNodeHome(Ogre::SceneNode* n)
{
	_nodeHome = n;
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

EN_ST_CHARACTER Character::getStatus(void) const
{
	return _status;
}

void Character::setStatus(EN_ST_CHARACTER st)
{
	_status = st;
}


int Character::getDirection(void) const
{
	return _direction;
}

void Character::setDirection(int D)
{
	_direction = D;
	setFaceDirection(D);
}

int Character::getFaceDirection(void) const
{
	return _faceDirection;
}

void Character::setFaceDirection(int D)
{
	switch(_faceDirection)
	{
		case UP_PATH:
			switch(D)
			{
				case DOWN_PATH:
					getNode()->yaw(Ogre::Degree(180));
					break;
				case LEFT_PATH:
					getNode()->yaw(Ogre::Degree(90));
					break;
				case RIGHT_PATH:
					getNode()->yaw(Ogre::Degree(-90));
					break;
			}
			break;
		case DOWN_PATH:
			switch(D)
			{
				case UP_PATH:
					getNode()->yaw(Ogre::Degree(180));
					break;
				case LEFT_PATH:
					getNode()->yaw(Ogre::Degree(-90));
					break;
				case RIGHT_PATH:
					getNode()->yaw(Ogre::Degree(90));
					break;
			}
			break;
		case LEFT_PATH:
			switch(D)
			{
				case UP_PATH:
					getNode()->yaw(Ogre::Degree(-90));
					break;
				case DOWN_PATH:
					getNode()->yaw(Ogre::Degree(90));
					break;
				case RIGHT_PATH:
					getNode()->yaw(Ogre::Degree(180));
					break;
			}
			break;
		case RIGHT_PATH:
			switch(D)
			{
				case UP_PATH:
					getNode()->yaw(Ogre::Degree(90));
					break;
				case DOWN_PATH:
					getNode()->yaw(Ogre::Degree(-90));
					break;
				case LEFT_PATH:
					getNode()->yaw(Ogre::Degree(180));
					break;
			}
			break;
	}
	if (D != NONE_PATH)
		_faceDirection = D;
}


void Character::setMove(bool M)
{
	_move = M;
}

bool Character::getMove(void)
{
	return _move;
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

void Character::teleport(GraphVertex* v)
{

	try {
		std::vector<GraphVertex*> teleports;
		int nextTransport = 0;

		if((v->getType() & VE_TRANSPORT_LEFT) == VE_TRANSPORT_LEFT && getDirection() == LEFT_PATH)
			nextTransport = VE_TRANSPORT_RIGHT;
		else if((v->getType() & VE_TRANSPORT_RIGHT) == VE_TRANSPORT_RIGHT && getDirection() == RIGHT_PATH)
			nextTransport = VE_TRANSPORT_LEFT;
		if (nextTransport!=0) {
			teleports = InfoGame::getSingleton().getScene()->getGraph()->getVertexes(nextTransport);
			float x = teleports.at(0)->getPosition().x;
			float y = teleports.at(0)->getPosition().z;
			float z = -(teleports.at(0)->getPosition().y);

			getNode()->setPosition(x,y,z);
			setLastVertex(teleports.at(0));
		}

	}catch(...)  {
		std::cout << "Error en teleport..." << std::endl;
	}

}

