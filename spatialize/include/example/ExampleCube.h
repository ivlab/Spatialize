/*
 * Copyright Regents of the University of Minnesota, 2014.  This software is released under the following license: http://opensource.org/licenses/lgpl-3.0.html.
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#ifndef EXAMPLECUBE_H_
#define EXAMPLECUBE_H_

#include "Scene.h"
#include "Mesh.h"
#include "GL/glew.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Spatialize {

class ExampleCube : public Scene {
public:
	ExampleCube(GLchar *path);
	virtual ~ExampleCube();

	const Box& getBoundingBox();
	void draw(float time, MinVR::CameraRef camera, MinVR::WindowRef window, Shader shader);

private:
	//GLuint VBO, VAO, EBO, texture1, texture2;
    vector<Mesh> meshes;
    vector<Texture> textures_loaded;
	std::string directory;
    glm::vec3 min, max;
    void loadModel(std::string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

    Box _boundingBox;
};

} /* namespace Spatialize */

#endif /* EXAMPLECUBE_H_ */
