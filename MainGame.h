#pragma once
#include <SDL\SDL.h>
#include <GL\glew.h>
#include <vector>

#include <Snicker\Sprite.h>
#include <Snicker\GLSLProgram.h>
#include <Snicker\GLTexture.h>
#include <Snicker\Window.h>
#include <Snicker\Camera2D.h>
#include <Snicker\SpriteBatch.h>
#include <Snicker\InputManager.h>
#include <Snicker\Timing.h>
#include <Snicker\SpriteFont.h>
#include <Snicker\AudioEngine.h>

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


