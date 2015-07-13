/*
 * Copyright Regents of the University of Minnesota, 2014.  This software is released under the following license: http://opensource.org/licenses/lgpl-3.0.html.
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#ifndef SCENE_H_
#define SCENE_H_

#include "MVRCore/AbstractCamera.H"
#include "MVRCore/AbstractWindow.H"
#include "Box.h"
#include "Shader.h"
#include <memory>

namespace MinVR {
typedef AbstractCameraRef CameraRef;
}

namespace Spatialize {

class Scene;
typedef std::shared_ptr<class Scene> SceneRef;


class Scene {
public:
	virtual ~Scene() {}

	virtual const Box& getBoundingBox() = 0;
	virtual void draw(float time, MinVR::CameraRef camera, MinVR::WindowRef window, Shader shader) = 0;
};

} /* namespace Spatialize */

#endif /* SCENE_H_ */
