/*
 * Copyright Regents of the University of Minnesota, 2014.  This software is released under the following license: http://opensource.org/licenses/lgpl-3.0.html.
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#include <mesh/concrete/SimpleMesh.h>

namespace Spatialize {

SimpleMesh::SimpleMesh(const std::vector<glm::vec3>& vertices,
		const std::vector<glm::vec3>& normals, const std::vector<int>& indices) : _vertices(vertices), _normals(normals), _indices(indices) {
}

SimpleMesh::~SimpleMesh() {
	// TODO Auto-generated destructor stub
}

void SimpleMesh::draw() {
}

} /* namespace Spatialize */
