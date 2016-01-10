#include <Frame.h>

Frame::Frame(int index,
			 const Ogre::Vector3& position,
			 const Ogre::Vector4& rotation) : _index(index),
			 	 	 	 	 	 	 	 	  _position(position),
			 	 	 	 	 	 	 	 	  _rotation(rotation) {}

Frame::~Frame () {}

int Frame::getIndex () const
{
	return _index;
}

Ogre::Vector3 Frame::getPosition () const
{
	return _position;
}

Ogre::Vector4 Frame::getRotation () const
{
	return _rotation;
}

