#pragma once

#include <string>
#include "SDL.h"
#include <list>
#include "Vector2D.h"

class Action {
};

class State
{
public:

	State(const char* nm, std::list<SDL_Keycode> kP, std::list<SDL_Keycode> kE, SDL_EventType eT, Vector2D vel, const char* anim)
		: name(nm), keyPresses(kP), keyExclusions(kE), eventType(eT), velocity(vel), animation(anim)
	{}

	SDL_EventType eventType;
	Vector2D velocity;
	const char* name;
	std::list<SDL_Keycode> keyPresses;
	std::list<SDL_Keycode> keyExclusions;
	const char* animation;
private:

};
class Range {
};
