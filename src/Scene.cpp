#include "Scene.h"

Scene::Scene()
{
	_graph = new Graph();
	_balls.reserve(250);		// Approx. reservation for 250 balls objects in the vector
}

Scene::~Scene()
{
	for (std::vector< SceneBall* >::iterator it = _balls.begin() ; it != _balls.end(); ++it)
	{
		delete (*it);
	}
	_balls.clear();
	delete _graph;
}

SceneBall Scene::getBallByIndex(int index) const
{
	return *(_balls.at(index));
}

int Scene::getTotalBalls(void) const
{
	return _totalBalls;
}

int Scene::getBallsLeft(void) const
{
	return _Ballsleft;
}

void Scene::decBalls(int i)
{
	_Ballsleft -= i;
}

void Scene::addBall(const SceneBall& scBall)
{
	_balls.push_back(new SceneBall(scBall));
}

void Scene::addCamera (Camera* camera) {
	_cameras.push_back(camera);
}



