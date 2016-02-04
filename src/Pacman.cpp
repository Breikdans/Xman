#include "Pacman.h"


void Pacman::move(const int key, Ogre::Real deltaT)
{
	if (isIntoVertex(_lastVertex))
	{	// Esta dentro de un vertice
		switch (key)
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
//				_node->setPosition(_lastVertex->getPosition().x,_lastVertex->getPosition().z,_node->getPosition().z);
		}
	}
	else
	{	// Esta en medio del camino
		switch (_direction)
		{
			case LEFT_PATH:
				if(key == RIGHT_PATH) _direction = RIGHT_PATH;
				break;
			case RIGHT_PATH:
				if(key == LEFT_PATH) _direction = LEFT_PATH;
				break;
			case UP_PATH:
				if(key == DOWN_PATH) _direction = DOWN_PATH;
				break;
			case DOWN_PATH:
				if(key == UP_PATH) _direction = UP_PATH;
				break;
		}
	}

	// MOVER
	float s = InfoGame::getSingleton().getLevel(InfoGame::getSingleton().getCurrentLevel()).getPlayerSpeed();
	switch(_direction)
	{
		case LEFT_PATH:
			_node->translate(-s * deltaT,0,0);
			break;
		case RIGHT_PATH:
			_node->translate(s * deltaT,0,0);
			break;
		case UP_PATH:
			_node->translate(0,0,-s * deltaT);
			////std:://cout << "UP! y: " << -s << std::endl;
			break;
		case DOWN_PATH:
			_node->translate(0,0,s * deltaT);
			////std:://cout << "DOWN! y: " << s << std::endl;
			break;
		case NONE_PATH:
			_node->translate(0,0,0);
			break;
	}
}

GraphVertex* Pacman::getClosestAdjacentVertex() const
{
	std::vector<GraphEdge*> edges = _lastVertex->getEdges();
	std::vector<GraphEdge*>::iterator it = edges.begin();

	GraphVertex * closestVertex = _lastVertex;

	float x = getPosition().x;
	float y = getPosition().z;

	float valorMenor = 0.0f;
	float valor		 = 0.0f;

	for(; it != edges.end(); it++)
	{
		valor = abs(x - (*it)->getDestination()->getPosition().x) + abs(y - (*it)->getDestination()->getPosition().y);
		if (valor < valorMenor)
		{
			valorMenor = valor;
			closestVertex = (*it)->getDestination();
		}
	}

	return closestVertex;
}

GraphVertex* Pacman::getLastVertex() const
{
	static GraphVertex* oldVertex = _lastVertex;
	if(oldVertex != _lastVertex)
	{
		cout << endl << "\t\tPACMAN: " << _lastVertex->getIndex() << endl;
		oldVertex = _lastVertex;
	}
		return _lastVertex;
}

