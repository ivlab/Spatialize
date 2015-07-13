/*
 * Copyright Regents of the University of Minnesota, 2014.  This software is released under the following license: http://opensource.org/licenses/lgpl-3.0.html.
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#include <SpatializeApp.h>
#include "example/ExampleCube.h"
#include "MVRCore/StringUtils.H"

using namespace MinVR;

namespace Spatialize {

SpatializeApp::SpatializeApp() : MinVR::AbstractMVRApp() {
	_startTime = -1;
	_numFrames = 0;
	_touch0 = false;
	_touch1 = false;
	_tempTrans = glm::vec3(0.0f);
	_translation = glm::vec3(0.0f);
	_startSize = 1.0f;
	_tempScale = 1.0f;
	_scale = 1.0f;
}

SpatializeApp::~SpatializeApp() {
}

void SpatializeApp::doUserInputAndPreDrawComputation(
		const std::vector<MinVR::EventRef>& events, double synchronizedTime) {
	for(int i=0; i < events.size(); i++) {
		std::cout << events[i]->getName() <<std::endl;

		//std::string down = ;
		std::string name = events[i]->getName();
		if (MinVR::startsWith(name, "Touch_Cursor_Down0"))
		{
			_touch0 = true;
			_pos0 = events[i]->get2DData();
			_scale0 = _pos0;
		}
		else if (MinVR::startsWith(name, "Touch_Cursor_Down1"))
		{
			_touch1 = true;
			_scale1 = events[i]->get2DData();
			_startSize = glm::length((_scale1 - _scale0));
		}
		else if (_touch0 && MinVR::startsWith(name, "Touch_Cursor_Move0"))
		{
			glm::dvec4 data = events[i]->get4DData();
			_scale0 = glm::vec2(data.x, data.y);
			if (!_touch1)
			{
				glm::vec2 trans0 = glm::vec2(data.x, data.y) - _pos0;
				_tempTrans = glm::vec3(trans0.x, 0.0, trans0.y);
			}
			else
			{
				_tempScale = glm::length((_scale1 - _scale0))/_startSize;
			}
		}
		else if (_touch1 && _touch0 && MinVR::startsWith(name, "Touch_Cursor_Move1"))
		{
			glm::dvec4 data = events[i]->get4DData();
			_scale1 = glm::vec2(data.x, data.y);
			_tempScale = glm::length((_scale1 - _scale0))/_startSize;
		}
		else if (MinVR::startsWith(name, "Touch_Cursor_Up0"))
		{
			_touch0 = false;
			_translation += _tempTrans;
			_tempTrans = glm::vec3(0.0f);
		}
		else if (MinVR::startsWith(name, "Touch_Cursor_Up1"))
		{
			_scale *= _tempScale;
			_touch1 = false;
			_scale1 = _scale0;
			_tempScale = 1.0f;
		}
	}

	_time = glfwGetTime();

	if (_startTime < 0)
	{
		_startTime = _time;
	}
	else
	{
		_numFrames++;
		float fps = _numFrames/(_time-_startTime);
		//std::cout << fps << std::endl;
		//std::cout << _startSize << std::endl;
	}

}

void SpatializeApp::initializeContextSpecificVars(int threadId,
		MinVR::WindowRef window) {
	initGL();
	initVBO(threadId);
	initLights();

	glClearColor(0.f, 0.f, 0.f, 0.f);

	GLenum err;
	if((err = glGetError()) != GL_NO_ERROR) {
		std::cout << "openGL ERROR in initializeContextSpecificVars: "<<err<<std::endl;
	}
}

void SpatializeApp::initVBO(int threadId)
{
    _mutex.lock();
	_scene[threadId] = SceneRef(new ExampleCube("model/nanosuit.obj"));
    _mutex.unlock();
}

void SpatializeApp::initGL()
{
	glShadeModel(GL_SMOOTH);                    // shading mathod: GL_SMOOTH or GL_FLAT
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);      // 4-byte pixel alignment

    // enable /disable features
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    //glEnable(GL_CULL_FACE);

     // track material ambient and diffuse from surface color, call it before glEnable(GL_COLOR_MATERIAL)
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glClearColor(0, 0, 0, 0);                   // background color
    glClearStencil(0);                          // clear stencil buffer
    glClearDepth(1.0f);                         // 0 is near, 1 is far
    glDepthFunc(GL_LEQUAL);

	GLenum err;
	if((err = glGetError()) != GL_NO_ERROR) {
		std::cout << "GLERROR initGL: "<<err<<std::endl;
	}
}

void SpatializeApp::initLights()
{
	// set up light colors (ambient, diffuse, specular)
    GLfloat lightKa[] = {.2f, .2f, .2f, 1.0f};  // ambient light
    GLfloat lightKd[] = {.7f, .7f, .7f, 1.0f};  // diffuse light
    GLfloat lightKs[] = {1, 1, 1, 1};           // specular light
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightKa);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightKd);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightKs);

    // position the light
    float lightPos[4] = {0.5, 0, 3, 1}; // positional light
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    glEnable(GL_LIGHT0);                        // MUST enable each light source after configuration

	GLenum err;
	if((err = glGetError()) != GL_NO_ERROR) {
		std::cout << "GLERROR initLights: "<<err<<std::endl;
	}
}

void SpatializeApp::postInitialization() {
}

void SpatializeApp::drawGraphics(int threadId, MinVR::AbstractCameraRef camera,
		MinVR::WindowRef window) {

	SceneRef scene = _scene[threadId];

	const Box& box = scene->getBoundingBox();
	float size = glm::length((box.getHigh()-box.getLow()));

	glm::dmat4 trans = glm::translate(glm::dmat4(1.0f), glm::dvec3(-box.center() + _translation + _tempTrans));
	glm::dmat4 scale = glm::scale(trans, glm::dvec3(1.0f*_scale*_tempScale/size));

	camera->setObjectToWorldMatrix(scale);

    Shader shader("shader.vs", "shader.frag");

	_scene[threadId]->draw(_time, camera, window, shader);
}

}
