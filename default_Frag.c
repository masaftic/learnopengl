#version 330 core

out vec4 FragColor;

// inputs the color from the vertex shader
in vec3 ourColor;
// Inputs the texture coordinates from the Vertex Shader
in vec2 texCoord;

// Gets the Texture Unit from the main function
uniform sampler2D tex0;
uniform sampler2D tex1;


void main()
{
	// FragColor = texture(tex0, texCoord) * vec4(ourColor, 1.0);
	FragColor = mix(texture(tex0, texCoord), texture(tex1, texCoord), 0.55);
}
