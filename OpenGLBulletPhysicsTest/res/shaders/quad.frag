#version 330 core

in vec3 Pos;
in vec2 TextCoord;

out vec4 FragColor;

uniform sampler2D text;

void main(){

	FragColor = texture(text, TextCoord);

}