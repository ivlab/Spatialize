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
#include <memory>
#include "MVRCore/GraphicsObject.H"

namespace MinVR {
typedef AbstractCameraRef CameraRef;
}

namespace Spatialize {

class Scene;
typedef std::shared_ptr<class Scene> SceneRef;


class Scene : public MinVR::GraphicsObject {
public:
	virtual ~Scene() {}

	virtual const Box& getBoundingBox() = 0;
};

} /* namespace Spatialize */

#endif /* SCENE_H_ */
