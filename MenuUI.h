#pragma once
#include "UI.h"



class MenuUI : public UI {

public:

	void init(float xPos, float yPos, float width, float height, std::string texturePath);
	void processButtonMouseOver(Snicker::InputManager& inputManager);

};