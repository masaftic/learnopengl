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

	// load levels
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
			Ball->Velocity = glm::vec2(100.0f, -400.0f);
			Ball->Stuck = false;
		}

		if (Ball->Stuck) {
			Ball->Position = Player->Position + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -BALL_RADIUS * 2.0f);
		}
	}
}

void Game::Update(float dt)
{
	Ball->Move(dt, this->Width);
	this->DoCollisions();
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

// COLLISIONS ARE BROKEN FOR NOW
void Game::DoCollisions()
{
	for (GameObject& box : this->Levels[this->LevelNumber].Bricks) {
		if (!box.Destroyed) {
			if (CheckCollision(*Ball, box)) {
				if (!box.IsSolid)
					box.Destroyed = true;
				Ball->Velocity.y *= -1;
				break;
			}
		}
	}

	if (CheckCollision(*Ball, *Player)) {
		// check where it hit the board, and change velocity based on where it hit the board
		float centerBoard = Player->Position.x + Player->Size.x / 2.0f;
		float distance = (Ball->Position.x + Ball->Radius) - centerBoard;
		float percentage = distance / (Player->Size.x / 2.0f);
		// then move accordingly
		float strength = 2.0f;
		glm::vec2 oldVelocity = Ball->Velocity;
		Ball->Velocity.x = INITIAL_BALL_VELOCITY.x * percentage * strength;
		Ball->Velocity.y = Ball->Velocity.y = -1.0f * abs(Ball->Velocity.y); ;
		Ball->Velocity = glm::normalize(Ball->Velocity) * glm::length(oldVelocity);
	}
}

bool CheckCollision(BallObject& one, GameObject& two)
{
	// get center point circle first 
	glm::vec2 center(one.Position + one.Radius);
	// calculate AABB info (center, half-extents)
	glm::vec2 aabb_half_extents(two.Size.x / 2.0f, two.Size.y / 2.0f);
	glm::vec2 aabb_center(
		two.Position.x + aabb_half_extents.x,
		two.Position.y + aabb_half_extents.y
	);
	// get difference vector between both centers
	glm::vec2 difference = center - aabb_center;
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
	// add clamped value to AABB_center and we get the value of box closest to circle
	glm::vec2 closest = aabb_center + clamped;
	// retrieve vector between center circle and closest point AABB and check if length <= radius
	difference = closest - center;
	return glm::length(difference) < one.Radius;
}

bool CheckCollision(GameObject& one, GameObject& two)
{
	bool collisionX = one.Position.x + one.Size.x >= two.Position.x && two.Position.x + two.Size.x >= one.Position.x;
	bool collisionY = one.Position.y + one.Size.y >= two.Position.y && two.Position.y + two.Size.y >= one.Position.y;
	return collisionX && collisionY;
}