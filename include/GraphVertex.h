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

const int UP_PATH = 			0x01;	// 00000001
const int DOWN_PATH =		0x02;	// 00000010
const int LEFT_PATH = 		0x04;	// 00000100
const int RIGHT_PATH =		0x08;   // 00001000
const int NONE_PATH = 		0;


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

		void addEdge (GraphEdge* e);
		std::vector<GraphEdge*> getEdges ();

		const int getMaskPaths();

		void setMaskPaths();
	private:
		int _index;						// Index of the vertex (unique index)
		EN_TYPE_VERTEX _type;			// Type of vertex
		Ogre::Vector3 _position; 		// vertex's position in 3D space
		std::vector<GraphEdge*> _edges;	// edges where the vertex is
		int _maskPaths;

};

#endif	/* GRAPHVERTEX_H_ */

