#version 330

out vec4 fragColour;

in vec4 colour;
in float intensity;
in vec3 fragNormal;
in vec3 fragVert;

uniform vec3 mAmbient;
uniform vec3 sAmbient;

uniform vec3 lightPos;
uniform mat4 model;

void main() {

	vec3 lightDir =  lightPos - vec3(model * vec4(fragVert, 1.0));
	vec3 unitDir = normalize(lightDir);

	float intensity = dot(unitDir, fragNormal);

	// ambient
	vec3 components = mAmbient * sAmbient;

	vec4 multiplier;

	if (intensity > 0.95)
		multiplier = vec4(1.0,1.0,1.0,1.0);
	else if (intensity > 0.75)
		multiplier = vec4(0.8,0.8,0.8,1.0);
	else if (intensity > 0.5)
		multiplier = vec4(0.6,0.6,0.6,1.0);
	else if (intensity > 0.25)
		multiplier = vec4(0.4,0.4,0.4,1.0);
	else
		multiplier = vec4(0.2,0.2,0.2,1.0);


	fragColour = colour  * multiplier + vec4(components, 1);// * vec4(components, 0.0); //vec4(max(vec3(0.0, 0.0, 0.0), (lightColour * dot(normal, (surfaceToLight))) * attenuation), 1.0);
}
