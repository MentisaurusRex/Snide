#include "Map1.h"
#include <SnickerSource\ResourceManager.h>
#include <SnickerSource\GLTexture.h>

Map1::Map1()
{
}


Map1::~Map1()
{
}

void Map1::load() {

	Snicker::GLTexture m_grassTexture = Snicker::ResourceManager::getTexture("Source/Textures/Shrub_1.png");
	Snicker::GLTexture m_dirtTexture = Snicker::ResourceManager::getTexture("Source/Textures/Dirt.png");
	Snicker::GLTexture m_fenceTexture = Snicker::ResourceManager::getTexture("Source/Textures/Fence.png");


	//Init test Terrain
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 13; j++) {
			m_terrainList.emplace_back(glm::vec2(-330.0f + (i * 32), 300.0f - (j * 32)), glm::vec2(32.0f, 32.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
									(300.0f - (j * 32)), m_grassTexture, Snicker::ColorRGBA8(255, 255, 255, 255));
		}
	}

	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			m_terrainList.emplace_back(glm::vec2(130.0f + (i * 32), 0.0f - (j * 32)), glm::vec2(32.0f, 32.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
				(0.0f - (j * 32)), m_grassTexture, Snicker::ColorRGBA8(255, 255, 255, 255));
		}
	}


	m_terrainList.emplace_back(glm::vec2(64.0f, 32.0f), glm::vec2(32.0f, 32.0f), glm::vec4(1.0f, 0.0f, 1.0f, 1.0f),
		32.0f, m_fenceTexture, Snicker::ColorRGBA8(255, 255, 255, 255));

	m_terrainList.emplace_back(glm::vec2(96.0f, 32.0f), glm::vec2(32.0f, 32.0f), glm::vec4(1.0f, 0.0f, 1.0f, 1.0f),
		32.0f, m_fenceTexture, Snicker::ColorRGBA8(255, 255, 255, 255));
	
	m_terrainList.emplace_back(glm::vec2(128.0f, 32.0f), glm::vec2(32.0f, 32.0f), glm::vec4(1.0f, 0.0f, 1.0f, 1.0f),
		32.0f, m_fenceTexture, Snicker::ColorRGBA8(255, 255, 255, 255));


	m_terrainList.emplace_back(glm::vec2(0, 0), glm::vec2(32.0f, 32.0f), glm::vec4((1.0f / 16.0f), 0.0f, (1.0f / 16.0f), (1.0f)),
		99990, m_dirtTexture, Snicker::ColorRGBA8(255, 255, 255, 255));

	m_terrainList.emplace_back(glm::vec2(0, -32.0f), glm::vec2(32.0f, 32.0f), glm::vec4((11.0f / 16.0f), 0.0f, (1.0f / 16.0f), (1.0f)),
		99990, m_dirtTexture, Snicker::ColorRGBA8(255, 255, 255, 255));

	m_terrainList.emplace_back(glm::vec2(0, -64.0f), glm::vec2(32.0f, 32.0f), glm::vec4((8.0f / 16.0f), 0.0f, (1.0f / 16.0f), (1.0f)),
		99990, m_dirtTexture, Snicker::ColorRGBA8(255, 255, 255, 255));

	m_terrainList.emplace_back(glm::vec2(32.0f, -64.0f), glm::vec2(32.0f, 32.0f), glm::vec4((5.0f / 16.0f), 0.0f, (1.0f / 16.0f), (1.0f)),
		99990, m_dirtTexture, Snicker::ColorRGBA8(255, 255, 255, 255));

	m_terrainList.emplace_back(glm::vec2(32, -96.0f), glm::vec2(32.0f, 32.0f), glm::vec4((4.0f / 16.0f), 0.0f, (1.0f / 16.0f), (1.0f)),
		99990, m_dirtTexture, Snicker::ColorRGBA8(255, 255, 255, 255));

}

void Map1::unload() {

}

void Map1::draw(Snicker::SpriteBatch& spriteBatch) {
	for (Terrain it : m_terrainList) {
		it.draw(spriteBatch);
	}
}