#ifndef GHOST_H_
#define GHOST_H_

#include "Character.h"
typedef enum
{
	EN_CHASER	= 0,	// (Blinky - RED GHOST) siempre va a la casilla del pacman. Incrementa su velocidad cuando quedan pocas bolas en pantalla
	EN_AMBUSHER,		// (Pinky - PINK GHOST) siempre intenta cortarle el camino al pacman, yendo 4 casillas por delante en la direccion del pacman... o 2 vertices
	EN_FICKLE,			// (Inky - BLUE GHOST, fickle = caprichoso) a ratos persigue como CHASER y a ratos como AMBUSHER
	EN_PRETENDER		// (Clyde - ORANGE GHOST) cuando esta lejos del pacman, pasa a modo ST_SCATTER (a su esquina) y cuando esta cerca a ST_CHASE como EN_CHASER
}EN_GHOST_TYPE;

class Ghost : public Character
{

	public:
		Ghost(GraphVertex* lv = 0, GraphVertex* vt = 0, EN_GHOST_TYPE tg = EN_CHASER);
		Ghost(const Ghost& G);
		Ghost& operator= (const Ghost &G);
		~Ghost();

		void move(GraphVertex* pacmanLastVertex, Ogre::Real deltaT);

		void setPacmanLastVertex(GraphVertex* vertex);

	private:
		std::vector<int> calculatePath(GraphVertex *origin, GraphVertex *destiny);
		void updateVertexTarget();
		void setDirectionNextVertex(int);

		void FollowPath(const std::vector<int> &path, Ogre::Real deltaT);

void PintaPath(std::vector<int> &path);

		GraphVertex* 	_pacmanLastSavedVertex;
		GraphVertex*	_vertexTarget;
		EN_GHOST_TYPE 	_typeGhost;

};

#endif /* GHOST_H_ */
