#ifndef GRAPHVERTEX_H_
#define GRAPHVERTEX_H_

#include <iostream>
#include <vector>
#include <GraphEdge.h>
#include <OGRE/Ogre.h>

using namespace std;

typedef enum{
	EN_VE_NORMAL = 0,
	EN_VE_TRANSPORT= 1,
	EN_VE_STPLATYER=2,
	EN_VE_STENEMY=3,
	EN_VE_FORBIDDEN=4
}EN_TYPE_VERTEX;

class GraphEdge;

class GraphVertex
{
	public:
		GraphVertex(int index, EN_TYPE_VERTEX type, Ogre::Vector3 position);
		GraphVertex(const GraphVertex& grVertex);

		GraphVertex& operator= (const GraphVertex &grVertex);

		~GraphVertex ();

		int getIndex(void) const;
		EN_TYPE_VERTEX getType(void) const;
		Ogre::Vector3 getPosition(void) const;

		void addEdge (GraphEdge* pEdge) 				{ _edges.push_back(pEdge); }
		std::vector<GraphEdge*> getEdges () const 		{ return _edges; }

		GraphVertex* UpVertex(const GraphVertex &V) const;
		GraphVertex* DownVertex(const GraphVertex &V) const;
		GraphVertex* LeftVertex(const GraphVertex &V) const;
		GraphVertex* RightVertex(const GraphVertex &V) const;
	private:
		int _index;						// Index of the vertex (unique index)
		EN_TYPE_VERTEX _type;			// Type of vertex
		Ogre::Vector3 _position; 		// vertex's position in 3D space
		std::vector<GraphEdge*> _edges;	// edges where the vertex is
};

#endif	/* GRAPHVERTEX_H_ */

