#version 330 core

in vec2 TexCoords;

out vec4 FragColor;

// Gets the Texture Unit from the main function
uniform sampler2D image;
uniform vec3 spriteColor;


void main()
{
	// FragColor = texture(tex0, texCoord) * vec4(ourColor, 1.0);
	FragColor = vec4(spriteColor, 1.0) * texture(image, TexCoords);
	// FragColor = texture(image, TexCoords);
	// FragColor = vec4(1.0f, 0.4f, 1.0f, 1.0f);
}
