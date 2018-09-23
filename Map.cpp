#include "stdafx.h"
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <rapidxml.hpp>

extern Manager manager;

Map::Map(std::string tID, int ms, int ts) : texID(tID), tileSize(ts), mapScale(ms)
{
	scaledSize = ts * ms;
}

Map::~Map()
{
}

void Map::LoadFullMap(std::string path)
{
	int srcX, srcY, scaledX, scaledY, rotations, tileID;

	std::ifstream mapFile (path);
	rapidxml::xml_document<> map;
	rapidxml::xml_node<> * root_node;
	const char * layerName;
	const char * tileName;
	const char * flipx;

	std::vector<char> buffer((std::istreambuf_iterator<char>(mapFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');

	map.parse<0>(&buffer[0]);

	root_node = map.first_node("tilemap");

	for (rapidxml::xml_node<> * layer_node = root_node->first_node("layer"); layer_node; layer_node = layer_node->next_sibling())
	{
		layerName = layer_node->first_attribute("name")->value();

		if (!strcmp(layerName, "Layer 0"))
		{

			for (rapidxml::xml_node<> * tile_node = layer_node->first_node("tile"); tile_node; tile_node = tile_node->next_sibling())
			{
				SDL_RendererFlip flip = SDL_FLIP_NONE;

				scaledX = atoi(tile_node->first_attribute("x")->value()) * scaledSize;
				scaledY = atoi(tile_node->first_attribute("y")->value()) * scaledSize;
				

				tileID = atoi(tile_node->first_attribute("tile")->value());
				
				srcX = ( tileID % 10 ) * tileSize;
				srcY = ( (tileID / 10 )  ) * tileSize;

				rotations = atoi(tile_node->first_attribute("rot")->value());

				flipx = tile_node->first_attribute("flipX")->value();

				if (!strcmp(flipx, "true"))
					flip = SDL_FLIP_HORIZONTAL;

				AddTile(srcX, srcY, scaledX, scaledY, rotations, flip);
			}
		}

		if (!strcmp(layerName, "Layer 1"))
		{
			for (rapidxml::xml_node<> * tile_node = layer_node->first_node("tile"); tile_node; tile_node = tile_node->next_sibling())
			{
				scaledX = atoi(tile_node->first_attribute("x")->value()) * scaledSize;
				scaledY = atoi(tile_node->first_attribute("y")->value()) * scaledSize;

				tileName = tile_node->first_attribute("tile")->value();

				if (!strcmp(tileName, "0"))
				{
					auto& tcol(manager.addEntity());
					tcol.addComponent<ColliderComponent>("terrain", scaledX, scaledY, scaledSize);
					tcol.addGroup(Game::groupColliders);
				}
			}
		} 
	}
}



void Map::AddTile(int srcX, int srcY, int x, int y, int rots, SDL_RendererFlip flp)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, x, y, tileSize, mapScale, rots, flp, texID);
	tile.addGroup(Game::groupMap);
}

