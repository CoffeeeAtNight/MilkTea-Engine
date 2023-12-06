#include <string>

#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

#include "GuiLoader.h"

using namespace std;

class GameEngine {
public:
	GameEngine();
	~GameEngine();

	void run();
private:
	int _mWindowWidth = 800;
	int _mWindowHeight = 600;
	string engineName = "MilkTea Engine";
	sf::RenderWindow window;

	GuiLoader guiLoader;

	void processEvents();
	void update();
	void render();
	void displayMainGuiWindow() const;
};
