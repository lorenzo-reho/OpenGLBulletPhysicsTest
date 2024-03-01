#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTextCoord;
layout (location = 3) in vec3 aTangent;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 FragPos;
//out vec3 Normal;
out vec2 TextCoord;
out mat3 TBN;

void main(){
	
	gl_Position = projection*view*model*vec4(aPos, 1.0);
	FragPos = vec3(model * vec4(aPos, 1.0));
	TextCoord = aTextCoord;
	// Normal = mat3(transpose(inverse(model))) * aNormal;  
	
	vec3 tangent =normalize(vec3(model*vec4(aTangent, 0.0)));
	vec3 normal = normalize(vec3(model*vec4(aNormal, 0.0)));
	tangent = normalize(tangent - dot(tangent, normal) * normal);
	vec3 bitangent = cross(normal, tangent);

	TBN = mat3(tangent, bitangent, normal);

}
