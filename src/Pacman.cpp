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
					setDirection(LEFT_PATH);
				}
				else if (!(_lastVertex->getMaskPaths() & getDirection()))
				{
					setDirection(NONE_PATH);
				}
				break;

			case RIGHT_PATH:
				if (_lastVertex->getMaskPaths() & RIGHT_PATH)
				{
					setDirection(RIGHT_PATH);
				}
				else if (!(_lastVertex->getMaskPaths() & getDirection()))
				{
					setDirection(NONE_PATH);
				}
				break;

			case UP_PATH:
				if (_lastVertex->getMaskPaths() & UP_PATH)
				{
					setDirection(UP_PATH);
				}
				else if (!(_lastVertex->getMaskPaths() & getDirection()))
				{
					setDirection(NONE_PATH);
				}
				break;

			case DOWN_PATH:
				if (_lastVertex->getMaskPaths() & DOWN_PATH)
				{
					setDirection(DOWN_PATH);
				}
				else if (!(_lastVertex->getMaskPaths() & getDirection()))
				{
					setDirection(NONE_PATH);
				}
				break;
//				_node->setPosition(_lastVertex->getPosition().x,_lastVertex->getPosition().z,_node->getPosition().z);
		}
	}
	else
	{	// Esta en medio del camino
		switch (getDirection())
		{
			case LEFT_PATH:
				if(key == RIGHT_PATH) setDirection(RIGHT_PATH);
				break;
			case RIGHT_PATH:
				if(key == LEFT_PATH) setDirection(LEFT_PATH);
				break;
			case UP_PATH:
				if(key == DOWN_PATH) setDirection(DOWN_PATH);
				break;
			case DOWN_PATH:
				if(key == UP_PATH) setDirection(UP_PATH);
				break;
		}
	}

	// MOVER
	float s = InfoGame::getSingleton().getLevel(InfoGame::getSingleton().getCurrentLevel()).getPlayerSpeed();
	switch(getDirection())
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

void Pacman::setDirection(int D)
{
	static int lastDirection = DOWN_PATH;
//cout << "PACMAN!!! DIRECCION: " << lastDirection << " NUEVA: " << D << endl;
	switch(lastDirection)
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
		lastDirection = D;

	_direction = D;
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
//DebugPacmanLastVertex();
	return _lastVertex;
}

void Pacman::DebugPacmanLastVertex()
{
	static GraphVertex* oldVertex = _lastVertex;
	if(oldVertex != _lastVertex)
	{
		cout << endl << "\t\tPACMAN: " << _lastVertex->getIndex() << endl;
		oldVertex = _lastVertex;
	}
}
