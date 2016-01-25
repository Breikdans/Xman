#include <GraphVertex.h>

GraphVertex::GraphVertex(int index, EN_TYPE_VERTEX type, Ogre::Vector3 position) : _index(index), _type(type), _position(position) {
	_maskPaths = 0;
}

GraphVertex::GraphVertex(const GraphVertex& grVertex)
{
	*this = grVertex;
}

void GraphVertex::addEdge(GraphEdge* e) {
	_edges.push_back(e);
}

std::vector<GraphEdge*> GraphVertex::getEdges ()  {
	return _edges;
}


GraphVertex::~GraphVertex ()
{
	std::vector<GraphEdge*>::iterator itEdge;
	for (itEdge = _edges.begin(); itEdge != _edges.end(); ++itEdge)
		delete *itEdge;

	_edges.clear();
}

int GraphVertex::getIndex(void) const
{
	return _index;
}

EN_TYPE_VERTEX GraphVertex::getType(void) const
{
	return _type;
}

Ogre::Vector3 GraphVertex::getPosition(void) const
{
	return _position;
}

GraphVertex& GraphVertex::operator= (const GraphVertex &grVertex)
{
	_index 		= grVertex._index;
	_type		= grVertex._type;
	_position	= grVertex._position;
	_maskPaths = grVertex._maskPaths;


	std::vector<GraphEdge*> e = grVertex._edges;
	vector<GraphEdge*>::iterator it = e.begin();

	for(; it != e.end();it++)
	{
		_edges.push_back(new GraphEdge(**it));
	}




	return *this;
}

const int GraphVertex::getMaskPaths() {
	return _maskPaths;
}

void GraphVertex::setMaskPaths() {
	std::vector<GraphEdge*> e = _edges;
	vector<GraphEdge*>::iterator it = e.begin();

	_maskPaths = 0;
	for(; it != e.end();it++)
	{
		GraphVertex* v = (*it)->getDestination();
		float oX = _position.x;
		float oY = _position.y;

		float dX = v->getPosition().x;
		float dY = v->getPosition().y;

		if (dX < oX)
		{ // Se puede ir a la izquierda
			_maskPaths |= LEFT_PATH;
		}

		if(dX > oX)
		{ // Se puede a la derecha
			_maskPaths |= RIGHT_PATH;
		}

		 if(dY > oY)
		{ // Se puede hacia abajo
			_maskPaths |= DOWN_PATH;
		}

		 if(dY < oY)
		 { // Se puede hacia arriba
		 		_maskPaths |= UP_PATH;
		 }
	}
	std::cout << "Vertex " << _index << " mask -> " << _maskPaths << std::endl;
}

