#pragma once

#include <Snicker\IMainGame.h>
#include "GamePlayScreen.h"

class App : public Snicker::IMainGame{
public:
	App();
	~App();

	virtual void onInit() override;
	virtual void addScreens() override;
	virtual void onExit() override;

private:
	std::unique_ptr<GamePlayScreen> m_gameplayScreen = nullptr;
};

