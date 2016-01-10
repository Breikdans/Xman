#include "SceneBall.h"

SceneBall::SceneBall(int index, EN_TYPE_BALL type, Ogre::Vector3 position) : _index(index), _type(type), _position(position) {}

SceneBall::SceneBall(const SceneBall& scBall)
{
	*this = scBall;
}

int SceneBall::getIndex(void) const
{
	return _index;
}

EN_TYPE_BALL SceneBall::getType(void) const
{
	return _type;
}

Ogre::Vector3 SceneBall::getPosition(void) const
{
	return _position;
}

SceneBall& SceneBall::operator= (const SceneBall &scBall)
{
	_index 		= scBall._index;
	_type		= scBall._type;
	_position	= scBall._position;

	return *this;
}
