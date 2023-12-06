#pragma once
#include <SFML/Graphics.hpp>

#include <imgui.h>

enum class GUI_SIZE_DIRECTION { X, Y };

class GuiLoader
{
public:
	GuiLoader();
	GuiLoader(sf::RenderWindow* sfWin, int mWinWidth, int mWinHeight);

	~GuiLoader();

	ImVec2 getGuiSize() const;
	float getGuiOffsetY() const;

	void setGuiSize(ImVec2 newGuiSize);
	void setGuiSize(float newGuiSizeXorY, GUI_SIZE_DIRECTION direc);
	void setOffsetY(float guiOffsetY);
	void setOffsetX(float guiOffsetX);

	void displayMainGuiWindow() const;

private:
	sf::RenderWindow* window;
	int _mWindowWidth, _mWindowHeight;
	int _mGuiOffsetY = 20;
	ImVec2 _mGuiSize = ImVec2(_mWindowWidth, _mWindowHeight + _mGuiOffsetY);
};

