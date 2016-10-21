#version 410 core

layout (location = 0) in vec4 position;

uniform mat4 toClipMatrix;
uniform float pointSize;

void main()
{
    gl_PointSize = pointSize;
	gl_Position = toClipMatrix * position;
}
