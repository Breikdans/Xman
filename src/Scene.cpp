#include "Scene.h"

Scene::Scene()
{
	_graph = new Graph();
	_balls.reserve(250);		// Approx. reservation for 250 balls objects in the vector
}

Scene::Scene(const Scene& S)
{
	*this = S;
}

//Scene& Scene::operator=(const Scene &S) : _cameras(S._cameras.size()), _balls(S._balls.size())	// inicializador constructor copia para C++11, reserva espacio para vectores
Scene& Scene::operator=(const Scene &S)
{
	_totalBalls = S._totalBalls;
	_Ballsleft	= S._Ballsleft;
	_graph 		= new Graph(*(S._graph));

    vector<Camera*>::iterator this_c_it = _cameras.begin();				// iterador para el vector destino (nuestro vector)
    vector<Camera*>::const_iterator that_c_it = S._cameras.begin();	// iterador constante para el vector origen (vector recibido)

	for(; that_c_it != S._cameras.end(); ++this_c_it, ++that_c_it)
	{
		*this_c_it = new Camera(**that_c_it);
	}

    vector<SceneBall*>::iterator this_s_it = _balls.begin();			// iterador para el vector destino (nuestro vector)
    vector<SceneBall*>::const_iterator that_s_it = S._balls.begin();	// iterador constante para el vector origen (vector recibido)

	for(; that_s_it != S._balls.end(); ++this_s_it, ++that_s_it)
	{
		*this_s_it = new SceneBall(**that_s_it);
	}

	return *this;
}

Scene::~Scene()
{
	for (std::vector< SceneBall* >::iterator it = _balls.begin() ; it != _balls.end(); ++it)
	{
		delete (*it);
	}
	_balls.clear();

	for (std::vector< Camera* >::iterator it = _cameras.begin() ; it != _cameras.end(); ++it)
	{
		delete (*it);
	}
	_cameras.clear();

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

void Scene::addCamera (Camera* camera)
{
	_cameras.push_back(camera);
}

Camera* Scene::getCamera(std::string cameraName) const
{
	std::vector<Camera*>::const_iterator it;

	for (it = _cameras.begin(); it != _cameras.end(); ++it)
	{
		if ((*it)->getName() == cameraName)
		{
			return (*it);
		}
	}
	throw ("Camara no encontrada");
}
