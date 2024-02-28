#version 330 core
layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedoSpec;

in vec3 FragPos;
in vec3 Normal;
in vec2 TextCoord;

uniform sampler2D diffuse1;
uniform sampler2D specular1;

void main(){
	
	gNormal = Normal;
	gPosition = FragPos;

	gAlbedoSpec.rgb = texture(diffuse1, TextCoord).rgb;
	gAlbedoSpec.a = texture(specular1, TextCoord).r;


}