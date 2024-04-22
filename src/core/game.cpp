#include "game.h"
#include <camera.h>
#include <texture.h>
#include <VAO.h>
#include <spriteRenderer.h>
#include <resourceManager.h>
#include <gameLevel.h>
#include <ballObject.h>

SpriteRenderer* Renderer;

GameObject* Player;

BallObject* Ball;


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
	// shader_sprite.setInt("image", 0);
	shader_sprite.setMat4("projection", projection);

	// set renderer controls
	Renderer = new SpriteRenderer(shader_sprite);

	// load textures
	// ResourceManager::LoadTexture("resources/textures/minato.png", true, "minato");
	ResourceManager::LoadTexture("resources/textures/background.jpg", false, "background");
	ResourceManager::LoadTexture("resources/textures/block.png", false, "block");
	ResourceManager::LoadTexture("resources/textures/block_solid.png", false, "block_solid");
	ResourceManager::LoadTexture("resources/textures/paddle.png", true, "paddle");

	GameLevel one; one.Load("resources/levels/level1.txt", this->Width, this->Height / 2);
	GameLevel two; two.Load("resources/levels/level2.txt", this->Width, this->Height / 2);
	GameLevel three; three.Load("resources/levels/level3.txt", this->Width, this->Height / 2);
	GameLevel four; four.Load("resources/levels/level4.txt", this->Width, this->Height / 2);
	
	this->Levels.push_back(one);
	this->Levels.push_back(two);
	this->Levels.push_back(three);
	this->Levels.push_back(four);

	glm::vec2 playerPos = glm::vec2(
		this->Width / 2.0f - PLAYER_SIZE.x / 2.0f,
		this->Height - PLAYER_SIZE.y
	);

	Texture playerSprite = ResourceManager::LoadTexture("resources/textures/paddle.png", true, "paddle");

	Player = new GameObject(playerPos, PLAYER_SIZE, playerSprite);

	Texture ballSprite = ResourceManager::LoadTexture("resources/textures/awesomeface.png", true, "paddle");

	glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -BALL_RADIUS * 2.0f);

	Ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY, ballSprite);
}

void Game::ProcessInput(float dt)
{
	if (this->State == GAME_ACTIVE)
	{
		float velocity = PLAYER_VELOCITY * dt;
		// move playerboard
		if (this->Keys[GLFW_KEY_A])
		{
			if (Player->Position.x >= 0.0f)
				Player->Position.x -= velocity;
		}
		if (this->Keys[GLFW_KEY_D])
		{
			if (Player->Position.x <= this->Width - Player->Size.x)
				Player->Position.x += velocity;
		}
		if (this->Keys[GLFW_KEY_W])
		{
			Ball->Velocity = glm::vec2(100.0f, -200.0f);
			Ball->Stuck = false;
		}

		if (Ball->Stuck) {
			Ball->Position = Player->Position + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -BALL_RADIUS * 2.0f);
		}
	}
}

void Game::Update(float dt)
{
	Ball->Position = Ball->Move(dt, this->Width);
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
		Player->Draw(*Renderer);
		Ball->Draw(*Renderer);
	}
}
