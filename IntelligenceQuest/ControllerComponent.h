#pragma once

#include <string>
#include "InputContext.h"
#include "ECS.h"
#include "game.h"
#include "Context.h"
#include "Inputs.h"
#include <SDL.h>
#include <cmath>

extern Manager manager;

class ControllerComponent : public Component
{
public:
	KeyboardHandler * keyboard = new KeyboardHandler();

	SDL_Scancode keys[4] = { SDL_SCANCODE_DOWN, SDL_SCANCODE_UP, SDL_SCANCODE_RIGHT, SDL_SCANCODE_LEFT };
	const char * animations[8] = { "walk down", "walk up", "walk right", "walk left", "walk down right", "walk down left", "walk up right", "walk up left" };
	
	ControllerComponent(double vSc) : vScale(vSc)
	{}

	~ControllerComponent()
	{}

	void createPlayerMovement()
	{
		if (!keyboard->checkKeyState(keys[0]) || !keyboard->checkKeyState(keys[1]))
		{
			entity->getComponent<TransformComponent>().velocity.y = 0;
			entity->getComponent<SpriteComponent>().animated = false;
		}
		if (!keyboard->checkKeyState(keys[2]) || !keyboard->checkKeyState(keys[3]))
		{
			entity->getComponent<TransformComponent>().velocity.x = 0;
			entity->getComponent<SpriteComponent>().animated = false;
		}

		if (keyboard->checkKeyState(keys[0]) && keyboard->checkKeyState(keys[2]))
		{
			entity->getComponent<TransformComponent>().velocity.y = vScale * std::pow(2, (1 / 2) ) / 2;
			entity->getComponent<TransformComponent>().velocity.x = vScale * std::pow(2, (1 / 2) ) / 2;
			entity->getComponent<SpriteComponent>().animated = true;
			entity->getComponent<SpriteComponent>().Play(animations[4]);
		}
		else if (keyboard->checkKeyState(keys[0]) && keyboard->checkKeyState(keys[3]))
		{
			entity->getComponent<TransformComponent>().velocity.y = vScale * std::pow(2, (1 / 2) ) / 2;
			entity->getComponent<TransformComponent>().velocity.x = -vScale * std::pow(2, (1 / 2) ) / 2;
			entity->getComponent<SpriteComponent>().animated = true;
			entity->getComponent<SpriteComponent>().Play(animations[5]);
		}
		else if (keyboard->checkKeyState(keys[1]) && keyboard->checkKeyState(keys[2]))
		{
			entity->getComponent<TransformComponent>().velocity.y = -vScale * std::pow(2, (1 / 2)) / 2;
			entity->getComponent<TransformComponent>().velocity.x = vScale * std::pow(2, (1 / 2)) / 2;
			entity->getComponent<SpriteComponent>().animated = true;
			entity->getComponent<SpriteComponent>().Play(animations[6]);
		}
		else if (keyboard->checkKeyState(keys[1]) && keyboard->checkKeyState(keys[3]))
		{
			entity->getComponent<TransformComponent>().velocity.y = -vScale * std::pow(2, (1 / 2) ) / 2;
			entity->getComponent<TransformComponent>().velocity.x = -vScale * std::pow(2, (1 / 2) ) / 2;
			entity->getComponent<SpriteComponent>().animated = true;
			entity->getComponent<SpriteComponent>().Play(animations[7]);
		}
		else if (keyboard->checkKeyState(keys[0]))
		{
			entity->getComponent<TransformComponent>().velocity.y = vScale;
			entity->getComponent<SpriteComponent>().animated = true;
			entity->getComponent<SpriteComponent>().Play(animations[0]);
		}
		else if (keyboard->checkKeyState(keys[1]))
		{
			entity->getComponent<TransformComponent>().velocity.y = -vScale;
			entity->getComponent<SpriteComponent>().animated = true;
			entity->getComponent<SpriteComponent>().Play(animations[1]);
		}
		else if (keyboard->checkKeyState(keys[2]))
		{
			entity->getComponent<TransformComponent>().velocity.x = vScale;
			entity->getComponent<SpriteComponent>().animated = true;
			entity->getComponent<SpriteComponent>().Play(animations[2]);
		}
		else if (keyboard->checkKeyState(keys[3]))
		{
			entity->getComponent<TransformComponent>().velocity.x = -vScale;
			entity->getComponent<SpriteComponent>().animated = true;
			entity->getComponent<SpriteComponent>().Play(animations[3]);
		}
	}

	void update() override
	{
		if (frameCount % 5 == 0)
		{
			createPlayerMovement();
		}
		frameCount++;
	}
private:
	double vScale;
	int frameCount = 0;
};

