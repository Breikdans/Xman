#ifndef LEVELINFO_H_
#define LEVELINFO_H_

#include <string>
using namespace std;

class LevelInfo
{
	public:
		LevelInfo ( string path = "./media/levels/level1/",
					string mesh = "walls.mesh",
					string xml ="output.xml",
					float spPlayer = 2.0f,
					float spRed = 2.1f,
					float spPink = 2.1f,
					float spBlue = 2.0f,
					float spOrange = 2.0f,
					int idLevel = 1, bool comp = false, int points = 0);
		string getPathFolder() const;
		string getMeshFile() const;

		int getId() const;
		bool getCompleted() const;
		int getPoints() const;
		string getXmlFile() const;
		float getPlayerSpeed() const;
	private:
		string _pathFolder;
		string _meshFile;
		string _xmlFile;
		float _playerSpeed;
		float _redGhostSpeed;
		float _pinkGhostSpeed;
		float _blueGhostSpeed;
		float _orangeGhostSpeed;

		int _idLevel;
		bool _completed;
		int _points;
};
#endif /* LEVEL_H_ */
