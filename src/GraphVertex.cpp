#include <GraphVertex.h>

GraphVertex::GraphVertex(int index, EN_TYPE_VERTEX type, Ogre::Vector3 position) : _index(index), _type(type), _position(position) {}

GraphVertex::GraphVertex(const GraphVertex& grVertex)
{
	*this = grVertex;
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

	return *this;
}

