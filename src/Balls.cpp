#include "Balls.h"

Balls::Balls() {}

Balls::~Balls()
{
	for (std::vector< SceneBall >::iterator it = _balls.begin() ; it != _balls.end(); ++it)
	{
		delete (*it);
	}
	_balls.clear();
}

SceneBall Balls::getBallByIndex(int index) const
{
	return _balls.at(index);
}

int getTotalBalls(void) const;
int getBallsLeft(void) const;

void decrementBall(int);
void addBall(const SceneBall& sceneBall);
