/*
 * Copyright Regents of the University of Minnesota, 2014.  This software is released under the following license: http://opensource.org/licenses/lgpl-3.0.html.
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#define GLM_FORCE_RADIANS

#include <SpatializeApp.h>
#include "example/ExampleCube.h"
#include "MVRCore/StringUtils.H"
#include "VRModel.h"
#include <unistd.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace MinVR;
using namespace std;

namespace Spatialize {

SpatializeApp::SpatializeApp(GLchar *path = NULL) : MinVR::AbstractMVRApp() {
	_startTime = -1;
	_numFrames = 0;
	_touch0 = false;
	_touch1 = false;
	_touch2 = false;
	_tempTrans = glm::vec3(0.0f);
	_translation = glm::vec3(0.0f);
	_startSize = 1.0f;
	_tempScale = 1.0f;
	_scale = 1.0f;
	_path = path;
	_rotationAngle = 0.0f;
	//_scale = 1.0f;
	/*_path = path;
    if (_path)
        this->loadModel(_path);*/

	_shader = ShaderRef(new Shader("share/shaders/default.vs", "share/shaders/default.fs"));

	if (_path)
	{
		std::cout << "Not cube" << std::endl;
		std::vector<glm::vec3> vertices;
		vertices.push_back(glm::vec3(-1.0f, -1.0, 0.0));
		vertices.push_back(glm::vec3(-1.0f, 1.0, 0.0));
		vertices.push_back(glm::vec3(1.0f, 1.0, 0.0));

		/*vertices.push_back(glm::vec3(1.0f, 1.0, 0.0));
		vertices.push_back(glm::vec3(1.0f, -1.0, 0.0));
		vertices.push_back(glm::vec3(-1.0f, -1.0, 0.0));*/

		std::vector<unsigned int> indices;
		for (int f = 0; f < vertices.size(); f++)
		{
			indices.push_back(f);
		}

		//_scene = SceneRef(new Mesh(vertices, indices));
		_scene = SceneRef(loadModel(_path));
	}
	else
	{
		std::cout << "Example cube" << std::endl;
	    _scene = SceneRef(new ExampleCube());
	}
}

SpatializeApp::~SpatializeApp() {
}

MeshRef SpatializeApp::loadModel(std::string path)
{
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
		return NULL;
	}

	cout << scene->mNumMeshes << endl;

    aiMesh *mesh = scene->mMeshes[0];

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texCoords;

    bool hasTexCoords = mesh->mTextureCoords[0];

    for (int i = 0; i < mesh->mNumVertices; i++) {
    	glm::vec3 vert;
    	vert.x = mesh->mVertices[i].x;
    	vert.y = mesh->mVertices[i].y;
    	vert.z = mesh->mVertices[i].z;
    	vertices.push_back(vert);

        if (mesh->HasNormals())
        {
        	glm::vec3 norm;
        	norm.x = mesh->mNormals[i].x;
        	norm.y = mesh->mNormals[i].y;
        	norm.z = mesh->mNormals[i].z;
        	normals.push_back(norm);
        }

        if (hasTexCoords)
        {
        	texCoords.push_back(glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y));
        }
    }

    std::vector<unsigned int> indices;
    for(int i = 0; i < mesh->mNumFaces; i++)
    {
    	aiFace face = mesh->mFaces[i];
    	// Retrieve all indices of the face and store them in the indices vector
    	for(int j = 0; j < face.mNumIndices; j++)
    		indices.push_back(face.mIndices[j]);
    }

    MeshRef finalMesh;

    if (mesh->HasNormals())
    {
        finalMesh = MeshRef(new Mesh(vertices, normals, indices));
    }
    else
    {
        finalMesh = MeshRef(new Mesh(vertices, indices));
    }

    if (hasTexCoords)
    {
    	finalMesh->setTexCoords(texCoords);
    }

    return finalMesh;
}

/*
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
}*/

void SpatializeApp::doUserInputAndPreDrawComputation(
		const std::vector<MinVR::EventRef>& events, double synchronizedTime) {
	_syncTime = synchronizedTime;

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
		else if (MinVR::startsWith(name, "Touch_Cursor_Down2"))
		{
			_touch2 = true;
			_vertPos = events[i]->get2DData();
		}
		else if (_touch0 && MinVR::startsWith(name, "Touch_Cursor_Move0"))
		{
			glm::dvec4 data = events[i]->get4DData();
			glm::vec2 oldScale0 = _scale0;
			_scale0 = glm::vec2(data.x, data.y);
			if (!_touch1)
			{
				glm::vec2 trans0 = glm::vec2(data.x, data.y) - _pos0;
				_tempTrans = glm::vec3(trans0.x, 0.0, trans0.y);
			}
			else
			{
				_tempScale = glm::length((_scale1 - _scale0))/_startSize;
				glm::vec2 oldVal = glm::normalize(_scale1-oldScale0);
				glm::vec2 newVal = glm::normalize(_scale1-_scale0);
				double diffAngle = acos(glm::min(1.0f, glm::dot(oldVal, newVal)));
				float cVal = glm::cross(glm::vec3(oldVal,0.0), glm::vec3(newVal,0.0)).z;
				_rotationAngle += cVal > 0 ? -diffAngle : diffAngle;
			}
		}
		else if (_touch1 && _touch0 && MinVR::startsWith(name, "Touch_Cursor_Move1"))
		{
			glm::dvec4 data = events[i]->get4DData();
			glm::vec2 oldScale1 = _scale1;
			_scale1 = glm::vec2(data.x, data.y);
			_tempScale = glm::length((_scale1 - _scale0))/_startSize;
			//_rotationAngle += 0.1;
			glm::vec2 oldVal = glm::normalize(oldScale1-_scale0);
			glm::vec2 newVal = glm::normalize(_scale1-_scale0);
			double diffAngle = acos(glm::min(1.0f, glm::dot(oldVal, newVal)));
			float cVal = glm::cross(glm::vec3(oldVal,0.0), glm::vec3(newVal,0.0)).z;
			_rotationAngle += cVal > 0 ? -diffAngle : diffAngle;
		}
		else if (_touch2 && _touch1  && _touch0 && MinVR::startsWith(name, "Touch_Cursor_Move2"))
		{
			glm::dvec4 data = events[i]->get4DData();
			glm::vec2 newVertPos = glm::vec2(data.x, data.y);
			float diff = glm::length(newVertPos-_pos0) - glm::length(_vertPos-_pos0);
			_translation += glm::vec3(0.0f, diff, 0.0f);
			_vertPos = newVertPos;
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
		else if (MinVR::startsWith(name, "Touch_Cursor_Up2"))
		{
			_touch2 = false;
		}
		else if (name == "kbd_C_CTRL_down") {
			terminate();
		}
	}

	_time = synchronizedTime;//glfwGetTime();

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

	glClearColor(0.f, 0.f, 0.f, 0.f);

	GLenum err;
	if((err = glGetError()) != GL_NO_ERROR) {
		std::cout << "openGL ERROR in initializeContextSpecificVars: "<<err<<std::endl;
	}
}

void SpatializeApp::initVBO(int threadId)
{
    _mutex.lock();
    _shader->initContext();
	_scene->initContext();
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

void SpatializeApp::postInitialization() {
}

void SpatializeApp::drawGraphics(MinVR::RenderDevice& renderDevice) {
	SceneRef scene = _scene;

	const Box& box = scene->getBoundingBox();
	float size = glm::length((box.getHigh()-box.getLow()));

	/*cout << box.center().x << " ";
	cout << box.center().y <<  " ";
	cout << box.center().z << endl;*/

	//0.776126 -0.438658 0
	//-4.44584 -3.63704 -1.70141 / 5.99809 2.75972 1.70141


	glm::dmat4 trans = glm::translate(glm::dmat4(1.0f), glm::dvec3(_translation + _tempTrans));
	//glm::dmat4 trans = glm::translate(glm::dmat4(1.0f), glm::dvec3(_translation + _tempTrans));
	glm::dmat4 scale = glm::scale(trans, glm::dvec3(1.0f*_scale*_tempScale/size));
	glm::dmat4 rot = glm::rotate(scale, _rotationAngle, glm::dvec3(0.0, 1.0, 0.0));
	trans = glm::translate(rot, glm::dvec3(-(box.center())));

	renderDevice.getWindowInfo().getCamera()->setObjectToWorldMatrix(trans);

	glm::vec4 lightPositions[1];
	lightPositions[0] = glm::vec4(0.5, 0, 3, 1);

	glm::vec4 lightK[1];
	lightK[0] = glm::vec4(0.2, 0.7, 0.5, 50);

//    GLfloat lightKa[] = {.2f, .2f, .2f, 1.0f};  // ambient light
//    GLfloat lightKd[] = {.7f, .7f, .7f, 1.0f};  // diffuse light
//    GLfloat lightKs[] = {1, 1, 1, 1};           // specular light

	_shader->useProgram();
	_shader->setParameter("model", glm::mat4(trans));//glm::mat4(renderDevice.getWindowInfo().getOffAxisCamera()->getObjectToWorldMatrix()));
	_shader->setParameter("view", glm::mat4(renderDevice.getWindowInfo().getOffAxisCamera()->getLastAppliedViewMatrix()));
	_shader->setParameter("projection", glm::mat4(renderDevice.getWindowInfo().getOffAxisCamera()->getLastAppliedProjectionMatrix()));
	_shader->setParameter("viewdir", glm::vec3(renderDevice.getWindowInfo().getOffAxisCamera()->getLookVector()));
	_shader->setParameter("lightPositions", lightPositions, 1);
	_shader->setParameter("lightK", lightK, 1);
	_shader->setParameter("lightCount", (GLuint)1);
	_shader->setParameter("hasTexCoords", (GLuint)0);

	scene->draw(renderDevice);

	_shader->releaseProgram();

}


}
