#include "Player.h"
#include <SDL\SDL.h>


Player::Player()
{
}


Player::~Player()
{
}

void Player::init(const glm::vec2& position, const glm::vec2& dimensions, Snicker::GLTexture texture, Snicker::ColorRGBA8 color, float speed) {
	m_position = position;
	m_dimensions = dimensions;
	m_color = color;
	m_texture = texture;
	m_speed = speed;

	m_rowNum = m_position.y;
}

void Player::draw(Snicker::SpriteBatch& spriteBatch) {
	glm::vec4 destRect;
	destRect.x = m_position.x - m_dimensions.x / 2.0f;
	destRect.y = m_position.y - m_dimensions.y / 2.0f;
	destRect.z = m_dimensions.x;
	destRect.w = m_dimensions.y;

	spriteBatch.draw(destRect, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), m_texture.id, m_rowNum, m_color);

}

void Player::update(Snicker::InputManager& inputManager) {
	if (inputManager.isKeyDown(SDLK_a)) {
		m_position += glm::vec2(-m_speed, 0.0f);
		m_rowNum = m_position.y;
	}
	if (inputManager.isKeyDown(SDLK_d)) {
		m_position += glm::vec2(m_speed, 0.0f);
		m_rowNum = m_position.y;
	}
	if (inputManager.isKeyDown(SDLK_w)) {
		m_position += glm::vec2(0.0f, m_speed);
		m_rowNum = m_position.y;
	}
	if (inputManager.isKeyDown(SDLK_s)) {
		m_position += glm::vec2(0.0f, -m_speed);
		m_rowNum = m_position.y;
	}
}
