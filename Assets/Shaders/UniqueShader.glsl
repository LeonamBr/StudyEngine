#type vertex
#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_Texture;
layout(location = 3) in float a_TexIndex;
layout(location = 4) in float a_Scale;

uniform mat4 u_ViewProjection;

out vec4 v_Color;
out vec2 v_Texture;
out float v_TexIndex;
out float v_Scale;

void main(){
                
    v_Color = a_Color;
    v_Texture = a_Texture;
    v_TexIndex = a_TexIndex;
    v_Scale = a_Scale;

    gl_Position = u_ViewProjection * vec4(a_Position, 1.0);

}

#type fragment
#version 450 core

layout(location = 0) out vec4 color;
layout(location = 1) out int color2;

in vec4 v_Color;
in vec2 v_Texture;
in float v_TexIndex;
in float v_Scale;

uniform sampler2D u_Textures[32];

void main(){
    
    color = texture(u_Textures[int(v_TexIndex)], v_Texture * v_Scale) * v_Color;

    color2 = 10;
    
}