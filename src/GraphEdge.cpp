#include <GraphEdge.h>

GraphEdge::GraphEdge (GraphVertex* origin, GraphVertex* dest, float weight, int direction) : _pOrigin(origin), _pDestination(dest), _weight(weight), _direction(direction)
{

}

GraphEdge::GraphEdge (const GraphEdge& G)
{
	*this = G;
}

GraphEdge& GraphEdge::operator=(const GraphEdge& G)
{
	_pOrigin 		= G._pOrigin;
	_pDestination	= G._pDestination;
	_weight			= G._weight;

	return *this;
}

GraphEdge::~GraphEdge () {}

void GraphEdge::setOrigin (GraphVertex* origin)
{
	_pOrigin = origin;
}

GraphVertex* GraphEdge::getOrigin () const
{
	return _pOrigin;
}

void GraphEdge::setDestination (GraphVertex* dest)
{
	_pDestination = dest;
}

GraphVertex* GraphEdge::getDestination () const
{
	return _pDestination;
}

void GraphEdge::setWeight(float w)
{
	_weight = w;
}

float GraphEdge::getWeight(void) const
{
	return _weight;
}
