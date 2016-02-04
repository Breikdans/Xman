#include "LevelInfo.h"

LevelInfo::LevelInfo(string path, string mesh, string xml,
					 float spPlayer, float spRed, float spPink, float spBlue, float spOrange,
					 int idLevel, bool comp, int points) : 	_pathFolder(path),
														_meshFile(mesh),
														_xmlFile(xml),
														_playerSpeed(spPlayer),
														_redGhostSpeed(spRed),
														_pinkGhostSpeed(spPink),
														_blueGhostSpeed(spBlue),
														_orangeGhostSpeed(spOrange),
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
