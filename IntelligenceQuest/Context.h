#pragma once
#include "InputContext.h"

class Context
{
public:
	const char * defaultName;

	Context(const char * name)
	{
		defaultName = name;
	}
	~Context()
	{}

	void readInputContexts(const char * path, std::map<const char *, SDL_Keycode> keyMap );

	void addController(InputContext inputContext);
private:
};