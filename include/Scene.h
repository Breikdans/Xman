#ifndef SCENE_H_
#define SCENE_H_

#include "Graph.h"
#include "Camera.h"

class Scene
{
	public:
		Scene();
		Scene(const Scene&);
		Scene& operator=(const Scene&);
		~Scene();

		void addCamera (Camera* camera);
		Camera* getCamera(std::string cameraName) const;

		std::vector<Camera*> getCameras () const 	{ return _cameras; }
		Graph* getGraph ()  						{ return _graph; }
	private:
		Graph* _graph;						// Graph describing the vertexes and connection between them (edges)

		std::vector<Camera*> _cameras; 		// Vector containing the game cameras
};

#endif /* SCENE_H_ */
