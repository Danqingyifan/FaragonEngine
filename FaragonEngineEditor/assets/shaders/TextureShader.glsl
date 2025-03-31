#type vertex
#version 330 core

layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec4 a_Color;
layout (location = 2) in vec2 a_TexCoord;
layout (location = 3) in float a_TexIndex;
layout (location = 4) in float a_TileFactor;


uniform mat4 u_ViewProjection;

out vec4 v_Color;
out vec2 v_TexCoord;
out float v_TexIndex;
out float v_TileFactor;

void main()
{
	gl_Position = u_ViewProjection * vec4(a_Pos, 1.0);

	//outs for fragment shader
	v_Color = a_Color;
	v_TexCoord = a_TexCoord;
	v_TexIndex = a_TexIndex;
	v_TileFactor = a_TileFactor;
}

#type fragment
#version 330 core

layout (location = 0) out vec4 o_Color;

in vec4 v_Color;
in vec2 v_TexCoord;
in float v_TexIndex;
in float v_TileFactor;

uniform sampler2D u_Textures[32];

void main()
{
	o_Color = texture(u_Textures[int(v_TexIndex)], v_TexCoord * v_TileFactor) * v_Color;
}