#include <iostream>

#include "GameEngine.h"
#include "GuiLoader.h"

GameEngine::GameEngine() : window(sf::VideoMode(_mWindowWidth, _mWindowHeight), engineName)
{
	ImGui::SFML::Init(window);
	GameEngine::guiLoader = GuiLoader(&window, _mWindowWidth, _mWindowHeight);
}

GameEngine::~GameEngine()
{
	ImGui::SFML::Shutdown();
}


void GameEngine::run() {
	while (window.isOpen()) {
		processEvents();
		update();
		render();
	}

	ImGui::SFML::Shutdown();
}

void GameEngine::processEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		ImGui::SFML::ProcessEvent(event);

		if (event.type == sf::Event::Closed)
			window.close();

		if (event.type == sf::Event::Resized) {
			sf::Vector2u updatedMainWindowSize = window.getSize();

			_mWindowWidth = updatedMainWindowSize.x;
			_mWindowHeight = updatedMainWindowSize.y;
			_mGuiSize = updatedMainWindowSize;
			_mGuiSize.y += _mGuiOffsetY;
		}
	}
}

void GameEngine::update() {
	ImGui::SFML::Update(window, sf::seconds(1.f / 60.f));
	displayMainGuiWindow();
}

void GameEngine::render() {
	window.clear();
	// Render SFML objects here
	ImGui::SFML::Render(window);
	window.display();
}

void GameEngine::displayMainGuiWindow() const {
	
}