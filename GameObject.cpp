#include "stdafx.h"

GameObject::GameObject(const char* texturesheet, int x, int y)
{
	objTexture = TextureManager::LoadTexture(texturesheet);
	
	xpos = x;
	ypos = y;
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
	xpos++;
	ypos++;

	srcRect.h = 300;
	srcRect.w = 300;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w / 5;
	destRect.h = srcRect.h / 5;
}

void GameObject::Render()
{
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}