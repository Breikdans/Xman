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
		int getTotalBalls(void) const;
		int getBallsLeft(void) const;
		void decBalls(int i = 1);
		void decLifes(int i = 1);

		std::string getCurrentMeshFile(void);

		Scene* getScene()  { return _scene; }
		void setScene(const Scene &sc);
		void addPoints(int i = 5);
		// Heredados de Ogre::Singleton.
		static InfoGame& getSingleton ();
		static InfoGame* getSingletonPtr ();

	private:
		int _lifes;
		int _currentLevel;
		int _totalPoints;
		int _ballsLeft;						// Balls left to complete level
		int _totalBalls;					// Total of balls in the beginning of the scene
		std::vector<LevelInfo> _lstLevels;
		Scene* _scene;

		void InitListLevels(void);
};
#endif /* INFOGAME_H_ */
