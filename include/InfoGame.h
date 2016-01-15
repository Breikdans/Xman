#ifndef INFOGAME_H_
#define INFOGAME_H_

#include "OGRE/Ogre.h"
#include "LevelInfo.h"
#include "Scene.h"

class InfoGame : public Ogre::Singleton<InfoGame>
{
	public:
		InfoGame(int lifes = 3, int currentLevel = 1, int totalPoints = 0);

		LevelInfo& getLevel(int level);

		int getLifes() const {return _lifes;}
		int getCurrentLevel() const {return _currentLevel;}
		int getTotalPoints() const {return _totalPoints;}

		void setScene(const Scene &sc);

	private:
		int _lifes;
		int _currentLevel;
		int _totalPoints;
		std::vector<LevelInfo> _lstLevels;
		Scene* _scene;
};
#endif /* INFOGAME_H_ */
