#ifndef FRAME_H
#define FRAME_H

#include <OgreVector3.h>
#include <OgreVector4.h>

class Frame
{
	public:
		Frame (int index, const Ogre::Vector3& position, const Ogre::Vector4& rotation);
		~Frame ();

		int getIndex () const;
		Ogre::Vector3 getPosition () const;
		Ogre::Vector4 getRotation () const;

	private:
		int _index;					// Frame index
		Ogre::Vector3 _position;	// Camera position in the frame index
		Ogre::Vector4 _rotation;	// Camera rotation in the frame index
};

#endif
