#pragma once

#include "Game.h"
#include "ECS.h"
#include "Components.h"
#include <string>
#include <vector>
#include "InputContext.h"
#include "KeyboardHandler.h"

extern Manager manager;

class KeyboardController : public Component
{
public:
	KeyboardController()
	{}

	~KeyboardController()
	{}

	TransformComponent * transform;
	KeyboardHandler * keyboard = new KeyboardHandler();
	SpriteComponent * sprite;

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override
	{
		if (frameCount % 5 == 0)
		{
			/***********
			 * Actions
			 ************/
			if (keyboard->checkKeyState(SDL_SCANCODE_Z))
			{
				switch (zaction % 2)
				{
				case 0:
					Game::assets->CreateTextBox(transform->position.x - Game::camera.x, transform->position.y - Game::camera.y, 15, 7, 50, 100, 2, "I am extremely intelligent");
					break;
				case 1:
					for (auto& t : manager.getGroup(Game::groupTextBoxes))
					{
						t->delGroup(Game::groupTextBoxes);
					}
					break;
				default:
					break;
				}
				zaction++;
			}
			
			if (keyboard->checkKeyState(SDL_SCANCODE_X))
			{
				switch (xaction % 2)
				{
				case 0:
					Game::assets->CreateMenu(transform->position.x - Game::camera.x, transform->position.y - Game::camera.y);
					break;
				case 1:
					for (auto& t : manager.getGroup(Game::groupTextBoxes))
					{
						t->delGroup(Game::groupTextBoxes);
					}
					break;
				default:
					break;
				}
				xaction++;
			}
			}

			/***********
			* States
			************/
			if (!keyboard->checkKeyState(SDL_SCANCODE_UP))
			{
				sprite->animated = false;
				transform->velocity.y = 0;
			}
			if (!keyboard->checkKeyState(SDL_SCANCODE_DOWN))
			{
				sprite->animated = false;
				transform->velocity.y = 0;
			}
			if (!keyboard->checkKeyState(SDL_SCANCODE_RIGHT))
			{
				sprite->animated = false;
				transform->velocity.x = 0;
			}
			if (!keyboard->checkKeyState(SDL_SCANCODE_LEFT))
			{
				sprite->animated = false;
				transform->velocity.x = 0;
			}

			if (keyboard->checkKeyState(SDL_SCANCODE_UP) && keyboard->checkKeyState(SDL_SCANCODE_RIGHT))
			{
				sprite->animated = true;
				sprite->Play("walk up right");
				transform->velocity.y = -0.707;
				transform->velocity.x = 0.707;
			}
			else if (keyboard->checkKeyState(SDL_SCANCODE_UP) && keyboard->checkKeyState(SDL_SCANCODE_LEFT))
			{
				sprite->animated = true;
				sprite->Play("walk up left");
				transform->velocity.y = -0.707;
				transform->velocity.x = -0.707;
			}
			else if (keyboard->checkKeyState(SDL_SCANCODE_DOWN) && keyboard->checkKeyState(SDL_SCANCODE_RIGHT))
			{
				sprite->animated = true;
				sprite->Play("walk down right");
				transform->velocity.y = 0.707;
				transform->velocity.x = 0.707;
			}
			else if (keyboard->checkKeyState(SDL_SCANCODE_DOWN) && keyboard->checkKeyState(SDL_SCANCODE_LEFT))
			{
				sprite->animated = true;
				sprite->Play("walk down left");
				transform->velocity.y = 0.707;
				transform->velocity.x = -0.707;
			}
			else if (keyboard->checkKeyState(SDL_SCANCODE_UP) )
			{
				sprite->animated = true;
				sprite->Play("walk up");
				transform->velocity.y = -1;
				transform->velocity.x = 0;
			}
			else if (keyboard->checkKeyState(SDL_SCANCODE_DOWN) )
			{
				sprite->animated = true;
				sprite->Play("walk down");
				transform->velocity.y = 1;
				transform->velocity.x = 0;
			}
			else if (keyboard->checkKeyState(SDL_SCANCODE_RIGHT) )
			{
				sprite->animated = true;
				sprite->Play("walk right");
				transform->velocity.x = 1;
				transform->velocity.y = 0;
			}
			else if (keyboard->checkKeyState(SDL_SCANCODE_LEFT) )
			{
				sprite->animated = true;
				sprite->Play("walk left");
				transform->velocity.x = -1;
				transform->velocity.y = 0;
			}
			frameCount++;
	}
private:
	int zaction = 0;
	int xaction = 0;
	bool xkeyCycle = false;
	bool zkeyCycle = false;
	int frameCount = 0;
};
