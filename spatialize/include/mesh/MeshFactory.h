/*
 * Copyright Regents of the University of Minnesota, 2014.  This software is released under the following license: http://opensource.org/licenses/lgpl-3.0.html.
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#ifndef MESHFACTORY_H_
#define MESHFACTORY_H_

#include "mesh/Mesh.h"
#include <string>

namespace Spatialize {

class MeshFactory;
typedef std::shared_ptr<class MeshFactory> MeshFactoryRef;

class MeshFactory {
public:
	virtual ~MeshFactory() {}

	virtual MeshRef load(const std::string& fileName) = 0;
};

} /* namespace Spatialize */

#endif /* MESHFACTORY_H_ */
