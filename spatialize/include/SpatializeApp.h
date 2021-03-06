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
//#include <GLFW/glfw3.h>
#include <vector>
#include <map>
#include <cmath>
#include "vrbase/Scene.h"
#include "MVRCore/Thread.h"
#include "vrbase/Mesh.h"
#include "vrbase/Shader.h"
#include "vrbase/Texture.h"
#include "vrbase/scene/CompositeScene.h"
#include "vrbase/EventListener.h"

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

	double getSyncTime() const {
		return _syncTime;
	}

	void setSyncTime(double syncTime) {
		_syncTime = syncTime;
	}

private:
	void initGL();
	void initVBO(int threadId);

	//std::map<int, SceneRef> _scene;
	vrbase::CompositeSceneRef _scene;
	float _startTime;
	int _numFrames;
	float _time;
    MinVR::Mutex _mutex;
    bool _touch0;
    bool _touch1;
    bool _touch2;
    glm::vec2 _pos0;
    glm::vec2 _scale0;
    glm::vec2 _scale1;
    glm::vec3 _tempTrans;
    glm::vec3 _translation;
    glm::vec2 _vertPos;
    double _rotationAngle;
    float _scale;
    float _startSize;
    float _tempScale;
    GLchar* _path;
    double _syncTime;
    vrbase::ShaderRef _shader;
    vrbase::TextureRef _texture;
    glm::dmat4 _trans;
    glm::dmat4 _rot;
    glm::dmat4 _scaleMat;
    std::vector<vrbase::EventListenerRef> _eventListeners;
//    std::map<std::string, TextureRef> _textureMap;

    std::vector<vrbase::MeshRef> loadModel(std::string path);

    /*void loadModel(std::string path);
    void processNodeTextures(aiNode *node, const aiScene *scene);
    vector<Texture> processMeshTextures(aiMesh *mesh, const aiScene *scene);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

    vector<Mesh> _meshes;
    vector<aiMesh*> _aimeshes;
    vector<Texture> _textures_loaded;
    std::string directory;
    glm::vec3 min, max;*/
};

}

#endif /* SPATIALIZEAPP_H_ */
