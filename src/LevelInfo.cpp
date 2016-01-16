#include "LevelInfo.h"

LevelInfo::LevelInfo(string path, string mesh, int id, bool comp, int points) : _pathFolder(path),
																				_meshFile(mesh),
																				_id(id),
																				_completed(comp),
																				_points(points) {}

string LevelInfo::getPathFolder() const
{
	return _pathFolder;
}
