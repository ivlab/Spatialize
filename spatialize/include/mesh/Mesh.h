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
#include <vector>
#include <glm/glm.hpp>

namespace Spatialize {

class Mesh;
typedef std::shared_ptr<class Mesh> MeshRef;

class Mesh {
public:
	Mesh() : _versionId(0) {}
	virtual ~Mesh() {}

	virtual const std::vector<int>& getIndices() const = 0;
	virtual void setIndices(const std::vector<int>& indices) = 0;
	virtual const std::vector<glm::vec3>& getNormals() const = 0;
	virtual void setNormals(const std::vector<glm::vec3>& normals) = 0;
	virtual const std::vector<glm::vec3>& getVertices() const = 0;
	virtual void setVertices(const std::vector<glm::vec3>& vertices) = 0;

	virtual int getVersionId() const {
		return _versionId;
	}

protected:
	void incrementVersion()
	{
		_versionId++;
	}

private:
	int _versionId;
};

} /* namespace Spatialize */

#endif /* MESH_H_ */
