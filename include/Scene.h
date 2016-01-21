#ifndef SCENE_H_
#define SCENE_H_

#include "Graph.h"
#include "SceneBall.h"
#include "Camera.h"

class Scene
{
	public:
		Scene();
		Scene(const Scene&);
		Scene& operator=(const Scene&);
		~Scene();
		SceneBall getBallByIndex(int index) const;
		int getTotalBalls(void) const;
		int getBallsLeft(void) const;
		void decBalls(int i = 1);
		std::vector<SceneBall*> getBalls() const { return _balls; }

		void addBall(const SceneBall& scBall);
		void addCamera (Camera* camera);

		Camera* getCamera(std::string cameraName) const;

		std::vector<Camera*> getCameras () const 	{ return _cameras; }
		Graph* getGraph () const 					{ return _graph; }
	private:
		Graph* _graph;						// Graph describing the vertexes and connection between them (edges)

		std::vector<Camera*> _cameras; 		// Vector containing the game cameras
		std::vector<SceneBall*> _balls;		// Vector containing the game balls
		int _totalBalls;					// Total of balls in the beginning of the scene
		int _ballsLeft;						// Balls left to complete level
};

#endif /* SCENE_H_ */
