#version 410 core

layout (location = 0) in vec4 position;

uniform mat4 toClipMatrix;

void main()
{
	gl_Position = toClipMatrix * position;
}
