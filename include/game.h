#pragma once

#include <vector>
#include "gameLevel.h"


enum GameState
{
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

class Game
{
public:
	GameState State;
	bool Keys[1024];
	unsigned int Width, Height;
	std::vector<GameLevel> Levels;
	unsigned int LevelNumber = 0;

	Game(unsigned int width, unsigned int height);
	~Game();

	void Init();
	void ProcessInput(float dt);
	void Update(float dt);
	void Render();
};

