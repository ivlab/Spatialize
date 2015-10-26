/*
 * Copyright Regents of the University of Minnesota, 2015.  This software is released under the following license: http://opensource.org/licenses/lgpl-3.0.html.
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#ifndef COMPOSITESCENE_H_
#define COMPOSITESCENE_H_

#include "Scene.h"
#include <vector>

namespace Spatialize {

class CompositeScene;
typedef std::shared_ptr<class CompositeScene> CompositeSceneRef;

class CompositeScene : public Scene {
public:
	CompositeScene();
	CompositeScene(const std::vector<SceneRef> &scenes);
	virtual ~CompositeScene();

	const Box& getBoundingBox();
	void draw(MinVR::RenderDevice& renderDevice);

	void addScene(SceneRef scene);
	void clear();

protected:
	void initContextItem();
	bool updateContextItem(bool changed);
	void cleanupContextItem();

private:
	void calculateBoundingBox();

	std::vector<SceneRef> _scenes;
	Box _boundingBox;
};

}

#endif /* COMPOSITESCENE_H_ */
