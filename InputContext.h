#pragma once

#include "Inputs.h"

class InputContext
{
public:
	InputContext()
	{};
	 
	InputContext(const char* cntxtID, std::list<State> stL, std::list<Action> aL, std::list<Range> rL)
		: contextID(cntxtID), states(stL), actions(aL), ranges(rL)
	{};

	~InputContext()
	{};

	const char * contextID;
	std::list<State> states;
	std::list<Action> actions;
	std::list<Range> ranges;

private:
};





