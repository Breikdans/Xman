#include "Camera.h"

Camera::Camera (int index, int fps, std::string name) : _index(index), _fps(fps), _name(name) {}

Camera::Camera (const Camera& C)
{
	*this = C;
}

Camera& Camera::operator=(const Camera& C)
{
	_index 	= C._index;			// Camera Index
	_fps	= C._fps;			// Frame rate per second of the camera
	_name	= C._name;			// Camera name

	// Path of the camera, giving in frames
	std::vector<Frame*>::const_iterator that_it = C._path.begin();
	for(; that_it != C._path.end(); that_it++)
	{
		Frame *temp = new Frame(**that_it);
		_path.push_back(temp);
	}

	return *this;
}

Camera::~Camera()
{
	for (std::vector<Frame*>::iterator it = _path.begin() ; it != _path.end(); ++it)
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

Frame Camera::getFrame(int index)
{
	std::vector<Frame*>::iterator it;

	Frame F(-1);
	for (it = _path.begin(); it != _path.end(); ++it)
	{
		if ((*it)->getIndex() == index)
		{
			F = *(*it);
			break;
		}
	}

	return F;
}

Camera::operator std::string() const
{
	std::stringstream r;
	r << "[Camera: " << _index << " FPS: " << _fps << "]";
	return r.str();
}
