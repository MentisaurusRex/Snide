#pragma once

#include <SnickerSource\IGameScreen.h>
#include <SnickerSource\SpriteBatch.h>
#include <SnickerSource\GLSLProgram.h>
#include <SnickerSource\Camera2D.h>
#include <SnickerSource\GLTexture.h>
#include <SnickerSource\Window.h>
#include "Player.h"
#include "Map1.h"

class GamePlayScreen : public Snicker::IGameScreen
{
public:
	GamePlayScreen(Snicker::Window* window);
	~GamePlayScreen();

	virtual int getNextScreenIndex() const override;
	virtual int getPreviousScreenIndex() const override;

	//Called at beginning and end of application
	virtual void build() override;
	virtual void destroy() override;

	//Called when a screen enters and exits focus
	virtual void onEntry() override;
	virtual void onExit() override;

	//Called in main game loop
	virtual void update() override;
	virtual void draw() override;

private:
	void checkInput();

	Snicker::SpriteBatch m_spriteBatch;
	Snicker::GLSLProgram m_textureProgram;
	Snicker::Camera2D m_camera;
	Snicker::GLTexture m_playerTexture;
	Snicker::GLTexture m_grassTexture;
	Snicker::Window* m_window;

	Player m_player;
	
	Map1 m_map;

	
};

