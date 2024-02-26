#ifndef RENDERER_H
#define RENDERER_H
#include "../Common.h"
#include "../GL.h"
#include "../Scene.h"
#include "../ShaderManager.h"
#include "../Camera.h"
#include "../EditorCamera.h"

namespace Renderer {
	void Init();
	void Render(Camera& camera, EditorCamera& editorCamera, MODE currentMode);
}
#endif