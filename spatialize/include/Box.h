/*
 * Copyright Regents of the University of Minnesota, 2015.  This software is released under the following license: http://opensource.org/licenses/lgpl-3.0.html.
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#ifndef BOX_H_
#define BOX_H_

#include <glm/glm.hpp>

namespace Spatialize {

class Box {
public:
	Box();
	Box(const glm::vec3& low, const glm::vec3& high);
	virtual ~Box();

	const glm::vec3& getHigh() const {
		return _high;
	}

	void setHigh(const glm::vec3& high) {
		_high = high;
	}

	const glm::vec3& getLow() const {
		return _low;
	}

	void setLow(const glm::vec3& low) {
		_low = low;
	}

	Box merge(const Box& box) const;
	glm::vec3 center() const;

private:
	glm::vec3 _low;
	glm::vec3 _high;
};

} /* namespace Spatialize */

#endif /* BOX_H_ */
