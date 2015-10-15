/*
 * Copyright Regents of the University of Minnesota, 2014.  This software is released under the following license: http://opensource.org/licenses/lgpl-3.0.html.
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#ifndef SPATIALIZEAPP_H_
#define SPATIALIZEAPP_H_

#include "GL/glew.h"
#include "MVRCore/AbstractMVRApp.H"
#include "MVRCore/AbstractCamera.H"
#include "MVRCore/AbstractWindow.H"
#include "MVRCore/Event.H"
#include <GLFW/glfw3.h>
#include <vector>
#include <map>
#include <cmath>
#include "Scene.h"
#include "MVRCore/Thread.h"
#include "Mesh.h"

namespace Spatialize {

class SpatializeApp : public MinVR::AbstractMVRApp {
public:
	SpatializeApp(GLchar *path);
	virtual ~SpatializeApp();

	void doUserInputAndPreDrawComputation(const std::vector<MinVR::EventRef> &events, double synchronizedTime);
	void initializeContextSpecificVars(int threadId, MinVR::WindowRef window);
	void postInitialization();
	void drawGraphics(int threadId, MinVR::AbstractCameraRef camera, MinVR::WindowRef window) {}
	void drawGraphics(MinVR::RenderDevice& renderDevice);

private:
	void initGL();
	void initVBO(int threadId);
	void initLights();

	//std::map<int, SceneRef> _scene;
	SceneRef _scene;
	float _startTime;
	int _numFrames;
	float _time;
    MinVR::Mutex _mutex;
    bool _touch0;
    bool _touch1;
    glm::vec2 _pos0;
    glm::vec2 _scale0;
    glm::vec2 _scale1;
    glm::vec3 _tempTrans;
    glm::vec3 _translation;
    float _scale;
    float _startSize;
    float _tempScale;
    GLchar* _path;

    void loadModel(std::string path);
    void processNodeTextures(aiNode *node, const aiScene *scene);
    vector<Texture> processMeshTextures(aiMesh *mesh, const aiScene *scene);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

    vector<Mesh> _meshes;
    vector<aiMesh*> _aimeshes;
    vector<Texture> _textures_loaded;
    std::string directory;
    glm::vec3 min, max;
};

}

#endif /* SPATIALIZEAPP_H_ */
