#include "Camera.h"

Camera::Camera (int index, int fps, std::string name) : _index(index), _fps(fps), _name(name) {}

Camera::~Camera()
{
	for (std::vector< Frame* >::iterator it = _path.begin() ; it != _path.end(); ++it)
	{
		delete (*it);
	}
	_path.clear();
}

void Camera::addFrameToPath (Frame* frame)
{
	_path.push_back(frame);
}

int Camera::getIndex () const
{
	return _index;
}

std::string Camera::getName() const
{
	return _name;
}

int Camera::getFPS () const
{
	return _fps;
}

const std::vector<Frame*> Camera::getPath () const
{
	return _path;
}

Camera::operator std::string() const
{
	std::stringstream r;
	r << "[Camera: " << _index << " FPS: " << _fps << "]";
	return r.str();
}
