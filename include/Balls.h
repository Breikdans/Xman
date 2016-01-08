#ifndef BALLS_H_
#define BALLS_H_

#include "SceneBall.h"

class Balls
{
	public:
		Balls();
		~Balls();
		SceneBall getBallByIndex(int index) const;
		int getTotalBalls(void) const;
		int getBallsLeft(void) const;

		void decrementBall(int);
		void addBall(const SceneBall& sceneBall);
	private:
		std::vector<SceneBall*> _balls;		// Vector containing the game balls
		int _total;							// Total of balls in the beginning of the scene
		int _left;							// Balls left to complete level
};

#endif /* BALLS_H_ */
