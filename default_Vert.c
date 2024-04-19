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

void main()
{
    gl_Position = vec4(aPos.x * (1 + scale), (aPos.y * (1 + scale)), aPos.z * (1 + scale), 1.0);
    ourColor = aColor;
    // Assigns the texture coordinates from the Vertex Data to "texCoord"
    texCoord = aTexCoord;
}
