#include "UI.h"
#include <SnickerSource\ResourceManager.h>
#include <SnickerSource\GLTexture.h>

UI::UI()
{
}

UI::~UI()
{
}

void UI::init(float xPos, float yPos, float width, float height, std::string texturePath) {

	m_position = glm::vec2(xPos, yPos);
	m_dimensions = glm::vec2(width, height);

	m_texturePath = texturePath;
		
	load();
}

void UI::load() {
	Snicker::GLTexture m_displayBox = Snicker::ResourceManager::getTexture(m_texturePath);
	
	m_uiBox = GUI(m_position, m_dimensions, glm::vec4(1.0f, 0.0f, 1.0f, 1.0f),
		0.0f, m_displayBox, Snicker::ColorRGBA8(255, 255, 255, 255));
}

void UI::unload() {

}

void UI::addButton(std::string label) {
	int line = m_buttons.size();
	int yPos = m_position.y - (35 * (line + 1));
	int xPos = m_position.x + 35;

	m_buttons.emplace_back(glm::vec2(xPos, yPos), glm::vec2(m_dimensions.x, 25), "Source/Textures/display2.png",
							Snicker::ColorRGBA8(255, 255, 255, 255), label, "Source/Fonts/STEREOFI.ttf");
}

void UI::draw(Snicker::SpriteBatch& spriteBatch) {
	m_uiBox.draw(spriteBatch);

	for (Button it : m_buttons) {
		it.draw(spriteBatch);
	}
}
