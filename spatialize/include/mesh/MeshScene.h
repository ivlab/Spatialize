/*
 * Copyright Regents of the University of Minnesota, 2014.  This software is released under the following license: http://opensource.org/licenses/lgpl-3.0.html.
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#ifndef MESHSCENE_H_
#define MESHSCENE_H_

#include "Scene.h"
#include "mesh/Mesh.h"
#include "GL/glew.h"

namespace Spatialize {

class MeshScene : public Scene {
public:
	MeshScene(MeshRef mesh);
	virtual ~MeshScene();

	void draw(float time, MinVR::CameraRef camera, MinVR::WindowRef window);

private:
	MeshRef _mesh;
};

} /* namespace Spatialize */

#endif /* MESHSCENE_H_ */
