#include "LevelInfo.h"

LevelInfo::LevelInfo(string path, string mesh, string xml,
					 float spPlayer, float spRed, float spPink, float spBlue, float spOrange,
					 float spDRed, float spDPink, float spDBlue, float spDOrange,
					 int tRedScatter, int tPinkScatter, int tBlueScatter, int tOrangeScatter,
					 int tRedChase, int tPinkChase, int tBlueChase, int tOrangeChase,
					 int tRedHome, int tPinkHome, int tBlueHome, int tOrangeHome,
					 int tRedScared, int tPinkScared, int tBlueScared, int tOrangeScared,
					 int idLevel, bool comp, int points) : 	_pathFolder(path),
															_meshFile(mesh),
															_xmlFile(xml),
															_playerSpeed(spPlayer),
															_redGhostSpeed(spRed), _pinkGhostSpeed(spPink),	_blueGhostSpeed(spBlue), _orangeGhostSpeed(spOrange),
															 _redGhostSpeedDead(spDRed), _pinkGhostSpeedDead(spDPink),	_blueGhostSpeedDead(spDBlue), _orangeGhostSpeedDead(spDOrange),
															_tRedScatter(tRedScatter), _tPinkScatter(tPinkScatter), _tBlueScatter(tBlueScatter), _tOrangeScatter(tOrangeScatter),
															_tRedChase(tRedChase), _tPinkChase(tPinkChase), _tBlueChase(tBlueChase), _tOrangeChase(tOrangeChase),
															_tRedHome(tRedHome), _tPinkHome(tPinkHome), _tBlueHome(tBlueHome), _tOrangeHome(tOrangeHome),
															_tRedScared(tRedScared), _tPinkScared(tPinkScared), _tBlueScared(tBlueScared), _tOrangeScared(tOrangeScared),
															_idLevel(idLevel),
															_completed(comp),
															_points(points) {}

string LevelInfo::getPathFolder() const
{
	return _pathFolder;
}

string LevelInfo::getMeshFile() const
{
	return _meshFile;
}

string LevelInfo::getXmlFile() const
{
	return _xmlFile;
}

float LevelInfo::getPlayerSpeed() const
{
	return _playerSpeed;
}




float LevelInfo::getRedGhostSpeed() const
{
	return _redGhostSpeed;
}

float LevelInfo::getPinkGhostSpeed() const
{
	return _pinkGhostSpeed;
}

float LevelInfo::getBlueGhostSpeed() const
{
	return _blueGhostSpeed;
}

float LevelInfo::getOrangeGhostSpeed() const
{
	return _orangeGhostSpeed;
}




int LevelInfo::getRedTimeScatter() const
{
	return _tRedScatter;
}

int LevelInfo::getRedTimeChase() const
{
	return _tRedChase;
}

int LevelInfo::getRedTimeHome() const
{
	return _tRedHome;
}

int LevelInfo::getRedTimeScared() const
{
	return _tRedScared;
}




int LevelInfo::getPinkTimeScatter() const
{
	return _tPinkScatter;
}

int LevelInfo::getPinkTimeChase() const
{
	return _tPinkChase;
}

int LevelInfo::getPinkTimeHome() const
{
	return _tPinkHome;
}

int LevelInfo::getPinkTimeScared() const
{
	return _tPinkScared;
}





int LevelInfo::getBlueTimeScatter() const
{
	return _tBlueScatter;
}

int LevelInfo::getBlueTimeChase() const
{
	return _tBlueChase;
}

int LevelInfo::getBlueTimeHome() const
{
	return _tBlueHome;
}

int LevelInfo::getBlueTimeScared() const
{
	return _tBlueScared;
}




int LevelInfo::getOrangeTimeScatter() const
{
	return _tOrangeScatter;
}

int LevelInfo::getOrangeTimeChase() const
{
	return _tOrangeChase;
}

int LevelInfo::getOrangeTimeHome() const
{
	return _tOrangeHome;
}

int LevelInfo::getOrangeTimeScared() const
{
	return _tOrangeScared;
}

