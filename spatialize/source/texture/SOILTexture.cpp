/*
 * Copyright Regents of the University of Minnesota, 2015.  This software is released under the following license: http://opensource.org/licenses/GPL-2.0
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#include <texture/SOILTexture.h>
#include <SOIL.h>
#include <iostream>

namespace Spatialize {

SOILTexture::SOILTexture(const std::string& filepath) : Texture() {

	int width, height;
	unsigned char* image = SOIL_load_image(filepath.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	if (image != NULL)
	{
		create(width, height, 1);

		for (int f = 0; f < width*height*4; f++)
		{
			get(f) = image[f];
		}

		delete[] image;
	}
}

SOILTexture::~SOILTexture() {
}

} /* namespace vrbase */
