#version 330

layout(location=0) in vec3 pos;
layout(location=1) in vec4 vertColour;
layout(location=2) in vec3 normal;
layout(location=3) in vec2 texVert;

out vec4 colour;
out vec3 fragVert;
out vec3 fragNormal;
out vec2 texCoord;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main(void) {
	gl_Position = projection * view * model * vec4(pos, 1.0);

	fragVert = pos;

	colour = vertColour;

	fragNormal = normal;

	texCoord = texVert;

}
