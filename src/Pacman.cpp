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

void Pacman::setLastVertex(GraphVertex*v) {
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

void Pacman::move(OIS::KeyCode) {


	if (isNearVertex())
	{	// Si está cerca de un vértice puede cambiar en todas direcciones, siempre que exista un nodo adyacente

	}
	else
	{ // Si está en medio de un camino, sólo puede cambiar de dirección

	}
}

bool Pacman::isNearVertex() {

	bool result=false;
	// Pregunta si está cerca del mismo vértice
	float xDiff = std::abs(_nodePacman->getPosition().x - _lastVertex->getPosition().x);
	float yDiff = std::abs(_nodePacman->getPosition().y - _lastVertex->getPosition().y);

	if (xDiff <= EPSILON && yDiff <= EPSILON) {
		result=true;

	}
//	cout << "xDiff " << xDiff << " yDiff"<< yDiff << endl;
//	cout << "nodePacman.x " << _nodePacman->getPosition().x << " _lastVertex.x"<< _lastVertex->getPosition().x << endl;
//	cout << "nodePacman.y " << _nodePacman->getPosition().y << " _lastVertex.y"<< _lastVertex->getPosition().y << endl;

	if (result==true) 	std::cout << "is In Vertex " << std::endl;
	return result;
}
