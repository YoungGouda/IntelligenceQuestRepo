#pragma once
#include <string>


class Map
{
public:
	Map(std::string tID, int ms, int ts);
	~Map();

	void LoadMap(std::string path, int sizex, int sizey);
	void AddTile(int srcX, int srcY, int x, int y);
private:
	std::string texID;
	const char* mapFilePath;
	int mapScale;
	int tileSize;
	int scaledSize;
};