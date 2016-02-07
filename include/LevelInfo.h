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
					int tRedScatter = 7, int tPinkScatter = 7, int tBlueScatter = 7, int tOrangeScatter = 7,
					int tRedChase = 8, int tPinkChase = 8, int tBlueChase = 12, int tOrangeChase = 20,
					int tRedHome = 0, int tPinkHome = 3, int tBlueHome = 4, int tOrangeHome = 10,
					int tRedScared= 5, int tPinkScared = 5, int tBlueScared = 5, int tOrangeScared = 5,
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

		int _tRedScatter;
		int _tPinkScatter;
		int _tBlueScatter;
		int _tOrangeScatter;

		int _tRedChase;
		int _tPinkChase;
		int _tBlueChase;
		int _tOrangeChase;

		int _tRedHome;
		int _tPinkHome;
		int _tBlueHome;
		int _tOrangeHome;

		int _tRedScared;
		int _tPinkScared;
		int _tBlueScared;
		int _tOrangeScared;

		int _idLevel;
		bool _completed;
		int _points;
};
#endif /* LEVEL_H_ */
