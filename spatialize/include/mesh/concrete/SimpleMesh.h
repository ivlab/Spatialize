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

namespace Spatialize {

class SimpleMesh : public Mesh {
public:
	SimpleMesh(const std::vector<glm::vec3>& vertices, const std::vector<glm::vec3>& normals, const std::vector<int>& indices);
	virtual ~SimpleMesh();

	const std::vector<int>& getIndices() const {
		return _indices;
	}

	void setIndices(const std::vector<int>& indices) {
		_indices = indices;
	}

	const std::vector<glm::vec3>& getNormals() const {
		return _normals;
	}

	void setNormals(const std::vector<glm::vec3>& normals) {
		_normals = normals;
	}

	const std::vector<glm::vec3>& getVertices() const {
		return _vertices;
	}

	void setVertices(const std::vector<glm::vec3>& vertices) {
		_vertices = vertices;
	}

private:
	std::vector<glm::vec3> _vertices;
	std::vector<glm::vec3> _normals;
	std::vector<int> _indices;
};

} /* namespace Spatialize */

#endif /* SIMPLEMESH_H_ */
