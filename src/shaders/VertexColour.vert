#version 330

layout(location=0) in vec3 pos;
layout(location=1) in vec4 vertColour;

out vec4 colour;

void main(void) {
	gl_Position = vec4(pos,1.0);
	colour = vertColour;
}

