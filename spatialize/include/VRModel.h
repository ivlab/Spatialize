/*
 * Copyright Regents of the University of Minnesota, 2014.  This software is released under the following license: http://opensource.org/licenses/lgpl-3.0.html.
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 *      Dan Orban (dtorban)
 */

#ifndef VRMODEL_H_
#define VRMODEL_H_

#include "Scene.h"
#include "Mesh.h"
#include "GL/glew.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>

namespace Spatialize {

class VRModel : public Scene {
public:
    VRModel(vector<Mesh>& _meshes, glm::vec3 min, glm::vec3 max) : _shader("shader.vs", "shader.frag"), 
      _light("light.vs", "light.frag"), meshes(_meshes) {
        _boundingBox = Box(min, max);
    }
    virtual ~VRModel();

    const Box& getBoundingBox();
    void draw(float time, MinVR::CameraRef camera, MinVR::WindowRef window, glm::mat4 objectToWorld);

private:
    //GLuint VBO, VAO, EBO, texture1, texture2;
    vector<Mesh>& meshes;

    Shader _shader;
    Shader _light;
    Box _boundingBox;
};

} /* namespace Spatialize */

#endif /* VRMODEL_H_ */
