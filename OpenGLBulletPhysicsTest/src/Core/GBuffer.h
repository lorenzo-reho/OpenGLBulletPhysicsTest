#pragma once
#include "GL.h"

namespace GBuffer {

	void Init();
	void Configure();
	
	inline unsigned int _gBuffer;
	inline unsigned int _gPosition;
	inline unsigned int _gNormal;
	inline unsigned int _gAlbedoSpec;
	inline unsigned int _gDepth;

}