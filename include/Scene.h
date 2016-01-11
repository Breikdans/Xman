#ifndef SCENE_H_
#define SCENE_H_

#include "SceneBall.h"
#include "Camera.h"

class Scene
{
	public:
		Scene();
		~Scene();
		SceneBall getBallByIndex(int index) const;
		int getTotalBalls(void) const;
		int getBallsLeft(void) const;

		void decBalls(int i = 1);
		void addBall(const SceneBall& scBall);

		void addCamera (Camera* camera);
		 std::vector<Camera*> getCameras () const { return _cameras; }
	private:
		std::vector<SceneBall*> _balls;		// Vector containing the game balls
		std::vector<Camera*> _cameras; // Vector containing the game cameras
		int _totalBalls;					// Total of balls in the beginning of the scene
		int _Ballsleft;						// Balls left to complete level
};

#endif /* SCENE_H_ */
