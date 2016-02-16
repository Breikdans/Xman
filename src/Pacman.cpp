#include "IntroState.h"
#include "PlayState.h"
#include "Pacman.h"
#include "StatesTimer.h"

Pacman::Pacman() {

}

Pacman::~Pacman() {

}

void Pacman::move(const int key, Ogre::Real deltaT)
{
	// MOVER
		float s = InfoGame::getSingleton().getLevel(InfoGame::getSingleton().getCurrentLevel()).getPlayerSpeed();
		switch(getDirection())
		{
			case LEFT_PATH:
				_node->translate(-s * deltaT,0,0);
				_node->setPosition(getPosition().x,getPosition().y, -(getLastVertex()->getPosition().y));
				break;
			case RIGHT_PATH:
				_node->translate(s * deltaT,0,0);
				_node->setPosition(getPosition().x,getPosition().y, -(getLastVertex()->getPosition().y));
				break;
			case UP_PATH:
				_node->translate(0,0,-s * deltaT);
				_node->setPosition(getLastVertex()->getPosition().x,getPosition().y, getPosition().z);
				////std:://cout << "UP! y: " << -s << std::endl;
				break;
			case DOWN_PATH:
				_node->translate(0,0,s * deltaT);
				_node->setPosition(getLastVertex()->getPosition().x,getPosition().y, getPosition().z);
				////std:://cout << "DOWN! y: " << s << std::endl;
				break;
			case NONE_PATH:
				_node->translate(0,0,0);
				break;
		}

	if (isIntoVertexTotal(getLastVertex()))
	{	// Esta dentro de un vertice

		if( (getLastVertex()->getType() & VE_BALL) == VE_BALL )
			eatBall();

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

	// Animacion
	Ogre::AnimationState* anim = PlayState::getSingleton().getSceneMgr()->getEntity("pacman")->getAnimationState("Action");
	Ogre::AnimationState* idle = PlayState::getSingleton().getSceneMgr()->getEntity("pacman")->getAnimationState("Idle");
	switch (getDirection())
		{
			case LEFT_PATH:
			case RIGHT_PATH:
			case UP_PATH:
			case DOWN_PATH:
				idle->setTimePosition(0.0);
				idle->setEnabled(false);
				anim->setEnabled(true);
				anim->setLoop(true);
				anim->addTime(deltaT);
				break;
			case NONE_PATH:
				anim->setTimePosition(0.0);
				anim->setEnabled(false);
				idle->setEnabled(true);
				idle->setLoop(true);
				idle->addTime(deltaT);
				break;
		}



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
			InfoGame::getSingleton().getTotalPoints();
			PlayState::getSingleton().updateInfoOverlay();
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


			PlayState::getSingleton().getRed().getStatesTimer()->changeStatus(ST_SCARED);
			PlayState::getSingleton().getPink().getStatesTimer()->changeStatus(ST_SCARED);
			PlayState::getSingleton().getBlue().getStatesTimer()->changeStatus(ST_SCARED);
			PlayState::getSingleton().getOrange().getStatesTimer()->changeStatus(ST_SCARED);

			break;
		}
	}
}

void Pacman::clearBall()
{
	Ogre::SceneNode *clearBall = PlayState::getSingleton().getSceneMgr()->getSceneNode("nodStageMap");
	Ogre::SceneNode *nodoHijo = NULL;

	if ((getLastVertex()->getType() & VE_BALLPOWER)==VE_BALLPOWER)
	{
		getLastVertex()->setType(VE_BALLNONE | VE_BALLESCAPE);
	} else {
		getLastVertex()->setType(VE_BALLNONE);
	}

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


