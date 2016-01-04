#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <Ogre.h>
#include <OgreSingleton.h>

class GameData : public Ogre::Singleton<GameData>
{
	public:
		GameData(int points=0, std::string player = "Player1", unsigned int lifes = 3, unsigned int currentLevel = 1) {}

		// Heredados de Ogre::Singleton.
		static GameData& getSingleton ();
		static GameData* getSingletonPtr ();

		unsigned int getPoints() const 			{return _points;}
		std::string getPlayer() const 			{return _player;}
		unsigned int getLifes() const 			{return _lifes;}
		unsigned int getCurrentLevel() const 	{return _currentLevel;}

		void setPoints(unsigned int p) 			{_points = p;}
		void setPlayer(std::string p) 			{_player = p;}
		void setLifes(unsigned int l)			{_lifes = l;}
		void setCurrentLevel(unsigned int l)	{_currentLevel = l;}
	private:
		unsigned int _points;
		std::string  _player;
		unsigned int _lifes;
		unsigned int _currentLevel;
};

#endif
