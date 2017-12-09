#version 120

attribute vec3 position;
attribute vec2 texCoord;
attribute vec3 normal;
attribute vec3 instPos;

varying vec2 texCoord0;

uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(position + instPos, 1.0);
	texCoord0 = texCoord;
	normal;
}