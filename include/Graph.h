#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <vector>
#include <GraphVertex.h>
#include <GraphEdge.h>

class Graph
{
	public:
		Graph ();
		Graph (const Graph&);
		Graph& operator=(const Graph&);
		~Graph ();

		void addVertex (GraphVertex* pVertex);
		void addEdge (GraphVertex* pOrigin,
					  GraphVertex* pDestination,
					  bool undirected = true);

		GraphVertex* getVertex (int index) const;
		std::vector<GraphVertex*> getVertexes () const 	{ return _vertexes; }
		std::vector<GraphEdge*> getEdges () const 		{ return _edges; }

	private:
		std::vector<GraphVertex*> _vertexes;
		std::vector<GraphEdge*> _edges;
};

#endif	/* GRAPH_H_ */
