#version 330 core

in vec2 tex_coords_o;

out vec4 color;

uniform mat3 mat_tex;
uniform sampler2D tex;

void main()
{
	vec3 tex_coords_final = mat_tex * vec3(tex_coords_o, 1.0);
	// NOTE: actually for textures, generally pqst instead of xyzw is used,
	// but since they represent the same values that's OK, ha-ha-ha
	tex_coords_final.x /= tex_coords_final.z;
	tex_coords_final.y /= tex_coords_final.z;
	color = texture(tex, tex_coords_final.xy);
}