#pragma once

#include "Game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component
{
public:
	TransformComponent * transform;
	SpriteComponent * sprite;

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override
	{
		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_UP:
				transform->velocity.y = -1;
				sprite->Play("walk up");
				break;
			case SDLK_DOWN:
				transform->velocity.y = 1;
				sprite->Play("walk down");
				break;
			case SDLK_RIGHT:
				transform->velocity.x = 1;
				sprite->Play("walk right");
				break;
			case SDLK_LEFT:
				transform->velocity.x = -1;
				sprite->Play("walk left");
				break;
			case SDLK_ESCAPE:
				Game::isRunning = false;
			default:
				break;
			}
		}
		if (Game::event.type == SDL_KEYUP)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_UP:
				transform->velocity.y = 0;
				sprite->Play("idle");
				break;
			case SDLK_DOWN:
				transform->velocity.y = 0;
				sprite->Play("idle");
				break;
			case SDLK_RIGHT:
				transform->velocity.x = 0;
				sprite->Play("idle");
				break;
			case SDLK_LEFT:
				transform->velocity.x = 0;
				sprite->Play("idle");
				break;
			default:
				break;
			}
		}
	}
};