#include "InfoGame.h"

template<> InfoGame* Ogre::Singleton<InfoGame>::msSingleton = 0;

InfoGame::InfoGame(int lifes, int currentLevel, int totalPoints) : _lifes(lifes), _currentLevel(currentLevel), _totalPoints(totalPoints)
{
	_scene = NULL;
	InitListLevels();
}

LevelInfo& InfoGame::getLevel(int level)
{
	return _lstLevels.at(level-1);	// -1 para ajustar a indices del Vector
}

void InfoGame::setScene(const Scene &sc)
{
	if(_scene != 0)	// comprobamos si el puntero es nulo, antes de liberarlo
		delete _scene;

	_scene = new Scene(sc);
}

void InfoGame::InitListLevels(void)
{
	// TODO: en lugar de recuperar la configuracion de niveles de un fichero, de momento lo metemos en un tabla
	LevelInfo tbl_Levels[] = {
								LevelInfo("./media/levels/level1/", "walls.mesh", "output.xml",
										  2.3f,
										  2.3f, 2.3f, 2.3f, 2.3f,
										  7, 7, 7, 7,
										  20, 18, 18, 18,
										  1, 2, 3, 4,
										  8, 8, 8, 8,
										  1, false, 0),
								LevelInfo("./media/levels/level2/", "lava.mesh", "output.xml"
										,3.0f,
										2.6f, 2.6f, 2.5f, 2.5f,
										7,7,7,7,
										 9,9,9,9,
										  0,3,4,10,
										  5,5,5,5,
										  2, false, 0)
							 };

	int lvls = sizeof(tbl_Levels) / sizeof(tbl_Levels[0]);

	for(int i = 0; i < lvls; i++)
		_lstLevels.push_back(tbl_Levels[i]);

}

InfoGame* InfoGame::getSingletonPtr ()
{
	return msSingleton;
}

InfoGame& InfoGame::getSingleton ()
{
	assert(msSingleton);
	return *msSingleton;
}

std::string InfoGame::getCurrentMeshFile(void)
{
	std::string mesh;
	mesh = getLevel(_currentLevel).getMeshFile();
	return mesh;
}

int InfoGame::getTotalBalls(void) const
{
	return _totalBalls;
}

int InfoGame::getBallsLeft(void) const
{
	return _ballsLeft;
}

void InfoGame::decBalls(int i)
{
	_ballsLeft -= i;
}

void InfoGame::decLifes(int i)
{
	_lifes -= i;
}

void InfoGame::addPoints(int i)
{
	_totalPoints += i;
}


