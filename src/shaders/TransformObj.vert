#version 330

layout(location=0) in vec3 pos;
layout(location=1) in vec4 mDiffuse;
layout(location=2) in vec3 normal;
layout(location=3) in vec2 texVert;


out vec4 colour;
out vec3 fragVert;
out vec2 texCoord;
out vec3 fragNormal;
out float intensity;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform vec3 lightPos;

void main(void) {
	gl_Position = projection * view * model * vec4(pos, 1.0);

	fragVert = pos;
	colour = vec4(mDiffuse, 1);

	vec3 lightDir =  lightPos - vec3(vec4(pos, 1.0));
	vec3 unitDir = normalize(lightDir);

	fragNormal = normal;
	texCoord = texVert;

	intensity = dot(unitDir, normal);

}
