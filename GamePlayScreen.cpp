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
	m_spriteBatch.init();

	//Shader init
	//Compile our color shader
	m_textureProgram.compileShaders("Source/Shaders/colorShading.vert", "Source/Shaders/colorShading.frag");
	m_textureProgram.addAttribute("vertexPosition");
	m_textureProgram.addAttribute("vertexColor");
	m_textureProgram.addAttribute("vertexUV");
	m_textureProgram.linkShaders();

	//Load the Texture
	m_playerTexture = Snicker::ResourceManager::getTexture("Source/Textures/Agromus.png");	
	
	//Init camera
	m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight());

	//Init Map
	m_map.load();

	//Init player
	m_player.init(glm::vec2(30.0f, 30.0f), glm::vec2(56.0f, 56.0f), m_playerTexture, Snicker::ColorRGBA8(255,255,255,255), 5.0f);	

}

void GamePlayScreen::onExit() {

}

void GamePlayScreen::update() {
	m_camera.update();
	checkInput();

	m_player.update(m_game->m_inputManager);
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
	glm::mat4 projectionMatrix = m_camera.getCameraMatrix();
	GLint pUniform = m_textureProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	m_spriteBatch.begin(Snicker::GlyphSortType::BACK_TO_FRONT);

	m_player.draw(m_spriteBatch);
	m_map.draw(m_spriteBatch);

	m_spriteBatch.end();
	m_spriteBatch.renderBatch();
	m_textureProgram.unuse();
}

void GamePlayScreen::checkInput() {
	SDL_Event evnt;

	while (SDL_PollEvent(&evnt)) {
		m_game->onSDLEvent(evnt);
	}
}
