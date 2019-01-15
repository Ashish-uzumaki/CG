#version 330

in vec4 vCol;

uniform mat4 model;

out vec4 color;

void main()
{
	//color = vec4(1.0f, 1.0f, 0.0f, 1.0f);
	color = vec4(vCol.x, vCol.y, 0.5, 1.0);
}