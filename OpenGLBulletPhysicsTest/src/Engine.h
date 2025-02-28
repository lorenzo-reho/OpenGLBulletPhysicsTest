#pragma once

#include "Core/GL.h"
#include "Core/Renderer/Renderer.h"

#include "Core/Physics.h"
#include "Core/Input.h"
#include "Core/FileSystem.h"
#include "Core/EditingMenu.h"
#include "Core/Sky.h"
#include "Core/GameObject.h"
#include "Core/EditingMenu.h"
#include "Core/EditorCamera.h"
#include "Core/GBuffer.h"

#include "imgui.h"
#include "imgui_internal.h"

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace Engine {


	void SetEngineMode(MODE newMode);
	void Run();

}