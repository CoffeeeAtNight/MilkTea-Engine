#include <iostream>

#include <GameEngine.h>
#include <GuiLoader.h>

const unsigned int GameEngine::WINDOW_WIDTH = 800;
const unsigned int GameEngine::WINDOW_HEIGHT = 600;
const string GameEngine::ENGINE_NAME = "MilkTea Engine";

GameEngine::GameEngine()
	: window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), ENGINE_NAME),
	chaibus(),
	guiLoader(&window, _mWindowWidth, _mWindowHeight, chaibus),
	assetManager(chaibus)
{
	ImGui::SFML::Init(window);
	_mWindowWidth = window.getSize().x;
	_mWindowHeight = window.getSize().y;

	guiLoader.setGuiSize(ImVec2(_mWindowWidth, _mWindowHeight + guiLoader.getGuiOffsetY()));
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
			guiLoader.setGuiSize(updatedMainWindowSize);

			guiLoader.setOffsetY(
				guiLoader.getGuiOffsetY()
			);
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

void GameEngine::displayMainGuiWindow() {
	// Init main gui window
	guiLoader.displayMainGuiWindow();
}