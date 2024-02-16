#ifndef RENDERER_H
#define RENDERER_H
#include "../Common.h"
#include "../GL.h"

#include "../Camera.h"
#include "../Scene.h"
#include "Model.h"

#include "../ShaderManager.h"
class Cube;

namespace Renderer {
	void Init();
	void Render(Camera& camera);

}
#endif