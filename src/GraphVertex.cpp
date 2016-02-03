#include <GraphVertex.h>

GraphVertex::GraphVertex(int index, int type, Ogre::Vector3 position, int mask) : _index(index), _type(type), _position(position), _maskPaths(mask) {}

GraphVertex::GraphVertex(const GraphVertex& grVertex)
{
	*this = grVertex;
}

GraphVertex& GraphVertex::operator= (const GraphVertex &grVertex)
{
	_index 		= grVertex._index;
	_type		= grVertex._type;
	_position	= grVertex._position;
	_maskPaths 	= grVertex._maskPaths;

	vector<GraphEdge*> e = grVertex._edges;
	vector<GraphEdge*>::iterator it = e.begin();

	for(; it != e.end();it++)
	{
		_edges.push_back(new GraphEdge(**it));
	}

	return *this;
}

GraphVertex::~GraphVertex ()
{
	vector<GraphEdge*>::iterator itEdge;
	for (itEdge = _edges.begin(); itEdge != _edges.end(); ++itEdge)
	{
		if(*itEdge != NULL)
			delete *itEdge;
	}

	_edges.clear();
}

void GraphVertex::addEdge(GraphEdge* e)
{
	_edges.push_back(e);
}

vector<GraphEdge*> GraphVertex::getEdges ()
{
	return _edges;
}

int GraphVertex::getIndex(void) const
{
	return _index;
}

int GraphVertex::getType(void) const
{
	return _type;
}

Ogre::Vector3 GraphVertex::getPosition(void) const
{
	return _position;
}

const int GraphVertex::getMaskPaths() {
//	//std:://cout << "Vertice " << _index << " -> mask " << _maskPaths << endl;
	return _maskPaths;
}

void GraphVertex::setMaskPaths()
{
	vector<GraphEdge*> e = _edges;
	vector<GraphEdge*>::iterator it = e.begin();
	float errRange = 0.15f;

//	//std:://cout << "Vertex " << _index << std::endl;
	_maskPaths = 0;
	for(; it != e.end();it++)
	{

		GraphVertex* vO = (*it)->getOrigin();
		GraphVertex* vD = (*it)->getDestination();
		GraphVertex* v = vO;

//		//cout << "     ORIGEN " << vO->getIndex() << " - DESTINO " << vD->getIndex() << std::endl;
		if (v->getIndex() == _index)
		{
			v = vD;
		}

//		//std:://cout << "         ARISTA " << v->getIndex()  << std::endl;
		float oX = _position.x;
		float oY = _position.y;

		float dX = v->getPosition().x;
		float dY = v->getPosition().y;

		if (dX < oX)
		{ // Se puede ir a la izquierda
			if (std::abs(dX-oX) > errRange)
			{
//				(*it)->setWeight(floor(std::abs(dX-oX))+0.5);
				_maskPaths |= LEFT_PATH;
			}
		}

		if(dX > oX)
		{ // Se puede a la derecha
			if (std::abs(dX-oX) > errRange)
			{
//				(*it)->setWeight(floor(std::abs(dX-oX))+0.5);
				_maskPaths |= RIGHT_PATH;
			}
		}

		if(dY > oY)
		{ // Se puede hacia abajo
			 if (std::abs(dY-oY) > errRange)
			 {
//				 (*it)->setWeight(floor(std::abs(dY-oY))+0.5);
				 _maskPaths |= UP_PATH;
			 }
		}

		if(dY < oY)
		{ // Se puede hacia arriba
			if (std::abs(dY-oY) > errRange)
			{
//				(*it)->setWeight(floor(std::abs(dY-oY))+0.5);
				_maskPaths |= DOWN_PATH;
			}
		}
//		//cout << "         WEIGHT " << (*it)->getWeight() << std::endl;
		(*it)->setWeight(1);
	}
//	//std:://cout << "Vertex " << _index << " mask -> " << _maskPaths << std::endl;
}

