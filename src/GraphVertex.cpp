#include <GraphVertex.h>

GraphVertex::GraphVertex(int index, EN_TYPE_VERTEX type, Ogre::Vector3 position) : _index(index), _type(type), _position(position) {}

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


	std::vector<GraphEdge*> e = grVertex._edges;
	vector<GraphEdge*>::iterator it = e.begin();

	for(; it != e.end();it++)
	{
		_edges.push_back(new GraphEdge(**it));
	}




	return *this;
}

//#define VERTEX_UP		1 << 0		// = 1. 32 bits de mascara. = 00000001
//#define VERTEX_DOWN 	1 << 1		// = 2. 32 bits de mascara. = 00000010
//#define VERTEX_RIGHT	1 << 2		// = 4. 32 bits de mascara. = 00000100
//#define VERTEX_LEFT		1 << 3		// = 8. 32 bits de mascara. = 00001000
//
//GraphVertex* GraphVertex::UpVertex(const GraphVertex &V) const
//{
//	std::vector<GraphEdge*>::const_iterator citEdge;
//	for (citEdge = _edges.begin(); citEdge != _edges.end(); ++citEdge)
//	{
//
//	}
//
//	retorno |= EN_UP
//
//	retorno = 3
//
//
//}
//
//if (AdjacentsVertex(V) & EN_UP)
//
//GraphVertex* GraphVertex::DownVertex(const GraphVertex &V) const;
//GraphVertex* GraphVertex::LeftVertex(const GraphVertex &V) const;
//GraphVertex* GraphVertex::RightVertex(const GraphVertex &V) const;
