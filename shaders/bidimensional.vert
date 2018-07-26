#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 tex_coords;

out vec2 tex_coords_o;

uniform mat4 mat;

void main()
{
	gl_Position = mat * position;
	tex_coords_o = tex_coords;
}