#ifndef GRAPHVERTEX_H_
#define GRAPHVERTEX_H_

#include <iostream>
#include <vector>
#include <GraphEdge.h>
#include <OGRE/Ogre.h>

using namespace std;

const int VE_NORMAL 	= 0;
const int VE_TRANSPORT	= 1;
const int VE_STPLAYER	= 2;
const int VE_STENEMY	= 4;
const int VE_FORBIDDEN	= 8;
const int VE_BALL		= 16;
const int VE_BALLPOWER	= 32;
const int VE_BALLNONE	= 64;

const int UP_PATH	= 		0x01;	// 00000001
const int DOWN_PATH =		0x02;	// 00000010 desplazamientos para máscara
const int LEFT_PATH = 		0x04;	// 00000100
const int RIGHT_PATH=		0x08;   // 00001000
const int NONE_PATH = 		0x00;	// 00000000


class GraphEdge;

class GraphVertex
{
	public:
//		GraphVertex();
		GraphVertex(int index = 0, int type = VE_NORMAL, Ogre::Vector3 position = Ogre::Vector3(0,0,0), int mask = NONE_PATH);
		GraphVertex(const GraphVertex& grVertex);

		GraphVertex& operator= (const GraphVertex &grVertex);

		~GraphVertex ();

		int getIndex(void) const;
		int getType(void) const;
		Ogre::Vector3 getPosition(void) const;

		void addEdge (GraphEdge* e);
		std::vector<GraphEdge*> getEdges ();

		const int getMaskPaths();

		void setMaskPaths();
	private:
		int _index;						// Index of the vertex (unique index)
		int _type;						// Type of vertex
		Ogre::Vector3 _position; 		// vertex's position in 3D space
		int _maskPaths;
		std::vector<GraphEdge*> _edges;	// edges where the vertex is

};

#endif	/* GRAPHVERTEX_H_ */

