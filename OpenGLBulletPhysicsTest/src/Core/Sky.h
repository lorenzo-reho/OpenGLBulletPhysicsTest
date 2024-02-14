#ifndef SKY_H
#define SKY_H

#include <iostream>
#include <vector>
#include <stb_image.h>
#include "Common.h"

using namespace std;

class Sky {
	
public:
	Sky(vector<string> faces);

	void CreateSky();
	void LoadCubemap(vector<string> faces);
	unsigned int GetVAO();
	unsigned int GetTextureID();

private:
	unsigned int _VAO, _VBO, _textureID;
};

#endif
