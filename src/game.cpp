#include "game.h"
#include <camera.h>
#include <texture.h>
#include <VAO.h>
#include <spriteRenderer.h>
#include <resourceManager.h>
#include <gameLevel.h>

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
	ResourceManager::LoadShader("resources/shaders/default.vert", "resources/shaders/default.frag", "sprite");
	// config shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width), static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);

	Shader shader_sprite = ResourceManager::GetShader("sprite");
	shader_sprite.Use();
	shader_sprite.setInt("image", 0);
	shader_sprite.setMat4("projection", projection);

	// set renderer controls
	Renderer = new SpriteRenderer(shader_sprite);

	// load textures
	ResourceManager::LoadTexture("resources/textures/minato.png", true, "minato");
	ResourceManager::LoadTexture("resources/textures/background.jpg", false, "background");
	ResourceManager::LoadTexture("resources/textures/block.png", false, "block");
	ResourceManager::LoadTexture("resources/textures/block_solid.png", false, "block_solid");

	GameLevel one; one.Load("resources/levels/level1.txt", this->Width, this->Height / 2);
	GameLevel two; two.Load("resources/levels/level2.txt", this->Width, this->Height / 2);
	GameLevel three; three.Load("resources/levels/level3.txt", this->Width, this->Height / 2);
	GameLevel four; four.Load("resources/levels/level4.txt", this->Width, this->Height / 2);
	
	this->Levels.push_back(one);
	this->Levels.push_back(two);
	this->Levels.push_back(three);
	this->Levels.push_back(four);
}

void Game::ProcessInput(float dt)
{
}

void Game::Update(float dt)
{
}

void Game::Render()
{
	if (this->State == GAME_ACTIVE)
	{
		Texture texture = ResourceManager::GetTexture("background");
		Renderer->DrawSprite(texture,
			glm::vec2(0.0f, 0.0f), glm::vec2(this->Width, this->Height), 0.0f
		);

		this->Levels[this->LevelNumber].Draw(*Renderer);
	}
}
