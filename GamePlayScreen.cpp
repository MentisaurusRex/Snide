#include "GamePlayScreen.h"
#include <iostream>
#include <SDL\SDL.h>
#include <SnickerSource\IMainGame.h>
#include <SnickerSource\ResourceManager.h>

GamePlayScreen::GamePlayScreen(Snicker::Window* window) : m_window(window){
}

GamePlayScreen::~GamePlayScreen(){

}

int GamePlayScreen::getNextScreenIndex() const {
	return SCREEN_INDEX_NO_SCREEN;
}

int GamePlayScreen::getPreviousScreenIndex() const {
	return SCREEN_INDEX_NO_SCREEN;
}

void GamePlayScreen::build() {

}

void GamePlayScreen::destroy() {

}

void GamePlayScreen::onEntry() {
	m_worldSpriteBatch.init();
	m_uiSpriteBatch.init();

	//Shader init
	//Compile our color shader
	m_textureProgram.compileShaders("Source/Shaders/colorShading.vert", "Source/Shaders/colorShading.frag");
	m_textureProgram.addAttribute("vertexPosition");
	m_textureProgram.addAttribute("vertexColor");
	m_textureProgram.addAttribute("vertexUV");
	m_textureProgram.linkShaders();

	//Load the Texture
	m_playerTexture = Snicker::ResourceManager::getTexture("Source/Textures/Agromus.png");	
	
	//Init cameras
	m_worldCamera.init(m_window->getScreenWidth(), m_window->getScreenHeight());
	m_uiCamera.init(m_window->getScreenWidth(), m_window->getScreenHeight());

	//m_uiCamera.setPosition(glm::vec2(0,0));

	m_uiCamera.setPosition(glm::vec2((m_window->getScreenWidth() / 2.0), -(m_window->getScreenHeight() / 2)));
	//m_uiCamera.setPosition(glm::vec2((m_window->getScreenWidth() / 2.0) - 280, -(m_window->getScreenHeight() / 2) + 128));

	//Init UI
	m_ui.init(0, 0, 200, 400, "Source/Textures/display.png");

	//Init Map
	m_map.load();
		
	//Load UI
	m_ui.load();

	//Init player
	m_player.init(glm::vec2(30.0f, 30.0f), glm::vec2(56.0f, 56.0f), m_playerTexture, Snicker::ColorRGBA8(255,255,255,255), 5.0f);	

	//TEMPORARY
	_spriteFont = new Snicker::SpriteFont("Source/Fonts/STEREOFI.ttf", 128);

}

void GamePlayScreen::onExit() {

}

void GamePlayScreen::update() {
	m_worldCamera.setPosition(m_player.getPosition());
	m_worldCamera.update();
	m_uiCamera.update();
	checkInput();

	m_player.update(m_game->m_inputManager);
	m_ui.processButtonMouseOver(m_game->m_inputManager);
	
}

void GamePlayScreen::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(32.0f/255.0f, 196.0f/255.0f, 108.0f/255.0f, 1.0f);

	m_textureProgram.use();

	// Upload texture uniform
	GLint textureUniform = m_textureProgram.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);
	glActiveTexture(GL_TEXTURE0);

	// Camera matrix
	glm::mat4 projectionMatrix = m_worldCamera.getCameraMatrix();
	GLint pUniform = m_textureProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	m_worldSpriteBatch.begin(Snicker::GlyphSortType::BACK_TO_FRONT);

	m_player.draw(m_worldSpriteBatch);
	m_map.draw(m_worldSpriteBatch);

	m_worldSpriteBatch.end();
	m_worldSpriteBatch.renderBatch();

	drawUI();

	m_textureProgram.unuse();
}

void GamePlayScreen::drawUI() {

	glm::mat4 hudCameraMatrix = m_uiCamera.getCameraMatrix();
	GLuint pLocation = m_textureProgram.getUniformLocation("P");
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(hudCameraMatrix[0][0]));

	m_uiSpriteBatch.begin();
	
	m_ui.draw(m_uiSpriteBatch);

	std::string buffer;
	buffer = "Agromus";

	//_spriteFont->draw(m_uiSpriteBatch, buffer.c_str(), glm::vec2(0, 0),
	//	glm::vec2(1.0), 0.0f, Snicker::ColorRGBA8(0, 0, 0, 255), Snicker::Justification::RIGHT);

	m_uiSpriteBatch.end();
	m_uiSpriteBatch.renderBatch();
}

void GamePlayScreen::checkInput() {
	SDL_Event evnt;

	while (SDL_PollEvent(&evnt)) {
		m_game->onSDLEvent(evnt);
	}
}
