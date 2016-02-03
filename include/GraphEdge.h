#ifndef GRAPHEDGE_H_
#define GRAPHEDGE_H_

#include <iostream>
#include <vector>
#include <GraphVertex.h>

using namespace std;

class GraphVertex;

class GraphEdge
{
	public:
		GraphEdge (GraphVertex* origin = NULL, GraphVertex* dest = NULL, float weight = 1.0f, int direction = 0);
		GraphEdge (const GraphEdge& G);
		GraphEdge& operator=(const GraphEdge& G);
		~GraphEdge ();

		void setOrigin (GraphVertex* origin);
		GraphVertex* getOrigin () const;
		void setDestination (GraphVertex* dest);
		GraphVertex* getDestination () const;
		void setWeight(float w);
		float getWeight(void) const;

	private:
		GraphVertex* _pOrigin;
		GraphVertex* _pDestination;
		float _weight;
		int _direction;
};

#endif
