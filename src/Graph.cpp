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
    vector<GraphVertex*>::iterator this_g_it = _vertexes.begin();
    vector<GraphVertex*>::const_iterator that_g_it = G._vertexes.begin();

	for(; that_g_it != G._vertexes.end(); ++this_g_it, ++that_g_it)
	{
		*this_g_it = new GraphVertex(**that_g_it);
	}

    vector<GraphEdge*>::iterator this_e_it = _edges.begin();
    vector<GraphEdge*>::const_iterator that_e_it = G._edges.begin();

	for(; that_e_it != G._edges.end(); ++this_e_it, ++that_e_it)
	{
		*this_e_it = new GraphEdge(**that_e_it);
	}

	return *this;
}

Graph::~Graph ()
{
	// Liberar vértices.
	typename std::vector<GraphVertex*>::iterator itVert;
	for (itVert = _vertexes.begin(); itVert != _vertexes.end();	++itVert)
		delete *itVert;

	// Liberar arcos.
	typename std::vector<GraphEdge*>::iterator itEdge;
	for (itEdge = _edges.begin(); itEdge != _edges.end(); ++itEdge)
		delete *itEdge;

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
