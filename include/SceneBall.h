#ifndef SCENEBALL_H_
#define SCENEBALL_H_

#include <OgreVector3.h>

typedef enum{
	EN_NORMAL = 1,
	EN_POWERUP= 2
}EN_TYPE_BALL;

class SceneBall
{
	public:
		SceneBall(int index, EN_TYPE_BALL type, Ogre::Vector3 position);
		SceneBall(const SceneBall& scBall);

		int getIndex(void) const;
		EN_TYPE_BALL getType(void) const;
		Ogre::Vector3 getPosition(void) const;

		SceneBall& operator= (const SceneBall &scBall);
	private:
		int _index;					// Index of the ball (unique index)
		EN_TYPE_BALL _type;			// Type of ball (normal = 0 or powerup = 1)
		Ogre::Vector3 _position; 	// Ball's position in 3D space
};

#endif /* SCENEBALL_H_ */
