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
#include "VRModel.h"
#include <unistd.h>

using namespace MinVR;

namespace Spatialize {

SpatializeApp::SpatializeApp(GLchar *path = NULL) : MinVR::AbstractMVRApp() {
	_startTime = -1;
	_numFrames = 0;
	_touch0 = false;
	_touch1 = false;
	_tempTrans = glm::vec3(0.0f);
	_translation = glm::vec3(0.0f);
	_startSize = 1.0f;
	_tempScale = 1.0f;
	_scale = 1.0f;
    _path = path;
    this->loadModel(_path);
}

SpatializeApp::~SpatializeApp() {
}

void SpatializeApp::loadModel(std::string path) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
        return;
    }
    this->directory = path.substr(0, path.find_last_of('/'));

    this->processNode(scene->mRootNode, scene);
}

void SpatializeApp::processNode(aiNode *node, const aiScene *scene) {
    for (GLuint i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        this->_meshes.push_back(this->processMesh(mesh, scene));
    }

    for (GLuint i = 0; i < node->mNumChildren; i++) {
        this->processNode(node->mChildren[i], scene);
    }
}

Mesh SpatializeApp::processMesh(aiMesh *mesh, const aiScene *scene) {
    vector<Vertex> vertices;
    vector<GLuint> indices;
    vector<Texture> textures;

    for (GLuint i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;

        glm::vec3 vect;
        vect.x = mesh->mVertices[i].x;
        vect.y = mesh->mVertices[i].y;
        vect.z = mesh->mVertices[i].z;
        vertex.Position = vect;

        if (!min.x && !min.y && !min.z && !max.x && !max.y && !max.z)
        {
            min = vect;
            max = vect;
        }
        else
        {
            if (vect.x < min.x) { min.x = vect.x; }
            if (vect.y < min.y) { min.y = vect.y; }
            if (vect.z < min.z) { min.z = vect.z; }
            if (vect.x > max.x) { max.x = vect.x; }
            if (vect.y > max.y) { max.y = vect.y; }
            if (vect.z > max.z) { max.z = vect.z; }
        }

        vect.x = mesh->mNormals[i].x;
        vect.y = mesh->mNormals[i].y;
        vect.z = mesh->mNormals[i].z;

        vertex.Normal = vect;

        if(mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x; 
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);  

        vertices.push_back(vertex);
    }

    for(GLuint i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // Retrieve all indices of the face and store them in the indices vector
        for(GLuint j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    if (mesh->mMaterialIndex >= 0) {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

        vector<Texture> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        vector<Texture> specularMaps = this->loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    return Mesh(vertices, indices, textures);
}

vector<Texture> SpatializeApp::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
    vector<Texture> textures;
    for(GLuint i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        // Check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
        GLboolean skip = false;
        for(GLuint j = 0; j < _textures_loaded.size(); j++)
        {
            if(_textures_loaded[j].path == str)
            {
                textures.push_back(_textures_loaded[j]);
                skip = true; // A texture with the same filepath has already been loaded, continue to next one. (optimization)
                break;
            }
        }
        if(!skip)
        {   // If texture hasn't been loaded already, load it
            Texture texture;
            texture.type = typeName;
            texture.path = str;
            textures.push_back(texture);
            this->_textures_loaded.push_back(texture);  // Store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
        }
    }
    return textures;
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
    if (!_path)
	    _scene[threadId] = SceneRef(new ExampleCube());
    else {
        _scene[threadId] = SceneRef(new VRModel(_meshes, min, max, directory));
        //_textures_loaded.clear();
    }
    _mutex.unlock();
}

void SpatializeApp::initGL()
{
	glShadeModel(GL_SMOOTH);                    // shading mathod: GL_SMOOTH or GL_FLAT
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);      // 4-byte pixel alignment

    // enable /disable feature
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
    /*float size = glm::length((box.getHigh()-box.getLow()));

    glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(-box.center() + _translation + _tempTrans));
    glm::mat4 scale = glm::scale(modelView, glm::vec3(1.0f*_scale*_tempScale/size));*/

    float cameraDistance;

    if ((box.getHigh().x - box.getLow().x) > (box.getHigh().y - box.getLow().y)) 
        cameraDistance = box.getHigh().x - box.getLow().x;
    else 
        cameraDistance = box.getHigh().y - box.getLow().y;

    glm::mat4 modelView = glm::translate(glm::mat4(1.0f), glm::vec3(-box.center().x, -box.center().y, -cameraDistance + -box.center().z));

    glm::mat4 objectToWorld = modelView;
 
    _scene[threadId]->draw(_time, camera, window, objectToWorld);
}

}
