#include "Pacman.h"


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
//				_node->setPosition(_lastVertex->getPosition().x,_lastVertex->getPosition().z,_node->getPosition().z);
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
			_node->translate(-s * deltaT,0,0);
			break;
		case RIGHT_PATH:
			_node->translate(s * deltaT,0,0);
			break;
		case UP_PATH:
			_node->translate(0,0,-s * deltaT);
			//std::cout << "UP! y: " << -s << std::endl;
			break;
		case DOWN_PATH:
			_node->translate(0,0,s * deltaT);
			//std::cout << "DOWN! y: " << s << std::endl;
			break;
		case NONE_PATH:
			_node->translate(0,0,0);
			break;
	}

}

