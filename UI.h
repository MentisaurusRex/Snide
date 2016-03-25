#pragma once
#include "LoadMap.h"
#include "Terrain.h"
#include "Button.h"
#include <vector>
#include <SnickerSource\SpriteFont.h>

class UI : LoadMap
{
public:
	UI();
	~UI();

	void init(float xPos, float yPos, float width, float height, std::string texturePath);

	virtual void load() override;
	virtual void unload() override;

	void addButton(std::string label);
	void draw(Snicker::SpriteBatch& spriteBatch);

protected:

	glm::vec2 m_position;
	glm::vec2 m_dimensions;
	
	GUI m_uiBox;
	std::vector<Button> m_buttons;
	std::string m_texturePath;

};

