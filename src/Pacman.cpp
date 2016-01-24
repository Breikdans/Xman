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
	 // Obtener las aristas del nodo
			vector<GraphEdge*> e = v->getEdges();
		    vector<GraphEdge*>::iterator it;

			for(it = e.begin() ;it != e.end(); it++)
			{
				// Calcula distancia
				float dest = (*it)->getDestination()->getPosition().y;
				float origin = _lastVertex->getPosition().y;
				if ( dest < origin ) {
					return true;
				}
			}
			return false;
}

bool Pacman::hasVertexDown(GraphVertex* v){
	 // Obtener las aristas del nodo
		vector<GraphEdge*> e = v->getEdges();
	    vector<GraphEdge*>::iterator it;

		for(it = e.begin() ;it != e.end(); it++)
		{
			// Calcula distancia
			float dest = (*it)->getDestination()->getPosition().y;
			float origin = _lastVertex->getPosition().y;
			if ( dest > origin ) {
				return true;
			}
		}
		return false;
}

bool Pacman::hasVertextLeft(GraphVertex* v){
	 // Obtener las aristas del nodo
		vector<GraphEdge*> e = v->getEdges();
	    vector<GraphEdge*>::iterator it;

		for(it = e.begin() ;it != e.end(); it++)
		{
			// Calcula distancia
			float dest = (*it)->getDestination()->getPosition().x;
			float origin = _lastVertex->getPosition().x;
			if ( dest < origin ) {
				return true;
			}
		}
		return false;
}

bool Pacman::hasVertexRight(GraphVertex* v){
	 // Obtener las aristas del nodo
		vector<GraphEdge*> e = v->getEdges();
	    vector<GraphEdge*>::iterator it;

		for(it = e.begin() ;it != e.end(); it++)
		{
			// Calcula distancia
			float dest = (*it)->getDestination()->getPosition().x;
			float origin = _lastVertex->getPosition().x;
			if ( dest > origin ) {
				return true;
			}
		}
		return false;
}

void Pacman::move(OIS::KeyCode k) {

    std:: cout << k << endl;

	if (isIntoVertex(_lastVertex))
	{
		// Si está cerca de un vértice puede cambiar en todas direcciones, siempre que exista un nodo adyacente
		if (k == OIS::KC_UP)
		{
			if (hasVertexUp(_lastVertex)) {
				_direction = UP;
			}

		}
		else if (k== OIS::KC_DOWN)
		{
			if (hasVertexDown(_lastVertex)) {
				_direction = DOWN;
			}

		}
		else if (k == OIS::KC_LEFT)
		{
			if (hasVertextLeft(_lastVertex)) {
				_direction = LEFT;
			}
		}
		else if (k == OIS::KC_RIGHT)
		{
			if (hasVertexRight(_lastVertex)) {
				_direction = RIGHT;
			}
		}

	}



		_speed = InfoGame::getSingleton().getLevel(InfoGame::getSingleton().getCurrentLevel()).getPlayerSpeed();
		if (_direction==UP) {
			_nodePacman->translate(0,-_speed,0);
		} else if (_direction==DOWN) {
			_nodePacman->translate(0,_speed,0);
		}
		else if(_direction==LEFT)
		{
			_nodePacman->translate(-_speed,0,0);
		}
		else if(_direction == RIGHT) {
			_nodePacman->translate(_speed,0,0);
		}




}

bool Pacman::isIntoVertex(GraphVertex* v) {

	// Pregunta si está cerca del mismo vértice
	float xDiff = std::abs(_nodePacman->getPosition().x - v->getPosition().x);
	float yDiff = std::abs(_nodePacman->getPosition().y - v->getPosition().y);
	if (xDiff <= EPSILON && yDiff <= EPSILON) {
			return true;
	}

	// En sus adyacentes
	vector<GraphEdge*> e = v->getEdges();
	vector<GraphEdge*>::iterator it;

	for(it = e.begin() ;it != e.end(); it++)
	{
		float xxDiff =(*it)->getDestination()->getPosition().x;
		float yyDiff =(*it)->getDestination()->getPosition().y;
		if (xxDiff <= EPSILON && yyDiff <= EPSILON) {
				   _lastVertex = (*it)->getDestination();
					return true;
		}

	}


	return false;

}
