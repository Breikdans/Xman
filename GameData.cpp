#include "GameData.h"

template<> GameData* Ogre::Singleton<GameData>::msSingleton = 0;

GameData& GameData::getSingleton ()
{
	return msSingleton;
}

GameData* GameData::getSingletonPtr ()
{
	assert(msSingleton);
	return *msSingleton;
}
