#include "stdafx.h"
#include <sstream>
#include <stdio.h>
#include <string>
// GLEW
#include <GL/glew.h>
#include <GL/GLU.h>
// GLM
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
// FreeType
#include <ft2build.h>
#include FT_FREETYPE_H
#include "Font.h"


Map* map;
Context context("map context");
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = { 0, 0, 2560, 2240 };
AssetManager* Game::assets = new AssetManager(&manager);

//OpenGL context
SDL_GLContext gContext;

GLuint Game::SCREEN_WIDTH;
GLuint Game::SCREEN_HEIGHT;

/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
	GLuint TextureID;   // ID handle of the glyph texture
	glm::ivec2 Size;    // Size of glyph
	glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
	GLuint Advance;    // Horizontal offset to advance to next glyph
};

bool Game::isRunning = false;
auto& player(manager.addEntity());
auto& test(manager.addEntity());
auto& test2(manager.addEntity());
auto& label(manager.addEntity());

Game::Game() 
{}

Game::~Game()
{}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	
	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;

	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) 
	{
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		//Double buffer should be on by default, but I set it anyway
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, 0);
		gContext = SDL_GL_CreateContext(window);

		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;
	}

	assets->AddTexture("terrain", "tile_set_2.png");
	assets->AddTexture("player", "flesh_child_full.png");
	assets->AddTexture("meak", "weak_father_full_128x64.png");
	assets->AddTexture("dad", "dad_full_128x64.png");
	assets->AddTexture("projectile", "rock.png");
	assets->AddTexture("textbox", "textbox.png");

	assets->AddFont("gilsans", "GIL_____.TTF", 18);

	map = new Map("terrain", 3, 32);

	map->LoadFullMap("testMap.xml");
	

	
	test2.addComponent<TransformComponent>(500, 500, 128, 64, 1);
	test2.addComponent<ControllerComponent>(1.5);
	test2.addComponent<SpriteComponent>("meak", false);
	test2.addGroup(groupPlayers);

	test.addComponent<TransformComponent>(564, 500, 128, 64, 1);
	test.addComponent<ControllerComponent>(2);
	test.addComponent<SpriteComponent>("dad", false);
	test.addGroup(groupPlayers); 
	
	player.addComponent<TransformComponent>(628, 564, 64, 64, 1);
	player.addComponent<SpriteComponent>("player", false);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

	SDL_Color white = { 255, 255, 255, 255 };


	label.addComponent<UILabel>(10, 10, "TEST", "gilsans", white);


	assets->CreateProjectile(Vector2D(600, 600), Vector2D(2,0), 200, 2, "projectile");
	assets->CreateProjectile(Vector2D(400, 620), Vector2D(2,1), 200, 2, "projectile");
	assets->CreateProjectile(Vector2D(100, 630), Vector2D(2,2), 200, 2, "projectile");
	assets->CreateProjectile(Vector2D(700, 610), Vector2D(2,-1), 200, 2, "projectile");
}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectiles));
auto& controllers(manager.getGroup(Game::groupControllers));
auto& textboxes(manager.getGroup(Game::groupTextBoxes));


//void Game::initGL()
//{
//	// Compile and setup the shader
//	shader = Shader("text.vs", "text.frag");
//	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(Game::SCREEN_WIDTH), 0.0f, static_cast<GLfloat>(Game::SCREEN_HEIGHT));
//	shader.use();
//	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
//
//	//Initialize Projection Matrix
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//
//	//Initialize Modelview Matrix
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//
//	glewExperimental = GL_TRUE;
//
//	if (TTF_Init() == -1)
//	{
//		std::cout << "Error : SDL_TTF " << std::endl;
//	}
//
//	// Define the viewport dimensions
//	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
//
//	// Set OpenGL options
//	glEnable(GL_CULL_FACE);
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//	// Init Glyph Atlas
//	font->initFont(128, 20, "GIL_____.TTF");
//}

void Game::handleEvents()
{

	SDL_PollEvent(&event);
	
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;

	default:
		break;
	}
}

void Game::update() 
{

	SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
	Vector2D playerPos = player.getComponent<TransformComponent>().position;
	int playerHeight = player.getComponent<TransformComponent>().height;


	std::stringstream ss;
	ss << "PLayer.position: " << playerPos;

	manager.refresh();
	manager.update();

	for (auto& c : colliders)
	{
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCol, playerCol))
		{
			player.getComponent<TransformComponent>().position = playerPos;
		}
	}

	for (auto& p : projectiles)
	{
		if (Collision::AABB(player.getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider))
		{
			p->destroy();
		}
	}

	camera.x = player.getComponent<TransformComponent>().position.x - (SCREEN_WIDTH / 2);
	camera.y = player.getComponent<TransformComponent>().position.y - (SCREEN_HEIGHT / 2);

	if (camera.x < 0)
		camera.x = 0;
	if (camera.y < 0)
		camera.y = 0;
	if (camera.x > camera.w)
		camera.x = camera.w;
	if (camera.y > camera.h)
		camera.y = camera.h;
}



void Game::render()
{
	SDL_RenderClear(renderer);
	for (auto& t : tiles)
	{
		t->draw();	
	}
	for (auto& p : players)
	{
		p->draw();
	}
	for (auto& p : projectiles)
	{
		p->draw();
	}
	for (auto& t : textboxes)
	{
		t->draw();
	}
	label.draw();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
