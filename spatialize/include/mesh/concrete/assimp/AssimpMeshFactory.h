/*
 * Copyright Regents of the University of Minnesota, 2014.  This software is released under the following license: http://opensource.org/licenses/lgpl-3.0.html.
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#ifndef ASSIMPMESHFACTORY_H_
#define ASSIMPMESHFACTORY_H_

#include "mesh/MeshFactory.h"

namespace Spatialize {

class AssimpMeshFactory : public MeshFactory {
public:
	AssimpMeshFactory();
	virtual ~AssimpMeshFactory();

	MeshRef load(const std::string& fileName);
};

} /* namespace Spatialize */

#endif /* ASSIMPMESHFACTORY_H_ */
