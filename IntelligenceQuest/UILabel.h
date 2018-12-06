#pragma once

#include "ECS.h"
#include "AssetManager.h"
#include "Game.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>


class UILabel : public Component
{
public:

	UILabel(const int x, const int y, const std::string text, const std::string font, SDL_Color& color) : 
		labelText(text), labelFont(font), textColor(color)
	{
		position.x = x;
		position.y = y;

		SetLabelText(labelText, labelFont);
	}
	~UILabel()
	{}

	void SetLabelText(std::string text, const std::string font)
	{
		SDL_Surface* surf = TTF_RenderText_Blended(Game::assets->GetFont(font), text.c_str(), textColor);
		labelTexture = SDL_CreateTextureFromSurface(Game::renderer, surf);
		SDL_FreeSurface(surf);

		SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);

	}
	
	void draw() override
	{
		SDL_RenderCopy(Game::renderer, labelTexture, nullptr, &position);
	}

private:
	SDL_Rect position;
	std::string labelText;
	std::string labelFont;
	SDL_Color textColor;
	SDL_Texture* labelTexture;
};