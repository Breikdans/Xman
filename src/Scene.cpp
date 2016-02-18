#include "Scene.h"

Scene::Scene()
{
	_graph = new Graph();
}

Scene::Scene(const Scene& S)
{
	*this = S;
}

//Scene& Scene::operator=(const Scene &S) : _cameras(S._cameras.size()), _balls(S._balls.size())	// inicializador constructor copia para C++11, reserva espacio para vectores
Scene& Scene::operator=(const Scene &S)
{
//	if (_graph != NULL)
//		delete _graph;

	_graph 		= new Graph(*(S._graph));

    vector<Camera*>::const_iterator that_c_it = S._cameras.begin();	// iterador constante para el vector origen (vector recibido)

	for(; that_c_it != S._cameras.end(); that_c_it++)
	{
		_cameras.push_back(new Camera(**that_c_it));
	}

	return *this;
}

Scene::~Scene()
{
	for (std::vector< Camera* >::iterator it = _cameras.begin() ; it != _cameras.end(); ++it)
	{
		delete (*it);
	}
	_cameras.clear();

	delete _graph;
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
