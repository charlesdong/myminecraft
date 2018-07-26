#version 330 core

in vec2 tex_coords_o;

out vec4 color;

uniform sampler2D tex;

void main()
{
	color = texture(tex, tex_coords_o);
}