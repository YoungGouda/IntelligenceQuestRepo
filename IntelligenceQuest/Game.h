#pragma once

#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <vector>
#include "AssetManager.h"
#include "InputContext.h"
#include "GL/glew.h"

class Game {

public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	//OpenGL
	void initGL();

	void handleEvents();
	void update();
	void render();
	void clean();

	bool running() {return isRunning;}


	
	static SDL_Renderer *renderer;
	static SDL_Event event;
	static bool isRunning;
	static SDL_Rect camera;
	static AssetManager* assets;
	static GLuint SCREEN_HEIGHT;
	static GLuint SCREEN_WIDTH;
	SDL_Window *window;

	enum groupLabels : std::size_t
	{
		groupMap,
		groupPlayers,
		groupColliders,
		groupProjectiles,
		groupControllers,
		groupTextBoxes
	};

private:

};
