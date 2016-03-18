#include "MainGame.h"
#include <SnickerSource\SnickerErrors.h>
#include <iostream>
#include <string>
#include <SnickerSource\Snicker.h>
#include <SnickerSource\ResourceManager.h>

#include <algorithm>



MainGame::MainGame()
{
	_camera.init(_screenWidth, _screenHeight);
}

MainGame::~MainGame()
{
}

void MainGame::run() {
	initSystems();

	Snicker::Music music = m_audioEngine.loadMusic("Sounds/west-winds.ogg");
	music.play(-1);
	gameLoop();
}


void MainGame::initSystems() {
	Snicker::init(); //This pretty much has to go first in initialization

	m_audioEngine.init();

	_window.create("Snide", _screenWidth, _screenHeight, Snicker::BORDERLESS);

	initShaders();

	_spriteBatch.init();
	_hudSpriteBatch.init();

	//Initialize sprite font
	_spriteFont = new Snicker::SpriteFont("Fonts/STEREOFI.ttf", 128);

	_camera.init(_screenWidth, _screenHeight);
	_hudCamera.init(_screenWidth, _screenHeight);
	_hudCamera.setPosition(glm::vec2((_screenWidth / 2.0) - 280, -(_screenHeight / 2) + 128));
}

void MainGame::initShaders() {
	_colorProgram.compileShaders("Snide/Source/Shaders/colorShading.vert", "Snide/Source/Shaders/colorShading.frag");
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.addAttribute("vertexUV");
	_colorProgram.linkShaders();

}

void MainGame::gameLoop() {
	const float DESIRED_FPS = 60.0f;
	const int MAX_PHYSICS_STEPS = 6;
	const float MS_PER_SECOND = 1000;
	const float DESIRED_FRAME_TIME = MS_PER_SECOND / DESIRED_FPS;
	const float MAX_DELTA_TIME = 1.0f;

	Snicker::FPSLimiter _fpsLimiter;
	_fpsLimiter.setMaxFPS(DESIRED_FPS);	

	float previousTicks = (float)SDL_GetTicks();

	while (m_gameState != GameState::EXIT) {
		//used for frame time measuring
		_fpsLimiter.begin();

		float newTicks = (float)SDL_GetTicks();
		float frameTime = newTicks - previousTicks;
		previousTicks = newTicks;
		float totalDeltaTime = frameTime / DESIRED_FRAME_TIME;

		m_inputManager.update();
		processInput();

		int i = 0;
		
		while (totalDeltaTime > 0.0f && i < MAX_PHYSICS_STEPS) {
			float deltaTime = std::min(totalDeltaTime, MAX_DELTA_TIME);
			
			/*do movement updates (pass deltaTime for parameters)

			*/
			totalDeltaTime -= deltaTime;
			i++;
		}
		

		_camera.update();
		_hudCamera.update();

		drawGame();		

		//limit fps to MAX_FPS
		_fps = _fpsLimiter.end();	
		
		//Only print 1 time every 10 frames
		static int frameCounter = 0;
		frameCounter++;
		if (frameCounter == 10000) {
			std::cout << _fps << std::endl;
			frameCounter = 0;
		}
	}
}

void MainGame::processInput() {
	SDL_Event evnt;

	const float CAMERA_SPEED = 20;
	const float SCALE_SPEED = 0.1f;

	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type)
		{
		case SDL_QUIT:
			m_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			m_inputManager.setMouseCoords((float)evnt.motion.x, (float)evnt.motion.y);
			break;
		case SDL_KEYDOWN:
			m_inputManager.pressKey(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			m_inputManager.releaseKey(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			m_inputManager.pressKey(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			m_inputManager.releaseKey(evnt.button.button);
			break;

		}
	}

	if (m_inputManager.isKeyDown(SDLK_w)) {
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, CAMERA_SPEED));
	}
	if (m_inputManager.isKeyDown(SDLK_s)) {
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, -CAMERA_SPEED));
	}
	if (m_inputManager.isKeyDown(SDLK_a)) {
		_camera.setPosition(_camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));
	}
	if (m_inputManager.isKeyDown(SDLK_d)) {
		_camera.setPosition(_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
	}
	if (m_inputManager.isKeyDown(SDLK_q)) {
		_camera.setScale(_camera.getScale() + SCALE_SPEED);
	}
	if (m_inputManager.isKeyDown(SDLK_e)) {
		_camera.setScale(_camera.getScale() - SCALE_SPEED);
	}

	if (m_inputManager.isKeyDown(SDL_BUTTON_LEFT)) {
		glm::vec2 mouseCoords = m_inputManager.getMouseCoords();
		mouseCoords = _camera.convertScreenToWorld(mouseCoords);
		std::cout << mouseCoords.x << " " << mouseCoords.y << std::endl;
	}
	
}

void MainGame::drawGame() {
	//set base depth to 1
	glClearDepth(1.0);

	//clears color and buffer depth
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Enable shader
	_colorProgram.use();

	//We are using texture unit 0
	glActiveTexture(GL_TEXTURE0);
	//Gets the uniform location
	GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
	//Tell the shader the texture is in texture unit 0
	glUniform1i(textureLocation, 0);

	//Set Camera matrix
	glm::mat4 cameraMatrix = _camera.getCameraMatrix();
	GLuint pLocation = _colorProgram.getUniformLocation("P");	
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));
	
	_spriteBatch.begin(/*defaulting to sort by texture*/);

	static Snicker::GLTexture texture = Snicker::ResourceManager::getTexture("Textures/Agromus.png");
	glm::vec4 pos(0.0f, 0.0f, 50.0f, 50.0f);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	
	Snicker::ColorRGBA8 color(255, 255, 255, 255);
	
	
	//if (_camera.isBoxInView(/*pos*/ /*dims*/)) {
	//
	//}

	_spriteBatch.draw(pos, uv, texture.id, 0.0f, color);
	

	_spriteBatch.end();

	_spriteBatch.renderBatch();

	drawHud();

	//Unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);

	//Disable shader
	_colorProgram.unuse();

	//Swap buffer and draw everything to screen
	_window.swapBuffer();
}

void MainGame::drawHud() {
	std::string buffer;

	glm::mat4 hudCameraMatrix = _hudCamera.getCameraMatrix();
	GLuint pLocation = _colorProgram.getUniformLocation("P");
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(hudCameraMatrix[0][0]));

	_hudSpriteBatch.begin();

	buffer = "Agromus";

	_spriteFont->draw(_hudSpriteBatch, buffer.c_str(), glm::vec2(0, 0), 
						glm::vec2(1.0), 0.0f, Snicker::ColorRGBA8(255, 255, 255, 255), Snicker::Justification::RIGHT);

	_hudSpriteBatch.end();
	_hudSpriteBatch.renderBatch();
}

