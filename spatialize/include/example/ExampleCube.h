/*
 * Copyright Regents of the University of Minnesota, 2014.  This software is released under the following license: http://opensource.org/licenses/lgpl-3.0.html.
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#ifndef EXAMPLECUBE_H_
#define EXAMPLECUBE_H_

#include "vrbase/Scene.h"
#include "vrbase/Shader.h"
#include "GL/glew.h"

namespace Spatialize {

class ExampleCube : public vrbase::Scene {
public:
	ExampleCube();
	virtual ~ExampleCube();

	virtual void initContextItem();
	virtual bool updateContextItem(bool changed);
	virtual void cleanupContextItem();
	const vrbase::Box& getBoundingBox();
	void draw(MinVR::RenderDevice& renderDevice);

private:
	MinVR::ContextSpecificPtr<GLuint> _vboId;
	vrbase::Box _boundingBox;
};

} /* namespace Spatialize */

#endif /* EXAMPLECUBE_H_ */
