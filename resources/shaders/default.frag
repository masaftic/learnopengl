#version 330 core

out vec4 FragColor;

// inputs the color from the vertex shader
in vec3 color;
// Inputs the texture coordinates from the Vertex Shader
in vec2 texCoord;

// Gets the Texture Unit from the main function
uniform sampler2D tex0;
uniform float ourColor;


void main()
{
		FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);

}
