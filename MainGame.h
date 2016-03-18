#pragma once
#include <SDL\SDL.h>
#include <GL\glew.h>
#include <vector>

#include <SnickerSource\Sprite.h>
#include <SnickerSource\GLSLProgram.h>
#include <SnickerSource\GLTexture.h>
#include <SnickerSource\Window.h>
#include <SnickerSource\Camera2D.h>
#include <SnickerSource\SpriteBatch.h>
#include <SnickerSource\InputManager.h>
#include <SnickerSource\Timing.h>
#include <SnickerSource\SpriteFont.h>
#include <SnickerSource\AudioEngine.h>

enum class GameState { PLAY, EXIT };

class MainGame
{
public:
	MainGame();
	~MainGame();
	void run();

private:
	void initSystems();
	void initShaders();
	void gameLoop();
	void processInput();
	void drawGame();
	void drawHud();

	Snicker::Window _window;
	int _screenWidth = 1024;
	int _screenHeight = 768;
	GameState m_gameState = GameState::PLAY;
	float _maxFPS = 60.0f;

	float _fps;

	Snicker::SpriteBatch _spriteBatch;
	Snicker::SpriteBatch _hudSpriteBatch;

	Snicker::GLSLProgram _colorProgram;
	Snicker::Camera2D _camera;	
	Snicker::Camera2D _hudCamera; //heads up display
	Snicker::InputManager m_inputManager;
	Snicker::SpriteFont* _spriteFont;
	Snicker::AudioEngine m_audioEngine;

	
	
};


