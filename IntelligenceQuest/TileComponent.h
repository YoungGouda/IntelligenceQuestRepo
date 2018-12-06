#pragma once


#include "ECS.h"
#include "SDL.h"


class TileComponent : public Component
{
public:
	SDL_Texture * texture;
	SDL_Rect srcRect, destRect;
	Vector2D position;

	TileComponent() = default;

	~TileComponent()
	{
		SDL_DestroyTexture(texture);
	}

	TileComponent(int srcX, int srcY, int xpos, int ypos, int tsize, int tscale, int rots, SDL_RendererFlip flp, std::string id) 
	{
		flip = flp;
		rotations = rots;
		texture = Game::assets->GetTexture(id);

		position.x = xpos;
		position.y = ypos;

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = tsize;

		destRect.x = xpos;
		destRect.y = ypos;
		destRect.w = destRect.h = tsize * tscale;
	}

	void update() override
	{
		destRect.x = position.x - Game::camera.x;
		destRect.y = position.y - Game::camera.y;
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, rotations, flip);
	}
private:

	SDL_RendererFlip flip = SDL_FLIP_NONE;
	int rotations = 0;
};