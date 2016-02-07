#ifndef GHOST_H_
#define GHOST_H_

#include "Character.h"
#include "StatesTimer.h"

typedef enum
{
	EN_CHASER	= 0,	// (Blinky - RED GHOST) siempre va a la casilla del pacman. Incrementa su velocidad cuando quedan pocas bolas en pantalla
	EN_AMBUSHER,		// (Pinky - PINK GHOST) siempre intenta cortarle el camino al pacman, yendo 4 casillas por delante en la direccion del pacman... o 2 vertices
	EN_FICKLE,			// (Inky - BLUE GHOST, fickle = caprichoso) a ratos persigue como CHASER y a ratos como AMBUSHER
	EN_PRETENDER		// (Clyde - ORANGE GHOST) cuando esta lejos del pacman, pasa a modo ST_SCATTER (a su esquina) y cuando esta cerca a ST_CHASE como EN_CHASER
}EN_GHOST_TYPE;

class StatesTimer;

class Ghost : public Character
{

	public:
		Ghost(GraphVertex* vt = 0, EN_GHOST_TYPE tg = EN_CHASER);
		Ghost(const Ghost& G);
		Ghost& operator= (const Ghost &G);
		~Ghost();

		void move(GraphVertex* pacmanLastVertex, Ogre::Real deltaT);
		GraphVertex* getLastVertex() const;
		bool checkCollision();
		void transformScared();
		void transformNormal();
		void transformDead();


		void addScatterPoint(int scatterIndex, int vertexIndex);
		void calculateScatterPath();
		std::vector<int> getScatterPath();

		int getTimeScatter() const;
		int getTimeScared() const;
		int getTimeChase() const;
		int getTimeHome() const;

		void setTimeScatter(int T);
		void setTimeScared(int T);
		void setTimeChase(int T);
		void setTimeHome(int T);

		StatesTimer* getStatesTimer();

	private:
		std::vector<int> calculatePath(GraphVertex *origin, GraphVertex *destiny);
		void updateVertexTarget();
		void setDirectionNextVertex(int);

		void FollowPath(const std::vector<int> &path, Ogre::Real deltaT);
		bool isEqualPath(const std::vector<int> &path);
		GraphVertex* calculateEscapeVertex();

void DebugPath(const std::vector<int>& path);
void DebugGhostLastVertex() const;
void DebugTarget();
void DebugPintaPath(std::vector<int> &path);

		GraphVertex*	_vertexTarget;
		EN_GHOST_TYPE 	_typeGhost;

		std::map<int, int> _scatterMapPath;
		std::vector<int> _scatterPath;

		std::vector<int> _path;

		int _timeScatter;
		int _timeChase;
		int _timeHome;
		int _timeScared;

		StatesTimer* _statesTimer;

};

#endif /* GHOST_H_ */
