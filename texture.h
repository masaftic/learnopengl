#pragma once

#include<glad/glad.h>
#include<stb/stb_image.h>

#include"shaderClass.h"

class Texture
{
public:
	GLuint ID;
	GLenum type;
	GLenum slot;
	Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

	void texUniform(Shader& shader, const char* uniform, GLuint unit);
	void Activate();
	void Bind();
	void Unbind();
	void Delete();
};
