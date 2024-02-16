#pragma once

#include "GL.h"


namespace Input {
	void Update();
	bool IsKeyPressed(int key);
	bool IsKeyReleased(int key);
	bool IsMousePressed(int code);
	bool IsMouseReleased(int code);

	Utils::MousePosition GetCursorPos();

}