#pragma once
#include <glm\glm.hpp>
#include <SnickerSource\Vertex.h>
#include <SnickerSource\SpriteBatch.h>
#include <SnickerSource\GLTexture.h>
#include <SnickerSource\InputManager.h>

class GUI {
public:
	GUI();
	GUI(const glm::vec2& position, const glm::vec2& dimensions, const glm::vec4& uv, float rowNum, Snicker::GLTexture texture, Snicker::ColorRGBA8 color);
	~GUI();

	void init();
	void draw(Snicker::SpriteBatch& spriteBatch);
	void update(Snicker::InputManager& inputManager);

protected:
	glm::vec2 m_position;
	glm::vec2 m_dimensions;
	glm::vec4 m_uv;
	Snicker::ColorRGBA8 m_color;
	Snicker::GLTexture m_texture;

};