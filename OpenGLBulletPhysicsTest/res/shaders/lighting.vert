#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTextCoord;

out vec2 TextCoord;

void main(){
	TextCoord = aTextCoord;
	gl_Position = vec4(aPos, 1.0f);
}