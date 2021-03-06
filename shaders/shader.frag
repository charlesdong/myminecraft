#version 330 core

in vec2 tex_coords_o;

out vec4 color;

uniform sampler2D tex;
uniform vec3 color_aux;

void main()
{
	color = texture(tex, tex_coords_o) * vec4(color_aux, 1.0);
}