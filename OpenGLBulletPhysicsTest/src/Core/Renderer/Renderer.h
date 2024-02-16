#pragma once
#include "../Common.h"
#include "../Cube.h"

#include "../GL.h"
#include "../Camera.h"
#include "../Scene.h"
#include "Model.h"


#include "../ShaderManager.h"

namespace Renderer {
	void Init();
	void Render(Camera& camera);

	inline bool _isCollisionDebug = true;
}