#include "game.h"
#include <camera.h>
#include <texture.h>
#include <VAO.h>
#include <spriteRenderer.h>
#include <resourceManager.h>

SpriteRenderer* Renderer;

Game::Game(unsigned int width, unsigned int height) : Height(height), Width(width), State(GAME_ACTIVE), Keys()
{
	
}

Game::~Game()
{
	delete Renderer;
}

void Game::Init()
{
	// load shaders
	ResourceManager::LoadShader("resources/shaders/default_Vert.c", "resources/shaders/default_Frag.c", "sprite");
	// config shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width), static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
	// load texture in slot 0

	Shader shader_sprite = ResourceManager::GetShader("sprite");
	shader_sprite.Use();
	shader_sprite.setInt("image", 0);
	shader_sprite.setMat4("projection", projection);

	// set renderer controls
	Renderer = new SpriteRenderer(shader_sprite);

	// load textures
	ResourceManager::LoadTexture("resources/textures/minato.png", true, "minato");

}

void Game::ProcessInput(float dt)
{
}

void Game::Update(float dt)
{
}

void Game::Render()
{
	Texture texture = ResourceManager::GetTexture("minato");
	Renderer->DrawSprite(texture, glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));

}
