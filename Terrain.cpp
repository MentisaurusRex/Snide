#include "Terrain.h"

Terrain::Terrain() {

}

Terrain::Terrain(const glm::vec2& position, const glm::vec2& dimensions, const glm::vec4& uv, float rowNum, Snicker::GLTexture texture, Snicker::ColorRGBA8 color)
{
	m_position = position;
	m_dimensions = dimensions;
	m_rowNum = rowNum;
	m_color = color;
	m_texture = texture;
	m_uv = uv;
	
}


Terrain::~Terrain()
{
}

void Terrain::init() {
	
}

void Terrain::draw(Snicker::SpriteBatch& spriteBatch) {
	glm::vec4 destRect;
	destRect.x = m_position.x - m_dimensions.x / 2.0f;
	destRect.y = m_position.y - m_dimensions.y / 2.0f;
	destRect.z = m_dimensions.x;
	destRect.w = m_dimensions.y;

	spriteBatch.draw(destRect, m_uv, m_texture.id, m_rowNum, m_color);
}

void Terrain::update(Snicker::InputManager& inputManager) {

}
