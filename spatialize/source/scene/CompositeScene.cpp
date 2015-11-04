/*
 * Copyright Regents of the University of Minnesota, 2015.  This software is released under the following license: http://opensource.org/licenses/lgpl-3.0.html.
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#include "scene/CompositeScene.h"

namespace Spatialize {

CompositeScene::CompositeScene(const std::vector<SceneRef> &scenes) : _scenes(scenes) {
	calculateBoundingBox();
}

CompositeScene::~CompositeScene() {
}

CompositeScene::CompositeScene() : _scenes() {
}

void CompositeScene::addScene(SceneRef scene) {
	_scenes.push_back(scene);
	calculateBoundingBox();
	incrementVersion();
}

const Box& CompositeScene::getBoundingBox() {
	calculateBoundingBox();
	return _boundingBox;
}

void CompositeScene::draw(MinVR::RenderDevice& renderDevice) {
	for (int f = 0; f < _scenes.size(); f++)
	{
		_scenes[f]->draw(renderDevice);
	}
}

void CompositeScene::initContextItem() {
	for (int f = 0; f < _scenes.size(); f++)
	{
		_scenes[f]->initContext();
	}
}

bool CompositeScene::updateContextItem(bool changed) {
	for (int f = 0; f < _scenes.size(); f++)
	{
		_scenes[f]->updateContext();
	}
	return true;
}

void CompositeScene::cleanupContextItem() {
}

void CompositeScene::clear() {
	_scenes.clear();
	incrementVersion();
}

void CompositeScene::calculateBoundingBox() {
	Box box;

	for (int f = 0; f < _scenes.size(); f++)
	{
		if (f == 0)
		{
			box = _scenes[f]->getBoundingBox();
		}
		else
		{
			box = box.merge(_scenes[f]->getBoundingBox());
		}
	}

	_boundingBox = box;
}

}



