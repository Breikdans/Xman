#include "Pacman.h"



void Pacman::setPosition(Ogre::Vector3 pos) {
	_nodePacman->setPosition(pos.x,pos.y,pos.z);
}

void Pacman::setPosition(float x=0, float y=0, float z=0) {
	_nodePacman->setPosition(x,y,z);
}

Ogre::Vector3 Pacman::getPosition() {

	return _nodePacman->getPosition();

}

Ogre::SceneNode* Pacman::getNode() {
	return _nodePacman;
}

void Pacman::setNode(Ogre::SceneNode* n) {
	_nodePacman = n;
}

void Pacman::setLastVertex(GraphVertex *v) {
	_lastVertex = v;
}

GraphVertex* Pacman::getLastVertex() {
	return _lastVertex;
}

float Pacman::getSpeed() {
	return _speed;
}

void Pacman::setSpeed(float s) {
	_speed = s;
}


void Pacman::move(const int k, Ogre::Real deltaT)
{
	if (isIntoVertex(_lastVertex))
	{	// Esta dentro de un vertice
		switch (k)
		{
			case LEFT_PATH:
				if (_lastVertex->getMaskPaths() & LEFT_PATH)
				{
					_direction = LEFT_PATH;
				}
				else if (!(_lastVertex->getMaskPaths() & _direction))
				{
					_direction = NONE_PATH;
				}
				break;

			case RIGHT_PATH:
				if (_lastVertex->getMaskPaths() & RIGHT_PATH)
				{
					_direction = RIGHT_PATH;
				}
				else if (!(_lastVertex->getMaskPaths() & _direction))
				{
					_direction = NONE_PATH;
				}
				break;

			case UP_PATH:
				if (_lastVertex->getMaskPaths() & UP_PATH)
				{
					_direction = UP_PATH;
				}
				else if (!(_lastVertex->getMaskPaths() & _direction))
				{
					_direction = NONE_PATH;
				}
				break;

			case DOWN_PATH:
				if (_lastVertex->getMaskPaths() & DOWN_PATH)
				{
					_direction = DOWN_PATH;
				}
				else if (!(_lastVertex->getMaskPaths() & _direction))
				{
					_direction = NONE_PATH;
				}
				break;
//				_nodePacman->setPosition(_lastVertex->getPosition().x,_lastVertex->getPosition().z,_nodePacman->getPosition().z);
		}
	}
	else
	{	// Esta en medio del camino
		switch (_direction)
		{
			case LEFT_PATH:
				if(k == RIGHT_PATH) _direction = RIGHT_PATH;
				break;
			case RIGHT_PATH:
				if(k == LEFT_PATH) _direction = LEFT_PATH;
				break;
			case UP_PATH:
				if(k == DOWN_PATH) _direction = DOWN_PATH;
				break;
			case DOWN_PATH:
				if(k == UP_PATH) _direction = UP_PATH;
				break;
		}
	}

	// MOVER
	float s = InfoGame::getSingleton().getLevel(InfoGame::getSingleton().getCurrentLevel()).getPlayerSpeed();
	switch(_direction)
	{
		case LEFT_PATH:
			_nodePacman->translate(-s * deltaT,0,0);
			break;
		case RIGHT_PATH:
			_nodePacman->translate(s * deltaT,0,0);
			break;
		case UP_PATH:
			_nodePacman->translate(0,0,-s * deltaT);
			//std::cout << "UP! y: " << -s << std::endl;
			break;
		case DOWN_PATH:
			_nodePacman->translate(0,0,s * deltaT);
			//std::cout << "DOWN! y: " << s << std::endl;
			break;
		case NONE_PATH:
			_nodePacman->translate(0,0,0);
			break;
	}

}

bool Pacman::isIntoVertex(GraphVertex* v) {

	bool result=false;

	// Pregunta si está cerca del mismo vértice
	float xDiff = std::abs(_nodePacman->getPosition().x - v->getPosition().x);
	float yDiff = std::abs(_nodePacman->getPosition().z - (-v->getPosition().y));

	//std::cout << _nodePacman->getPosition().x << ", " << _nodePacman->getPosition().y

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
			float xxDiff =std::abs(_nodePacman->getPosition().x - (*it)->getDestination()->getPosition().x);
			float yyDiff =std::abs(_nodePacman->getPosition().z - (-(*it)->getDestination()->getPosition().y));


			if (xxDiff <= EPSILON && yyDiff <= EPSILON)
			{
				_lastVertex = (*it)->getDestination();
				result = true;
			}
		}
	}

	if (result==true)
	{
		std::cout << "ESTOY EN EL NODO " << _lastVertex->getIndex() << std::endl;
	}
	return result;

}
