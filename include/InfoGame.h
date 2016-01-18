#ifndef INFOGAME_H_
#define INFOGAME_H_

#include <Ogre.h>
#include <OgreSingleton.h>
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

		std::string getCurrentMeshFile(void);

		void setScene(const Scene &sc);
		// Heredados de Ogre::Singleton.
		static InfoGame& getSingleton ();
		static InfoGame* getSingletonPtr ();

	private:
		int _lifes;
		int _currentLevel;
		int _totalPoints;
		std::vector<LevelInfo> _lstLevels;
		Scene* _scene;

		void InitListLevels(void);
};
#endif /* INFOGAME_H_ */
