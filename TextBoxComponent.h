#pragma once

#include "ECS.h"
#include "SDL.h"
#include "Vector2D.h"
#include "Game.h"


class TextBoxComponent : public Component
{
public:
	SDL_Texture * texture;
	SDL_Rect srcRect, destRect;
	Vector2D position;

	TextBoxComponent() = default;

	~TextBoxComponent()
	{
		SDL_DestroyTexture(texture);
	}

	TextBoxComponent(int srcX, int srcY, int xpos, int ypos, int size, int wscale, int hscale, int rots, SDL_RendererFlip flp, std::string id)
	{
		flip = flp;
		rotations = rots;
		texture = Game::assets->GetTexture(id);

		position.x = xpos;
		position.y = ypos;

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = size;

		destRect.x = xpos;
		destRect.y = ypos;
		destRect.w = size * wscale;
		destRect.h = size * hscale;
	}
	
	void update() override
	{
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, rotations, flip);
	}
private:

	SDL_RendererFlip flip = SDL_FLIP_NONE;
	int rotations = 0;
};