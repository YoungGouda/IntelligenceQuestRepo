#include "stdafx.h"

ControllerComponent::ControllerComponent()
{
	states.push_back(State("down release", std::list<SDL_Keycode>(SDLK_DOWN), std::list<SDL_Keycode>(), SDL_KEYUP, Vector2D(NAN, 0), "none"));
	states.push_back(State("right release", std::list<SDL_Keycode>(SDLK_RIGHT), std::list<SDL_Keycode>(), SDL_KEYUP, Vector2D(0, NAN), "none"));
	states.push_back(State("left release", std::list<SDL_Keycode>(SDLK_LEFT), std::list<SDL_Keycode>(), SDL_KEYUP, Vector2D(0, NAN), "none"));
	states.push_back(State("up right", std::list<SDL_Keycode>(SDLK_UP, SDLK_RIGHT), std::list<SDL_Keycode>(), SDL_KEYDOWN, Vector2D(0.707, -0.707), "walk up right"));
	states.push_back(State("up left", std::list<SDL_Keycode>(SDLK_UP, SDLK_LEFT), std::list<SDL_Keycode>(), SDL_KEYDOWN, Vector2D(-0.707, -0.707), "walk up left"));
	states.push_back(State("down right", std::list<SDL_Keycode>(SDLK_DOWN, SDLK_RIGHT), std::list<SDL_Keycode>(), SDL_KEYDOWN, Vector2D(0.707, 0.707), "walk down right"));
	states.push_back(State("down left", std::list<SDL_Keycode>(SDLK_DOWN, SDLK_LEFT), std::list<SDL_Keycode>(), SDL_KEYDOWN, Vector2D(-0.707, 0.707), "walk down left"));
	states.push_back(State("up", std::list<SDL_Keycode>(SDLK_UP), std::list<SDL_Keycode>(SDLK_RIGHT, SDLK_LEFT), SDL_KEYDOWN, Vector2D(0, -1), "walk up"));
	states.push_back(State("down", std::list<SDL_Keycode>(SDLK_DOWN), std::list<SDL_Keycode>(SDLK_RIGHT, SDLK_LEFT), SDL_KEYDOWN, Vector2D(0, 1), "walk down"));
	states.push_back(State("right", std::list<SDL_Keycode>(SDLK_RIGHT), std::list<SDL_Keycode>(SDLK_UP, SDLK_DOWN), SDL_KEYDOWN, Vector2D(1, 0), "walk right"));
	states.push_back(State("left", std::list<SDL_Keycode>(SDLK_LEFT), std::list<SDL_Keycode>(SDLK_UP, SDLK_DOWN), SDL_KEYDOWN, Vector2D(-1, 0), "walk left"));
}