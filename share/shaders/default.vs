#version 300 es
precision mediump float;
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec2 texCoord;
out vec3 pos;
out vec3 norm;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	pos = (model * vec4(position, 1.0f)).xyz;
    gl_Position = projection * view * model * vec4(position, 1.0f);
    texCoord = texCoords;
    norm = normalize((model * vec4(normal, 0.0)).xyz);
}
