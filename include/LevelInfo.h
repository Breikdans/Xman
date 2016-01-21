#ifndef LEVELINFO_H_
#define LEVELINFO_H_

#include <string>
using namespace std;

class LevelInfo
{
	public:
		LevelInfo(string path = "./media/levels/level1/",
					    string mesh = "walls.mesh",
					    string xml ="output.xml",
					    int id = 1, bool comp = false, int points = 0);
		string getPathFolder() const;
		string getMeshFile() const;

		int getId() const;
		bool getCompleted() const;
		int getPoints() const;
		string getXmlFile() const;
	private:
		string _pathFolder;
		string _meshFile;
		string _xmlFile;

		int _id;
		bool _completed;
		int _points;
};
#endif /* LEVEL_H_ */
