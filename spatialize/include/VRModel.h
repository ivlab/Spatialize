///*
// * Copyright Regents of the University of Minnesota, 2014.  This software is released under the following license: http://opensource.org/licenses/lgpl-3.0.html.
// * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
// *
// * Code author(s):
// *      Dan Orban (dtorban)
// */
//
//#ifndef VRMODEL_H_
//#define VRMODEL_H_
//
//#include "Scene.h"
//#include "Mesh.h"
//#include "GL/glew.h"
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <glm/ext.hpp>
//#include <SOIL.h>
//
//namespace Spatialize {
//
//class VRModel : public Scene {
//public:
//    VRModel(vector<Mesh> _meshes, glm::vec3 min, glm::vec3 max, std::string directory) : _shader("shader.vs", "shader.frag"),
//      _light("light.vs", "light.frag"), meshes(_meshes) {
//
//        for (GLuint i = 0; i < meshes.size(); i++) {
//            for (GLuint j = 0; j < meshes[i].textures.size(); j++) {
//                Texture& texture = meshes[i].textures[j];
//
//                std::string filename = string(texture.path.C_Str());
//                filename = directory + '/' + filename;
//                GLuint textureID;
//                glGenTextures(1, &textureID);
//                int width,height;
//                unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
//                // Assign texture to ID
//                glBindTexture(GL_TEXTURE_2D, textureID);
//                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
//                glGenerateMipmap(GL_TEXTURE_2D);
//
//                // Parameters
//                glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
//                glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
//                glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
//                glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//                glBindTexture(GL_TEXTURE_2D, 0);
//                SOIL_free_image_data(image);
//
//                texture.id = textureID;
//            }
//
//            meshes[i].setupMesh();
//        }
//
//        _boundingBox = Box(min, max);
//    }
//    virtual ~VRModel();
//
//    const Box& getBoundingBox();
//    void draw(float time, MinVR::CameraRef camera, MinVR::WindowRef window, glm::mat4 objectToWorld);
//
//private:
//    //GLuint VBO, VAO, EBO, texture1, texture2;
//    vector<Mesh> meshes;
//
//    Shader _shader;
//    Shader _light;
//    Box _boundingBox;
//};
//
//} /* namespace Spatialize */
//
//#endif /* VRMODEL_H_ */
