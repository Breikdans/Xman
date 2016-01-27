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
		GraphEdge (GraphVertex* origin = NULL, GraphVertex* dest = NULL);
		~GraphEdge ();

		void setOrigin (GraphVertex* origin) 	{ _pOrigin = origin; }
		GraphVertex* getOrigin () const 		{ return _pOrigin; }
		void setDestination (GraphVertex* dest) { _pDestination = dest; }
		GraphVertex* getDestination () const 	{ return _pDestination; }
		void setWeight(float w)					{ _weight = w; }
		float getWeight(void) const				{ return _weight; }

	private:
		GraphVertex* _pOrigin;
		GraphVertex* _pDestination;
		float _weight;
};

#endif
