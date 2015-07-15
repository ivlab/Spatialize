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
#include <glm/glm.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "MVRCore/Event.H"
#include <GLFW/glfw3.h>
#include <vector>
#include <map>
#include <cmath>
#include "Scene.h"
#include "MVRCore/Thread.h"

namespace Spatialize {

class SpatializeApp : public MinVR::AbstractMVRApp {
public:
	SpatializeApp(GLchar *path);
	virtual ~SpatializeApp();

	void doUserInputAndPreDrawComputation(const std::vector<MinVR::EventRef> &events, double synchronizedTime);
	void initializeContextSpecificVars(int threadId, MinVR::WindowRef window);
	void postInitialization();
	void drawGraphics(int threadId, MinVR::AbstractCameraRef camera, MinVR::WindowRef window);

private:
	void initGL();
	void initVBO(int threadId);
	void initLights();

	std::map<int, SceneRef> _scene;
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
};

}

#endif /* SPATIALIZEAPP_H_ */
