#include "MenuUI.h"
#include <iostream>

void MenuUI::init(float xPos, float yPos, float width, float height, std::string texturePath) {
	UI::init(xPos, yPos, width, height, texturePath);

	addButton("Test1");
	addButton("Test2");

}

void MenuUI::processButtonMouseOver(Snicker::InputManager& inputManager) {

	glm::vec2 coords = inputManager.getMouseCoords();

	std::cout << "X: " << coords.x << " Y: " << coords.y << std::endl;
	int var = 0;

	if (m_buttons[0].isMouseInBounds(inputManager.getMouseCoords(), m_position)) {
		var = 1;
	}

	if (m_buttons[1].isMouseInBounds(inputManager.getMouseCoords(), m_position)) {
		var = 2;
	}

}


