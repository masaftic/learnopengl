#pragma once
#include <shaderClass.h>
#include <texture.h>
#include <glm/glm.hpp>
#include "VAO.h"


// it's effectively not much more than a 2D image used together with some data to position it in a larger world
// (e.g. position, rotation, and size). 
// Basically, sprites are the render-able image/texture objects we use in a 2D game.

class SpriteRenderer
{
public:
	SpriteRenderer(Shader& shader);
	~SpriteRenderer();

	void DrawSprite(Texture& texture,
					glm::vec2 position,
					glm::vec2 size = glm::vec2(10.0f, 10.0f),
					float rotate = 0.0f,
					glm::vec3 color = glm::vec3(1.0f));

private:

	Shader shader;
	VAO quadVAO;

	void initRenderData();
};