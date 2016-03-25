#pragma once
#include "LoadMap.h"
#include <SnickerSource\GLTexture.h>
#include <glm\glm.hpp>
#include <SnickerSource\Vertex.h>
#include <SnickerSource\SpriteFont.h>
#include "GUI.h"

class Button : LoadMap
{
public:
	Button(glm::vec2 position, glm::vec2 dimensions, std::string texture_fp, Snicker::ColorRGBA8 color, std::string label, std::string spriteFontPath);
	~Button();

	virtual void load() override;
	virtual void unload() override;

	void draw(Snicker::SpriteBatch& spriteBatch);
	bool isMouseInBounds(const glm::vec2 mouse_position, const glm::vec2 ui_position);

private:
	std::string m_label;
	glm::vec2 m_position;
	glm::vec2 m_dimensions;
	std::string m_texture_fp;

	Snicker::SpriteFont* m_spriteFont;

	GUI m_button;

};