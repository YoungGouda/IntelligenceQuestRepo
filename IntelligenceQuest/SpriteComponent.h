#pragma once

#include "Components.h"
#include "SDL.h"
#include "TextureManager.h"
#include "Animation.h"
#include <map>
#include "AssetManager.h"


class SpriteComponent : public Component
{
private:
	TransformComponent *transform;
	SDL_Texture *texture;
	SDL_Rect srcRect, destRect;

	int frames = 0;
	int speed = 200;
	int rotations = 0;

public:

	bool animated = false;
	int animIndex = 0;

	std::map<const char*, Animation > animations;

	SDL_RendererFlip spriteflip = SDL_FLIP_NONE;

	SpriteComponent() = default;
	SpriteComponent(std::string id)
	{
		setTex(id);
	}

	SpriteComponent(std::string id, int rots)
	{
		rotations = rots;
		setTex(id);
	}

	SpriteComponent(std::string id, bool isAnimated)
	{
		
		animated = isAnimated;

		Animation walkDown = Animation(0, 2, speed );
		Animation walkUp = Animation(1, 2, speed);
		Animation walkRight = Animation(2, 2, speed);
		Animation walkLeft = Animation(2, 2, speed, 0, SDL_FLIP_HORIZONTAL);
		Animation walkDownRight = Animation(3, 2, speed);
		Animation walkDownLeft = Animation(3, 2, speed, 0, SDL_FLIP_HORIZONTAL);
		Animation walkUpRight = Animation(4, 2, speed);
		Animation walkUpLeft = Animation(4, 2, speed, 0, SDL_FLIP_HORIZONTAL);

		animations.emplace("walk down", walkDown);
		animations.emplace("walk up", walkUp);
		animations.emplace("walk right", walkRight);
		animations.emplace("walk left", walkLeft);
		animations.emplace("walk down right", walkDownRight);
		animations.emplace("walk down left", walkDownLeft);
		animations.emplace("walk up right", walkUpRight);
		animations.emplace("walk up left", walkUpLeft);

		setTex(id);
	}

	~SpriteComponent()
	{
	}

	void setTex(std::string id)
	{
		texture = Game::assets->GetTexture(id);
	}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;
	}
	void update() override
	{
		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames) + transform->width;
		}
		else
		{
			srcRect.x = 0;
		}

		srcRect.y = animIndex * transform->height;

		destRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
		destRect.y = static_cast<int>(transform->position.y) - Game::camera.y;
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, rotations, spriteflip);
	}

	void Play(const char* animName)
	{
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
		rotations = animations[animName].rotations;
		spriteflip = animations[animName].flip;
	}
};