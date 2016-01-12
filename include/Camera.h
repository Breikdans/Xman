#ifndef CAMERA_H_
#define CAMERA_H_

#include "Frame.h"

class Camera
{
	public:
		Camera (int index, int fps, std::string name);
		~Camera();

		void addFrameToPath (Frame* frame);
		int getIndex () const;
		int getFPS () const;
		std::string getName () const;
		const std::vector<Frame*> getPath () const;

		operator std::string() const;

	private:
		std::string _name;					// Camera name
		int _index;					// Camera Index
		int _fps;					// Frame rate per second of the camera
		std::vector<Frame*> _path;	// Path of the camera, giving in frames
};

#endif /* CAMERA_H_ */
