/*
 * Copyright Regents of the University of Minnesota, 2015.  This software is released under the following license: http://opensource.org/licenses/GPL-2.0
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#ifndef SOILTEXTURE_H_
#define SOILTEXTURE_H_

#include "Texture.h"
#include <string>

namespace Spatialize {

class SOILTexture : public Texture {
public:
	SOILTexture(const std::string& filepath);
	virtual ~SOILTexture();
};

} /* namespace vrbase */

#endif /* SOILTEXTURE_H_ */
