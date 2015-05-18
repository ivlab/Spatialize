/*
 * Copyright Regents of the University of Minnesota, 2015.  This software is released under the following license: http://opensource.org/licenses/lgpl-3.0.html.
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#include <Box.h>

namespace Spatialize {

Box::Box() : _low(0.0f), _high(0.0f) {

}

Box::Box(const glm::vec3& low, const glm::vec3& high) : _low(low), _high(high) {
}

Box::~Box() {
}

Box Box::merge(const Box& box) const {
	return Box(glm::vec3(
				glm::min(_low.x, box.getLow().x),
				glm::min(_low.y, box.getLow().y),
				glm::min(_low.z, box.getLow().z)),
			glm::vec3(
				glm::max(_high.x, box.getHigh().x),
				glm::max(_high.y, box.getHigh().y),
				glm::max(_high.z, box.getHigh().z)));
}

glm::vec3 Box::center() const {
	glm::vec3 center = _low + _high;
	center /= 2.0f;
	return center;
}

} /* namespace Spatialize */
