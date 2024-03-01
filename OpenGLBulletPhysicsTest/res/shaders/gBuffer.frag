#version 330 core
layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedoSpec;

in vec3 FragPos;
// in vec3 Normal;
in vec2 TextCoord;
in mat3 TBN;


uniform sampler2D diffuse1;
uniform sampler2D specular1;
uniform sampler2D normal1;

void main(){
	
	vec3 normal = texture(normal1, TextCoord).rgb;
	normal = normalize(normal * 2.0 - 1.0);
	normal = normalize(TBN * normal);

	gNormal = normal;
	
	// gNormal = Normal;
	gPosition = FragPos;

	gAlbedoSpec.rgb = texture(diffuse1, TextCoord).rgb;
	gAlbedoSpec.a = texture(specular1, TextCoord).r;


}