#pragma once
#include "../Common.h"
#include "../Cube.h"
#include "../GL.h"
#include "Camera.h"
#include "Shader.h"

namespace Renderer {
	void Init();
	void Render(Camera &camera, Shader& shader);
}