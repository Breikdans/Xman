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
					float tRedScatter = 7.0f, float tPinkScatter = 7.0f, float tBlueScatter = 7.0f, float tOrangeScatter = 7.0f,
					float tRedChase = 20.0f, float tPinkChase = 20.0f, float tBlueChase = 20.0f, float tOrangeChase = 20.0f,
					float tRedHome = 0.0f, float tPinkHome = 3.0f, float tBlueHome = 4.0f, float tOrangeHome = 10.0f,
					int idLevel = 1, bool comp = false, int points = 0);
		string getPathFolder() const;
		string getMeshFile() const;

		int getId() const;
		bool getCompleted() const;
		int getPoints() const;
		string getXmlFile() const;
		float getPlayerSpeed() const;
		float getRedGhostSpeed() const;
		float getPinkGhostSpeed() const;
		float getBlueGhostSpeed() const;
		float getOrangeGhostSpeed() const;

		float getRedTimeScatter() const;
		float getRedTimeChase() const;
		float getRedTimeHome() const;

		float getPinkTimeScatter() const;
		float getPinkTimeChase() const;
		float getPinkTimeHome() const;

		float getBlueTimeScatter() const;
		float getBlueTimeChase() const;
		float getBlueTimeHome() const;

		float getOrangeTimeScatter() const;
		float getOrangeTimeChase() const;
		float getOrangeTimeHome() const;

	private:
		string _pathFolder;
		string _meshFile;
		string _xmlFile;
		float _playerSpeed;
		float _redGhostSpeed;
		float _pinkGhostSpeed;
		float _blueGhostSpeed;
		float _orangeGhostSpeed;

		float _tRedScatter;
		float _tPinkScatter;
		float _tBlueScatter;
		float _tOrangeScatter;

		float _tRedChase;
		float _tPinkChase;
		float _tBlueChase;
		float _tOrangeChase;

		float _tRedHome;
		float _tPinkHome;
		float _tBlueHome;
		float _tOrangeHome;

		int _idLevel;
		bool _completed;
		int _points;
};
#endif /* LEVEL_H_ */
