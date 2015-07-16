/*
 * Copyright Regents of the University of Minnesota, 2014.  This software is released under the following license: http://opensource.org/licenses/lgpl-3.0.html.
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#ifndef EXAMPLECUBE_H_
#define EXAMPLECUBE_H_

#include "Scene.h"
#include "Shader.h"
#include "GL/glew.h"

namespace Spatialize {

class ExampleCube : public Scene {
public:
	ExampleCube();
	virtual ~ExampleCube();

	const Box& getBoundingBox();
	void draw(float time, MinVR::CameraRef camera, MinVR::WindowRef window, Shader shader);

private:
	GLuint _vboId;
	Box _boundingBox;
};

} /* namespace Spatialize */

#endif /* EXAMPLECUBE_H_ */
