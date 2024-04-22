#pragma once
#include "gameObject.h"

class BallObject : public GameObject
{
public:
	float Radius;
	bool Stuck;

	BallObject();
	BallObject(glm::vec2 pos, float radius, glm::vec2 velocity, Texture sprite);

	glm::vec2 Move(float deltaTime, unsigned int window_width);
	void Reset(glm::vec2 pos, glm::vec2 velocity);
};
