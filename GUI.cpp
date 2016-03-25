#include "GUI.h"

GUI::GUI() {

}

GUI::GUI(const glm::vec2& position, const glm::vec2& dimensions, const glm::vec4& uv, float rowNum, Snicker::GLTexture texture, Snicker::ColorRGBA8 color) {
	m_position = position;
	m_dimensions = dimensions;
	m_color = color;
	m_texture = texture;
	m_uv = uv;
}

GUI::~GUI() {

}

void GUI::init() {

}

void GUI::draw(Snicker::SpriteBatch& spriteBatch) {
	glm::vec4 destRect;
	destRect.x = m_position.x;
	destRect.y = m_position.y -m_dimensions.y;
	destRect.z = m_dimensions.x;
	destRect.w = m_dimensions.y;

	spriteBatch.draw(destRect, m_uv, m_texture.id, -999, m_color);
}

void GUI::update(Snicker::InputManager& inputManager) {

}