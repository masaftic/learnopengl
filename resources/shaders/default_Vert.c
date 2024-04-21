#version 330 core

layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoord>


// Outputs the texture coordinates to the fragment shader
out vec2 texCoord;


uniform mat4 projection;
uniform mat4 model;


void main()
{
    gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);
    // gl_Position = vec4(vertex.xy, 0.0, 1.0);
    texCoord = vertex.zw;
}
