/*
 * Copyright Regents of the University of Minnesota, 2014.  This software is released under the following license: http://opensource.org/licenses/lgpl-3.0.html.
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#include <mesh/MeshScene.h>

namespace Spatialize {

MeshScene::MeshScene(MeshRef mesh) : _mesh(mesh) {
}

MeshScene::~MeshScene() {
	// TODO Auto-generated destructor stub
}

void MeshScene::draw(float time, MinVR::CameraRef camera,
		MinVR::WindowRef window) {
}

} /* namespace Spatialize */



