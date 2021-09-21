#version 330

out vec4 fragColour;

in vec3 fragNormal;

in vec4 colour;
in vec3 fragVert;

uniform mat4 model;
uniform mat4 view;

uniform vec3 mAmbient;
uniform vec3 sAmbient;
uniform vec3 lightPos;
uniform vec3 lightColour;
uniform float constantAttenuation;
uniform float linearAttenuation;
uniform float quadraticAttenuation;

void main() {

	vec3 fragPosition = vec3(view * model * vec4(fragVert, 1.0));

	// Light calculations
	vec3 surfaceToLight = lightPos - fragPosition;

	float d = length(surfaceToLight);
	float attenuation = 1.0 / (constantAttenuation + d*linearAttenuation + d*d*quadraticAttenuation);

	// ambient
	vec3 components = mAmbient * sAmbient;

	fragColour = colour * vec4(max(vec3(0.0, 0.0, 0.0), (lightColour * dot(fragNormal, surfaceToLight)) * attenuation), 1.0) + vec4(components, 0);
}
