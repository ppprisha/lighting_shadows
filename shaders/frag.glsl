#version 410 core
in vec3 FragPos;
in vec3 Normal;
out vec4 FragColor;

// struct for PointLight
struct PointLight {
	bool enabled;	
	vec3 position;
	vec3 color;
	float intensity;
};

// struct for DirectionalLight
struct DirectionalLight {
	bool enabled;	
	vec3 direction;
	vec3 color;
};

// struct for SpotLight
struct SpotLight {
	bool enabled;	
	vec3 position;
	vec3 direction;
	vec3 color;
	float cutoff;
	float outerCutoff;
};

uniform PointLight pointLight;
uniform DirectionalLight directionalLight;
uniform SpotLight spotLight;
uniform vec3 viewPosition;

void main() {
	vec3 result = vec3(0.1);
	vec3 viewDirection = normalize(viewPosition - FragPos);
	vec3 norm = normalize(Normal);

	if (pointLight.enabled) {
		vec3 lightDirection = normalize(pointLight.position - FragPos);
		float diff = max(dot(norm, lightDirection), 0.0);
		vec3 diffuse = diff * pointLight.color * pointLight.intensity;

		float distance = length(pointLight.position - FragPos);
		float attenuation = 1.0 / (1.0 + 0.09*distance + 0.032*(distance*distance));

		result += diffuse * attenuation;
	}

	if (directionalLight.enabled) {
		vec3 lightDirection = normalize(-directionalLight.direction);
		float diff = max(dot(norm, lightDirection), 0.0);
		result += diff * directionalLight.color;
	}

	if (spotLight.enabled) {
		vec3 lightDirection = normalize(spotLight.position - FragPos);
		float theta = dot(lightDirection, normalize(-spotLight.direction));
		float epsilon = spotLight.cutoff - spotLight.outerCutoff;
		float intensity = clamp((theta - spotLight.outerCutoff) / epsilon, 0.0, 1.0);
		float diff = max(dot(norm, lightDirection), 0.0);
		result += diff * spotLight.color * intensity;
	}
	
	FragColor = vec4(result, 1.0);
}



