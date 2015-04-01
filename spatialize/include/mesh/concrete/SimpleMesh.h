/*
 * Copyright Regents of the University of Minnesota, 2014.  This software is released under the following license: http://opensource.org/licenses/lgpl-3.0.html.
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#ifndef SIMPLEMESH_H_
#define SIMPLEMESH_H_

#include "mesh/Mesh.h"
#include "Scene.h"
#include <vector>

namespace Spatialize {

class SimpleMesh : public Mesh {
public:
	SimpleMesh(const std::vector<glm::vec3>& vertices, const std::vector<glm::vec3>& normals, const std::vector<int>& indices);
	virtual ~SimpleMesh();

	void draw();

private:
	std::vector<glm::vec3> _vertices;
	std::vector<glm::vec3> _normals;
	std::vector<int> _indices;
};

} /* namespace Spatialize */

#endif /* SIMPLEMESH_H_ */
