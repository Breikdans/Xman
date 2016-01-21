#include "LevelInfo.h"

LevelInfo::LevelInfo(string path, string mesh, string xml,
								int id, bool comp, int points) : _pathFolder(path),
																				_meshFile(mesh),
																				_xmlFile(xml),
																				_id(id),
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
