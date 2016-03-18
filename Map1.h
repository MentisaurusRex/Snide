#pragma once
#include "LoadMap.h"
#include "Terrain.h"
#include <vector>
class Map1 : LoadMap
{
public:
	Map1();
	~Map1();

	virtual void load() override;
	virtual void unload() override;

	void draw(Snicker::SpriteBatch& spriteBatch);
private:
	std::vector<Terrain> m_terrainList;	
};


