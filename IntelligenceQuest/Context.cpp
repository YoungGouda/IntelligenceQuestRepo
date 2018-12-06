#include "stdafx.h"
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "SDL.h"
#include <rapidxml.hpp>

extern Manager manager;

void Context::readInputContexts(const char * path, std::map<const char *, SDL_Keycode> keyMap)
{
	std::list<State> states;
	std::list<Action> actions;
	std::list<Range> ranges;
	const char* contextID;
	std::ifstream inputFile(path);
	rapidxml::xml_document<> context;
	rapidxml::xml_node<> * root_node;
	std::list<SDL_Keycode> keys;
	std::list<SDL_Keycode> keyExclusions;
	SDL_EventType eventType;
	Vector2D velocity;
	const char* name;
	const char * contextName;
	const char * eventTypeName;
	const char * yVal;
	const char * xVal;
	const char * isExclude;
	double y = NAN;
	double x = NAN;


	std::vector<char> buffer((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');

	context.parse<0>(&buffer[0]);

	root_node = context.first_node("gamecontexts");

	for (rapidxml::xml_node<> * inputcontexts_node = root_node->first_node("inputcontexts"); inputcontexts_node; inputcontexts_node = inputcontexts_node->next_sibling())
	{
		contextID = inputcontexts_node->first_attribute("name")->value();
		for (rapidxml::xml_node<> * inputs_node = inputcontexts_node->first_node("inputs"); inputs_node; inputs_node = inputs_node->next_sibling())
		{
			name = inputs_node->first_attribute("name")->value();

			eventTypeName = inputs_node->first_attribute("eventtype")->value();
			eventType = SDL_KEYUP;
			if (!strcmp(eventTypeName, "SDL_KEYDOWN"))
				eventType = SDL_KEYDOWN;

			yVal = inputs_node->first_attribute("y")->value();
			xVal = inputs_node->first_attribute("x")->value();

			if (strcmp("NaN", yVal))
				y = atoi(yVal);
			else
				y = NAN;
			if (strcmp("NaN", xVal))
				x = atoi(xVal);
			else
				x = NAN;

			velocity.x = x;
			velocity.y = y;

			keys.clear();
			keyExclusions.clear();
			for (rapidxml::xml_node<> * input_node = inputcontexts_node->first_node("input"); input_node; input_node = input_node->next_sibling())
			{
				isExclude = input_node->first_attribute("isexclude")->value();

				if (!strcmp(isExclude, "true"))
					keys.push_back(keyMap[input_node->first_attribute("keypress")->value()]);
				else
					keyExclusions.push_back(keyMap[input_node->first_attribute("keypress")->value()]);

			}

			contextName = inputs_node->first_attribute("context")->value();

			if (!strcmp("state", contextName))
				states.push_back(State(name, keys, keyExclusions, eventType, velocity, inputs_node->first_attribute("animation")->value()));
		}
		addController( InputContext(contextID, states, actions, ranges) );
	}
}


void Context::addController(InputContext inContext)
{
}