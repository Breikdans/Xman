#include "LevelInfo.h"

LevelInfo::LevelInfo(string path, string mesh, string xml,
					 float spPlayer, float spRed, float spPink, float spBlue, float spOrange,
					 float tRedScatter, float tPinkScatter, float tBlueScatter, float tOrangeScatter,
					 float tRedChase, float tPinkChase, float tBlueChase, float tOrangeChase,
					 float tRedHome, float tPinkHome, float tBlueHome, float tOrangeHome,
					 int idLevel, bool comp, int points) : 	_pathFolder(path),
															_meshFile(mesh),
															_xmlFile(xml),
															_playerSpeed(spPlayer), _redGhostSpeed(spRed), _pinkGhostSpeed(spPink),	_blueGhostSpeed(spBlue), _orangeGhostSpeed(spOrange),
															_tRedScatter(tRedScatter), _tPinkScatter(tPinkScatter), _tBlueScatter(tBlueScatter), _tOrangeScatter(tOrangeScatter),
															_tRedChase(tRedChase), _tPinkChase(tPinkChase), _tBlueChase(tBlueChase), _tOrangeChase(tOrangeChase),
															_tRedHome(tRedHome), _tPinkHome(tPinkHome), _tBlueHome(tBlueHome), _tOrangeHome(tOrangeHome),
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




float LevelInfo::getRedTimeScatter() const
{
	return _tRedScatter;
}

float LevelInfo::getRedTimeChase() const
{
	return _tRedChase;
}

float LevelInfo::getRedTimeHome() const
{
	return _tRedHome;
}

float LevelInfo::getPinkTimeScatter() const
{
	return _tPinkScatter;
}

float LevelInfo::getPinkTimeChase() const
{
	return _tPinkChase;
}

float LevelInfo::getPinkTimeHome() const
{
	return _tPinkHome;
}

float LevelInfo::getBlueTimeScatter() const
{
	return _tBlueScatter;
}

float LevelInfo::getBlueTimeChase() const
{
	return _tBlueChase;
}

float LevelInfo::getBlueTimeHome() const
{
	return _tBlueHome;
}


float LevelInfo::getOrangeTimeScatter() const
{
	return _tOrangeScatter;
}

float LevelInfo::getOrangeTimeChase() const
{
	return _tOrangeChase;
}

float LevelInfo::getOrangeTimeHome() const
{
	return _tOrangeHome;
}


