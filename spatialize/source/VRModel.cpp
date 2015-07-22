/*
 * Copyright Regents of the University of Minnesota, 2014.  This software is released under the following license: http://opensource.org/licenses/lgpl-3.0.html.
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 *      Dan Orban (dtorban)
 */

#include <VRModel.h>

#include "MVRCore/AbstractMVRApp.H"
#include "MVRCore/AbstractCamera.H"
#include "MVRCore/AbstractWindow.H"
#include "MVRCore/Event.H"
#include <GLFW/glfw3.h>


namespace Spatialize {

VRModel::~VRModel() {

}

const Box& VRModel::getBoundingBox() {
    return _boundingBox;
}

} /* namespace Spatialize */

void Spatialize::VRModel::draw(float time, MinVR::CameraRef camera,
        MinVR::WindowRef window, glm::mat4 objectToWorld) {

    MinVR::CameraOffAxis* offAxisCamera = dynamic_cast<MinVR::CameraOffAxis*>(camera.get());

    glm::vec3 pointLightPositions[] = {
        glm::vec3(2.3f, -1.6f, -3.0f),
        glm::vec3(-1.7f, 0.9f, 1.0f)
    };


    /*UNCOMMENT FOR DEBUGGING BACKGROUND 
    (since by default a textureless model will match the background)*/
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _shader.Use();    

    glUniform3f(glGetUniformLocation(_shader.Program, "viewPos"), offAxisCamera->getLookVector().x, offAxisCamera->getLookVector().y, offAxisCamera->getLookVector().z);

    glUniform3f(glGetUniformLocation(_shader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);     
    glUniform3f(glGetUniformLocation(_shader.Program, "pointLights[0].ambient"), 0.05f, 0.05f, 0.05f);       
    glUniform3f(glGetUniformLocation(_shader.Program, "pointLights[0].diffuse"), 1.0f, 1.0f, 1.0f); 
    glUniform3f(glGetUniformLocation(_shader.Program, "pointLights[0].specular"), 1.0f, 1.0f, 1.0f);
    glUniform1f(glGetUniformLocation(_shader.Program, "pointLights[0].constant"), 1.0f);
    glUniform1f(glGetUniformLocation(_shader.Program, "pointLights[0].linear"), 0.009);
    glUniform1f(glGetUniformLocation(_shader.Program, "pointLights[0].quadratic"), 0.0032);      
    // Point light 2
    glUniform3f(glGetUniformLocation(_shader.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);     
    glUniform3f(glGetUniformLocation(_shader.Program, "pointLights[1].ambient"), 0.05f, 0.05f, 0.05f);       
    glUniform3f(glGetUniformLocation(_shader.Program, "pointLights[1].diffuse"), 1.0f, 1.0f, 1.0f); 
    glUniform3f(glGetUniformLocation(_shader.Program, "pointLights[1].specular"), 1.0f, 1.0f, 1.0f);
    glUniform1f(glGetUniformLocation(_shader.Program, "pointLights[1].constant"), 1.0f);
    glUniform1f(glGetUniformLocation(_shader.Program, "pointLights[1].linear"), 0.009);
    glUniform1f(glGetUniformLocation(_shader.Program, "pointLights[1].quadratic"), 0.0032);  

    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;
    
    model = objectToWorld;
    view = (glm::mat4) offAxisCamera->getLastAppliedViewMatrix(); //glm::translate(view, glm::vec3(0.0f, -8.0f, -20.0f));
    projection = (glm::mat4) offAxisCamera->getLastAppliedProjectionMatrix(); //glm::perspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
    
    // Get their uniform location
    GLint viewLoc = glGetUniformLocation(_shader.Program, "view");
    GLint projLoc = glGetUniformLocation(_shader.Program, "projection");
    GLint modelLoc = glGetUniformLocation(_shader.Program, "model");
    // Pass the matrices to the shader
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    // Note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
    
    for (GLuint i = 0; i < this->meshes.size(); i++) {
        this->meshes[i].Draw(_shader);
    }

    _light.Use();
    glUniformMatrix4fv(glGetUniformLocation(_light.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(_light.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
}