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


bool Pacman::hasVertexUp(GraphVertex* v) {
			return false;
}

bool Pacman::hasVertexDown(GraphVertex* v){
		return false;
}

bool Pacman::hasVertextLeft(GraphVertex* v){
	 // Obtener las aristas del nodo
		vector<GraphEdge*> e = v->getEdges();
	    vector<GraphEdge*>::iterator it;

	    bool result=false;

		for(it = e.begin() ;it != e.end(); it++)
		{
			// Calcula distancia
			float x_dest = (*it)->getDestination()->getPosition().x;
			float x_origin = _lastVertex->getPosition().x;

			float y_dest = (*it)->getDestination()->getPosition().y;
			float y_origin = _nodePacman->getPosition().y;
			float y_Diff = std::abs(y_dest-y_origin);

			if ( x_dest < x_origin && y_Diff <= EPSILON ) {
				std::cout << "LEFT si tiene" << y_Diff<<endl;
				result = true;
			}
		}
		return result;
}

bool Pacman::hasVertexRight(GraphVertex* v){
	return false;
}

void Pacman::move(const int k) {


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

		}
	}
	else
	{	// Esta en medio del camino

	}

	// MOVER
	float s = InfoGame::getSingleton().getLevel(InfoGame::getSingleton().getCurrentLevel()).getPlayerSpeed();
	switch(_direction)
	{
		case LEFT_PATH:
			_nodePacman->translate(-s,0,0);
			break;
		case RIGHT_PATH:
			_nodePacman->translate(s,0,0);
			break;
		case UP_PATH:
			_nodePacman->translate(0,-s,0);
			std::cout << "UP! y: " << -s << std::endl;
			break;
		case DOWN_PATH:
			_nodePacman->translate(0,s,0);
			std::cout << "DOWN! y: " << s << std::endl;
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
	float yDiff = std::abs(_nodePacman->getPosition().y - v->getPosition().y);
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
					float yyDiff =std::abs(_nodePacman->getPosition().y - (*it)->getDestination()->getPosition().y);


					if (xxDiff <= EPSILON && yyDiff <= EPSILON)
					{
							   _lastVertex = (*it)->getDestination();
								result = true;
					}

				}
	}

	if (result==true) {
		std::cout << "ESTOY EN EL NODO " << _lastVertex->getIndex() << std::endl;
	}
	return result;

}
