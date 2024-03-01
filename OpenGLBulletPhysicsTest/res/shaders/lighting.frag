#version 330 core

in vec2 TextCoord;

out vec4 FragColor;


struct Light{
	vec3 position;
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float radius;
	float intensity;
	vec3 lightColor;
};

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;

uniform vec3 cameraPos;


uniform Light light;


void main(){


	// coseno dell'angolo tra la direzione della luce e la normale


	vec3 FragPos = texture(gPosition, TextCoord).rgb;
	vec3 Normal = texture(gNormal, TextCoord).rgb;
	vec3 Diffuse = texture(gAlbedoSpec, TextCoord).rgb;
	// vec3 diffColor = vec3(1, 1, 1);

	vec3 lightDir = normalize(light.position - FragPos);

	vec3 norm = normalize(Normal);

	float angle = max(dot(norm, lightDir), 0.0);

	vec3 diffuse = light.diffuse * angle * Diffuse * light.lightColor;
	vec3 ambient = light.ambient * Diffuse  * light.lightColor;

	vec3 eyeDirection = normalize(cameraPos - FragPos);
	vec3 ref = reflect(-lightDir, norm);
	float theta = pow(max(dot(eyeDirection, ref), 0.0), 256.0f);

	float specularStrength = 1.0;
	vec3 specular =  specularStrength * light.specular * theta * vec3(1, 1, 1);

	float dist    = length(light.position - FragPos);
	float attenuation = smoothstep(light.radius, 0, dist);
	// attenuation = clamp(attenuation, 0.0, 0.9);

	// ambient  *= attenuation*light.intensity; 
	diffuse  *= attenuation*light.intensity;
	specular  *= light.intensity*attenuation;

	FragColor = vec4((ambient+diffuse), 1.0);
	// FragColor = texture(material.diffuse1, TextCoords);


	
}