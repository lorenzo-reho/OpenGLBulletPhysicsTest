#pragma once

#include "GL.h"


namespace Input {
	void Update();
	bool IsKeyPressed(int key);
	bool IsKeyReleased(int key);
	bool IsMousePressed(int code);
	bool IsMouseReleased(int code);
	// int GetMouseWheelOffsetY();

	Utils::MousePosition GetCursorPos();
	void SetCursorPos(double x, double y);
	bool IsMouseWheelUp();
	bool IsMouseWheelDown();


}