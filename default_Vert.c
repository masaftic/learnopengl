#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

// Texture Coordinates
layout (location = 2) in vec2 aTexCoord;

// Outputs the color for the Fragment Shader
out vec3 ourColor;

// Outputs the texture coordinates to the fragment shader
out vec2 texCoord;

uniform float scale;
uniform float xOffset;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
    gl_Position = proj * view * model * vec4(aPos, 1.0);
    ourColor = aColor;
    // Assigns the texture coordinates from the Vertex Data to "texCoord"
    texCoord = aTexCoord;
}
