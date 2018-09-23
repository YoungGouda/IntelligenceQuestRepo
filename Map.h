#pragma once
#include <string>


class Map
{
public:
	Map(std::string tID, int ms, int ts);
	~Map();

	void LoadFullMap(std::string path);
	void AddTile(int srcX, int srcY, int x, int y, int rots, SDL_RendererFlip flp);
private:
	std::string texID;
	const char* mapFilePath;
	int mapScale;
	int tileSize;
	int scaledSize;
};