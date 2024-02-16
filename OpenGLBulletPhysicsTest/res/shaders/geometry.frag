#version 330 core

out vec4 FragColor;
in vec3 FragPos;
in vec3 Normal;
in vec2 TextCoords;

uniform vec3 color;

struct Material{
	sampler2D diffuse1;
	sampler2D specular1;
	float shininess;
};

struct Light{
	// vec3 position;
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	// vec3 lightColor;
};

uniform Light light;
uniform Material material;

uniform vec3 cameraPos;

void main(){
	
	// coseno dell'angolo tra la direzione della luce e la normale

	vec3 diffColor = texture(material.diffuse1, TextCoords).rgb;

	vec3 lightDir = normalize(-light.direction);
	vec3 norm = normalize(Normal);

	float angle = max(dot(norm, lightDir), 0.0);

	vec3 diffuse = light.diffuse * angle * diffColor;
	vec3 ambient = light.ambient * diffColor;

	vec3 eyeDirection = normalize(cameraPos - FragPos);
	vec3 ref = reflect(-lightDir, norm);
	float theta = pow(max(dot(eyeDirection, ref), 0.0), material.shininess);

	float specularStrength = 0.5;
	vec3 specular =  specularStrength * light.specular * theta * diffColor;

	FragColor = vec4((ambient + diffuse + specular), 1.0);
	// FragColor = texture(material.diffuse1, TextCoords);
}