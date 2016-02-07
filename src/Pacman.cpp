#include "IntroState.h"
#include "PlayState.h"
#include "Pacman.h"

Pacman::Pacman() {
	_timer=new PowerControlTimer();
}

Pacman::~Pacman() {
	delete _timer;
}

void Pacman::move(const int key, Ogre::Real deltaT)
{
	if (isIntoVertex(getLastVertex()))
	{	// Esta dentro de un vertice

//		if( (getLastVertex()->getType() & VE_BALL) == VE_BALL )
//			eatBall();

		if( (getLastVertex()->getType() & VE_BALLPOWER) == VE_BALLPOWER )
			eatBallPower();

//		if( InfoGame::getSingleton().getBallsLeft() == 0 )
//			changeState(NextLevelState::getSingletonPtr());
//

		if( ((getLastVertex()->getType() & VE_TRANSPORT_LEFT) == VE_TRANSPORT_LEFT) ||
			((getLastVertex()->getType() & VE_TRANSPORT_RIGHT) == VE_TRANSPORT_RIGHT) )
			teleport(getLastVertex());

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

PowerControlTimer* Pacman::getTimer() {
	return _timer;
}


void Pacman::eatBall()
{
	std::vector<GraphVertex*> teleports = InfoGame::getSingleton().getScene()->getGraph()->getVertexes (VE_BALL);
	std::vector<GraphVertex*>::const_iterator cit = teleports.begin();
	std::vector<GraphVertex*>::const_iterator cend = teleports.end();

	for(;cit != cend; cit++)
	{
		if((*cit)->getIndex() == getLastVertex()->getIndex())
		{
			InfoGame::getSingleton().decBalls();
			InfoGame::getSingleton().addPoints();
			IntroState::getSingleton().getChompFXPtr()->play();
			clearBall();
			break;
		}
	}
}

void Pacman::eatBallPower()
{
	std::vector<GraphVertex*> teleports = InfoGame::getSingleton().getScene()->getGraph()->getVertexes (VE_BALLPOWER);
	std::vector<GraphVertex*>::const_iterator cit = teleports.begin();
	std::vector<GraphVertex*>::const_iterator cend = teleports.end();

	for(;cit != cend; cit++)
	{
		if((*cit)->getIndex() == getLastVertex()->getIndex())
		{
			InfoGame::getSingleton().decBalls();
			InfoGame::getSingleton().addPoints(30);
			clearBall();
			transformBallPower();
			setStatus(ST_POWERED);

			PlayState::getSingleton().getRed().transformScared();
			PlayState::getSingleton().getPink().transformScared();
			PlayState::getSingleton().getBlue().transformScared();
			PlayState::getSingleton().getOrange().transformScared();

			break;
		}
	}

	getTimer()->setSecondsLeft(10);


}

void Pacman::clearBall()
{
	Ogre::SceneNode *clearBall = PlayState::getSingleton().getSceneMgr()->getSceneNode("nodStageMap");
	Ogre::SceneNode *nodoHijo = NULL;

	getLastVertex()->setType(VE_BALLNONE);

	std::stringstream nodeName;
	nodeName << "ball_" << getLastVertex()->getIndex();

	nodoHijo = static_cast<Ogre::SceneNode*>(clearBall->getChild(nodeName.str()));
	nodoHijo->detachAllObjects();
	PlayState::getSingleton().getSceneMgr()->destroyEntity(nodeName.str());
	PlayState::getSingleton().getSceneMgr()->destroySceneNode(nodeName.str());
}

void Pacman::transformBallPower()
{
	Ogre::SceneNode *node = PlayState::getSingleton().getSceneMgr()->getSceneNode("pacman");
	Ogre::Entity *pEnt = NULL;

	pEnt = static_cast <Ogre::Entity *> (node->getAttachedObject("pacman"));
	// cambiamos la textura del objeto a SELECCIONADA
	pEnt->setMaterialName("ballPower");

}

void Pacman::transformBallUnPower()
{
	Ogre::SceneNode *node = PlayState::getSingleton().getSceneMgr()->getSceneNode("pacman");
	Ogre::Entity *pEnt = NULL;

	pEnt = static_cast <Ogre::Entity *> (node->getAttachedObject("pacman"));
	// cambiamos la textura del objeto a SELECCIONADA
	pEnt->setMaterialName("pacman");

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


