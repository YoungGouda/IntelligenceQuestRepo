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

	bool animated = false;
	int frames = 0;
	int speed = 100;

public:

	int animIndex = 0;

	std::map<const char*, Animation > animations;

	SDL_RendererFlip spriteflip = SDL_FLIP_NONE;

	SpriteComponent() = default;
	SpriteComponent(std::string id)
	{
		setTex(id);
	}

	SpriteComponent(std::string id, bool isAnimated)
	{
		animated = isAnimated;

		Animation idle = Animation(0, 1, 100);
		Animation walkDown = Animation(1, 2, 100);
		Animation walkUp = Animation(2, 2, 100);
		Animation walkRight = Animation(3, 2, 100);
		Animation walkLeft = Animation(4, 2, 100);
		Animation walkDownRight = Animation(5, 2, 100);
		Animation walkDownLeft = Animation(6, 2, 100);
		Animation walkUpRight = Animation(7, 2, 100);
		Animation walkUpLeft = Animation(8, 2, 100);

		animations.emplace("idle", idle);
		animations.emplace("walk down", walkDown);
		animations.emplace("walk up", walkUp);
		animations.emplace("walk right", walkRight);
		animations.emplace("walk left", walkLeft);

		Play("idle");
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
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}

		srcRect.y = animIndex * transform->height;

		destRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
		destRect.y = static_cast<int>(transform->position.y) - Game::camera.y;
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, spriteflip);
	}

	void Play(const char* animName)
	{
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}
};