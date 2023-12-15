#ifndef GAMEENGINE
#define GAMEENGINE
#include <string>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

#include <GuiLoader.h>
#include <AssetManager.h>
#include <ChaiBus.h>
#endif

using namespace std;

class GameEngine {
	ChaiBus chaibus;
	GuiLoader guiLoader;
	AssetManager assetManager;

	sf::RenderWindow window;
	float _mWindowWidth = 800;
	float _mWindowHeight = 600;

	void processEvents();
	void update();
	void render();
	void displayMainGuiWindow();

public:
	static const unsigned int WINDOW_WIDTH;
	static const unsigned int WINDOW_HEIGHT;
	static const string ENGINE_NAME;

	GameEngine();
	~GameEngine();

	void run();

};
