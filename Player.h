#pragma once
#include <glm\glm.hpp>
#include <Snicker\Vertex.h>
#include <Snicker\SpriteBatch.h>
#include <Snicker\GLTexture.h>
#include <Snicker\InputManager.h>
class Player
{
public:
	Player();
	~Player();

	void init(const glm::vec2& position, const glm::vec2& dimensions, Snicker::GLTexture texture, Snicker::ColorRGBA8 color, float speed = 1.0f);

	void draw(Snicker::SpriteBatch& spriteBatch);

	void update(Snicker::InputManager& inputManager);

	void setRowNum(float rowNum) { m_rowNum = rowNum; }
	float getGetNum() { return m_rowNum; }

private:
	float m_speed;
	glm::vec2 m_position;
	glm::vec2 m_dimensions;
	Snicker::ColorRGBA8 m_color;
	Snicker::GLTexture m_texture;
	float m_rowNum = 0;
};

