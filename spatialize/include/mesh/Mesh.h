/*
 * Copyright Regents of the University of Minnesota, 2014.  This software is released under the following license: http://opensource.org/licenses/lgpl-3.0.html.
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#ifndef MESH_H_
#define MESH_H_

#include <memory>

namespace Spatialize {

class Mesh;
typedef std::shared_ptr<class Mesh> MeshRef;

class Mesh {
public:
	virtual ~Mesh() {}

	virtual void draw() = 0;
};

} /* namespace Spatialize */

#endif /* MESH_H_ */
