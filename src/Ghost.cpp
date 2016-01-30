#include <boost/config.hpp>
#include <iostream>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

#include "Ghost.h"

using namespace boost;



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
	std::cout << "CurrentVertex: " << reversePath[i++] << std::endl;
	while((int)p.at(currentVertex) != origin->getIndex())
	{
		currentVertex = p.at(currentVertex);
		reversePath.push_back(currentVertex);
		std::cout << "CurrentVertex: " << reversePath[i++] << std::endl;
	}

	reversePath.push_back(p.at(currentVertex));
	std::cout << "CurrentVertex: " << reversePath[i] << std::endl;

	std::vector<int>::reverse_iterator rit = reversePath.rbegin();
	std::vector<int>::reverse_iterator rend = reversePath.rend();
	for(; rit != rend; rit++)
		path.push_back(*rit);

	delete [] array_edge;
	delete [] array_weights;
	for(i=0; i != (int)path.size(); i++)
		std::cout << "PATH: " << path[i] << std::endl;
	return path;
}
