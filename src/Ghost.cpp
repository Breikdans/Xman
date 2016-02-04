#include <boost/config.hpp>
#include <iostream>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

#include "PlayState.h"
#include "Ghost.h"

using namespace boost;

Ghost::Ghost(GraphVertex* lv, GraphVertex* vt, EN_GHOST_TYPE tg) : _pacmanLastSavedVertex(lv), _vertexTarget(vt), _typeGhost(tg)
{
	_speed 	= 2.1f;
	_status	= ST_CHASE;
}

Ghost::Ghost(const Ghost& G)
{
	*this = G;
}

Ghost& Ghost::operator= (const Ghost &G)
{
	// los punteros son para que apunten al vertice que nos pasen, no para crear un vertice con new
	_pacmanLastSavedVertex	= G._pacmanLastSavedVertex;
	_vertexTarget			= G._vertexTarget;

	_typeGhost				= G._typeGhost;

	return *this;
}

Ghost::~Ghost() {}

std::vector<int> Ghost::calculatePath(GraphVertex *origin, GraphVertex *destiny)
{
	std::vector<int> path;
	std::vector<int> reversePath;

	// Definición de estructuras de datos...
	typedef adjacency_list <listS, vecS, directedS,	no_property, property <edge_weight_t, int> > graph_t;
	typedef graph_traits <graph_t>::vertex_descriptor vertex_descriptor;
	typedef std::pair<int, int> Edge;

	std::vector<GraphEdge*> vEdges = InfoGame::getSingleton().getScene()->getGraph()->getEdges();
	std::vector<GraphEdge*>::iterator it_edge = vEdges.begin();

	int num_edges = vEdges.size();
	Edge *array_edge = new Edge[num_edges];
	int *array_weights = new int[num_edges];

	int num_vertexes = InfoGame::getSingleton().getScene()->getGraph()->getVertexes().size();

	int i = 0;

	for(it_edge = vEdges.begin(); it_edge != vEdges.end(); it_edge++)
	{
		Edge e( (*it_edge)->getOrigin()->getIndex(), (*it_edge)->getDestination()->getIndex() );
		array_edge[i] = e;

		array_weights[i++] = (*it_edge)->getWeight();
//		std::cout << "ELEMENTO " << i-1 << ": First: " << array_edge[i-1].first << " Second: " << array_edge[i-1].second << std::endl;
	}

	graph_t g(array_edge, array_edge + num_edges, array_weights, num_vertexes);

	std::vector<vertex_descriptor> p(num_vertices(g));
	std::vector<int> d(num_vertices(g));
	vertex_descriptor s = vertex(origin->getIndex(), g); // CAMINOS DESDE ORIGIN.

	// Algoritmo de Dijkstra.
	dijkstra_shortest_paths(g, s, predecessor_map(&p[0]).distance_map(&d[0]));


	i = 0;
	int currentVertex = destiny->getIndex();
	reversePath.push_back(currentVertex);
//	std::cout << "CurrentVertex: " << reversePath[i++] << std::endl;
	while((int)p.at(currentVertex) != origin->getIndex())
	{
		currentVertex = p.at(currentVertex);
		reversePath.push_back(currentVertex);
//		std::cout << "CurrentVertex: " << reversePath[i++] << std::endl;
	}

	reversePath.push_back(p.at(currentVertex));
//	std::cout << "CurrentVertex: " << reversePath[i] << std::endl;

	std::vector<int>::reverse_iterator rit = reversePath.rbegin();
	std::vector<int>::reverse_iterator rend = reversePath.rend();
	for(; rit != rend; rit++)
		path.push_back(*rit);

	delete [] array_edge;
	delete [] array_weights;

	return path;
}


void Ghost::setPacmanLastVertex(GraphVertex* vertex)
{
	_pacmanLastSavedVertex = vertex;
}

/**
 * Funcion que movera el fastasma
 */
void Ghost::move(GraphVertex* pacmanLastVertex, Ogre::Real deltaT)
{
	static std::vector<int> path;
	std::vector<int> pathaux;

//	std::vector<int> path;
	// Si PACMAN ha CAMBIADO de posicion, hay que recalcular el vertice-objetivo...
//	if (_pacmanLastSavedVertex &&
//		_pacmanLastSavedVertex->getIndex() != pacmanLastVertex->getIndex())
//	{
//		_pacmanLastSavedVertex = pacmanLastVertex;

		updateVertexTarget();
//	}

	path = calculatePath(getLastVertex(), _vertexTarget);
	PintaPath(path);
	// Si estamos en el mismo vertice, cogemos la misma direccion que el pacman
	if(getLastVertex() == _vertexTarget)
	{
		cout << "estamos en el mismo vertice" << endl;
		_direction = PlayState::getSingleton().getPacman().getDirection();
	}

	FollowPath(path, deltaT);
}

void Ghost::setDirectionNextVertex(int nextVertex)
{
	float errRange = 0.15f;
	GraphVertex *vertex = InfoGame::getSingleton().getScene()->getGraph()->getVertex(nextVertex);

	float x_ini = getLastVertex()->getPosition().x;
	float y_ini = getLastVertex()->getPosition().y;

	float x_fin = vertex->getPosition().x;
	float y_fin = vertex->getPosition().y;

	if (x_ini < x_fin)
	{
		if (std::abs(x_ini-x_fin) > errRange)
			_direction = RIGHT_PATH;
	}
	else if (x_ini > x_fin)
	{
		if (std::abs(x_ini-x_fin) > errRange)
		_direction = LEFT_PATH;
	}
	else if (y_ini < y_fin)
	{
		if (std::abs(y_ini-y_fin) > errRange)
		_direction = UP_PATH;
	}
	else if (y_ini > y_fin)
	{
		if (std::abs(y_ini-y_fin) > errRange)
		_direction = DOWN_PATH;
	}

//	switch(_direction)
//	{
//		case RIGHT_PATH:
//		case LEFT_PATH:
//			setPosition(getPosition().x, y)
//			break;
//	}
}

void Ghost::FollowPath(const std::vector<int> &path, Ogre::Real deltaT)
{
	// si estamos en un vertice, lo buscamos en el path y recogemos el siguiente vertice del path, para ir hacia el
	if ( isIntoVertex(getLastVertex()) )
	{

cout << "estoy en vertice!!: " << getLastVertex()->getIndex() << endl;
		std::vector<int>::const_iterator cit = path.begin();
		std::vector<int>::const_iterator cend = path.end();
		for(; cit != cend; cit++)
		{
			// si hemos encontrado el vertice actual en el path...
			if(getLastVertex()->getIndex() == *cit)
			{
				setDirectionNextVertex(*(++cit));
				break;
			}
		}
	}

	float s = getSpeed();
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

void Ghost::updateVertexTarget()
{
	// primero comprobamos el tipo del fantasma....
	switch(_typeGhost)
	{
		case EN_CHASER:		// (Blinky - RED GHOST) siempre va a la casilla del pacman. Incrementa su velocidad cuando quedan pocas bolas en pantalla
			// comprobamos en que estado esta....
			switch(_status)
			{
				case ST_NORMAL:		// Pacman: Normal
				case ST_POWERED:	// Pacman: Power!
					break;
				case ST_CHASE:		// Ghost:  Perseguir
					//_vertexTarget = PlayState::getSingleton().getPacman().getLastVertex();
					_vertexTarget = PlayState::getSingleton().getPacman().getClosestAdjacentVertex();
					break;
				case ST_SCATTER:	// Ghost:  Dispersarse cada uno a su esquina
				case ST_SCARED:		// Ghost:  Asustado!
					break;
			}
			break;
		case EN_AMBUSHER:	// (Pinky - PINK GHOST) siempre intenta cortarle el camino al pacman, yendo 4 casillas por delante en la direccion del pacman... o 2 vertices
			break;
		case EN_FICKLE:		// (Inky - BLUE GHOST, fickle = caprichoso) a ratos persigue como CHASER y a ratos como AMBUSHER
			break;
		case EN_PRETENDER:	// (Clyde - ORANGE GHOST) cuando esta lejos del pacman, pasa a modo ST_SCATTER (a su esquina) y cuando esta cerca a ST_CHASE como EN_CHASER
			break;
	}
}

void Ghost::PintaPath(std::vector<int> &path)
{
	static int i = 0;
	Ogre::SceneNode *drawPath = PlayState::getSingleton().getSceneMgr()->getSceneNode("drawPath");

	for (int j = 0; j < i; j++)
	{
		Ogre::SceneNode *nodoHijo = NULL;
		std::stringstream nodeName;
		nodeName << "ball_" << j;

		nodoHijo = static_cast<Ogre::SceneNode*>(drawPath->getChild(nodeName.str()));
		nodoHijo->detachAllObjects();
		PlayState::getSingleton().getSceneMgr()->destroyEntity(nodeName.str());
		PlayState::getSingleton().getSceneMgr()->destroySceneNode(nodeName.str());
	}

	i = 0;
	std::vector<int>::const_iterator it;
	for (it = path.begin(); it != path.end(); ++it)
	{
		GraphVertex* b = InfoGame::getSingleton().getScene()->getGraph()->getVertex((*it));
		float x = b->getPosition().x;
		float y = b->getPosition().z;
		float z = -b->getPosition().y;

		std::stringstream nodeName;
		nodeName << "ball_" << i++;
cout << "nodeName: " << nodeName.str() << endl;
		Ogre::Entity *entBall =PlayState::getSingleton().getSceneMgr()->createEntity(nodeName.str(),"ball.mesh");

		Ogre::SceneNode* ballNode = PlayState::getSingleton().getSceneMgr()->createSceneNode(nodeName.str());
		ballNode->setPosition(x,y,z);
		ballNode->attachObject(entBall);
		drawPath->addChild(ballNode);
	}

	cout << "BOLAS CREADAS: " << i << endl;
}

