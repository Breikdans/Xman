#include <Graph.h>

Graph::Graph ()
{
	// Reserva de memoria inicial.
	_vertexes.reserve(100);
	_edges.reserve(50);
}

Graph::Graph(const Graph& G)
{
	*this = G;
}

//Graph& Graph::operator=(const Graph& G) : _vertexes(G._vertexes.size()), _edges(G._edges.size())	// con esto inicializamos los vectores resultantes con el tamaño del vector a copiar
Graph& Graph::operator=(const Graph& G)
{
    vector<GraphVertex*>::const_iterator that_g_it = G._vertexes.begin();

	for(; that_g_it != G._vertexes.end(); that_g_it++)
	{
		GraphVertex *temp = new GraphVertex(**that_g_it);
		_vertexes.push_back(temp);
	}

    vector<GraphEdge*>::const_iterator that_e_it = G._edges.begin();

	for(; that_e_it != G._edges.end(); that_e_it++)
	{
		_edges.push_back(new GraphEdge(**that_e_it));
	}

	return *this;
}

Graph::~Graph ()
{
	// Liberar vértices.
//	typename std::vector<GraphVertex*>::iterator itVert;
//	for (itVert = _vertexes.begin(); itVert != _vertexes.end();	++itVert)
//	{
////		if(*itVert != 0)
////			delete *itVert;
//	}
//	// Liberar arcos.
//	typename std::vector<GraphEdge*>::iterator itEdge;
//	for (itEdge = _edges.begin(); itEdge != _edges.end(); ++itEdge)
//	{
////		if(*itEdge != 0)
////			delete *itEdge;
//	}

	//for(int i = 0; i < _vertexes.size(); i++)
	//	delete _vertexes[i];

	//for(int i = 0; i < _edges.size(); i++)
	//	delete _edges[i];
		
	_vertexes.clear();
	_edges.clear();
}

void Graph::addVertex(GraphVertex* pVertex)
{
	_vertexes.push_back(pVertex);
}

void Graph::addEdge (GraphVertex* pOrigin, GraphVertex* pDestination, bool undirected)
{
	GraphEdge* pEdge = new GraphEdge(pOrigin, pDestination);
	_edges.push_back(pEdge);
	pOrigin->addEdge(pEdge);

	if (undirected)
	{
		GraphEdge* pEdge2 = new GraphEdge(pDestination, pOrigin);
		_edges.push_back(pEdge2);
		pDestination->addEdge(pEdge2);
	}
}

GraphVertex* Graph::getVertex (int index) const
{
	std::vector<GraphVertex*>::const_iterator it;

	for (it = _vertexes.begin(); it != _vertexes.end(); ++it)
		if ((*it)->getIndex() == index)
			return (*it);

	return NULL;
}
