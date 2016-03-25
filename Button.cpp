#include "Button.h"
#include <SnickerSource\ResourceManager.h>
#include <iostream>

Button::Button(glm::vec2 position, glm::vec2 dimensions, std::string texture_fp, Snicker::ColorRGBA8 color, std::string label, std::string spriteFontPath)
	//: m_position(position), 
		//m_dimensions(dimensions)
{
	m_position = position;
	m_dimensions = dimensions;
	m_label = label;
	m_texture_fp = texture_fp;
	m_spriteFont = new Snicker::SpriteFont(spriteFontPath.c_str(), 20);;
	load();
}

Button::~Button() {
	
}

void Button::load() {
	Snicker::GLTexture button_texture = Snicker::ResourceManager::getTexture(m_texture_fp);

	m_button = GUI(m_position, m_dimensions, glm::vec4(1.0f, 0.0f, 1.0f, 1.0f),
		0.0f, button_texture, Snicker::ColorRGBA8(0, 0, 0, 0));
}

void Button::unload() {

}

void Button::draw(Snicker::SpriteBatch& spriteBatch) {
	
	m_spriteFont->draw(spriteBatch, m_label.c_str(), m_position,
		glm::vec2(1.0), 0.0f, Snicker::ColorRGBA8(0, 0, 0, 255), Snicker::Justification::RIGHT);

	m_button.draw(spriteBatch);	
}

bool Button::isMouseInBounds(const glm::vec2 mouse_position, const glm::vec2 ui_position) {
	bool isInBounds = false;

	std::cout << "Button X: " << (ui_position.x + m_position.x) << " Button Y: " << (ui_position.y + m_position.y) << std::endl;

	if (mouse_position.x >= (ui_position.x + m_position.x) && mouse_position.x <= (ui_position.x + m_dimensions.x)) {
		if (mouse_position.y >= (ui_position.y + m_position.y) && mouse_position.y <= (ui_position.y + m_dimensions.y)) {
			isInBounds = true;
		}
	}
	return isInBounds;
}