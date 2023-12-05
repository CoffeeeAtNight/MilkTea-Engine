#pragma once
#include <SFML/Graphics.hpp>

#include <imgui.h>

class GuiLoader
{
public:
	GuiLoader(sf::RenderWindow* sfWin, int mWinWidth, int mWinHeight)
	{
		window = sfWin;
		_mWindowWidth = mWinWidth;
		_mWindowHeight = mWinHeight; 
	};

	~GuiLoader();

	void setWindowSize(int mWinWidth, int mWinHeight) 
	{
		_mWindowWidth = mWinWidth;
		_mWindowHeight = mWinHeight;
	}

	ImVec2 getGuiSize() const
	{
		return _mGuiSize;
	}

	void displayMainGuiWindow() const 
	{
		// Start ImGui frame
		ImGui::Begin("mMenu", nullptr, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
				if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */ }
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Edit")) {
				if (ImGui::MenuItem("Undo", "Ctrl+Z")) {
					// Undo action
				}
				if (ImGui::MenuItem("Redo", "Ctrl+Y")) {
					// Redo action
				}
				ImGui::Separator();
				if (ImGui::MenuItem("Copy", "Ctrl+C")) {
					// Copy action
				}
				if (ImGui::MenuItem("Cut", "Ctrl+X")) {
					// Cut action
				}
				if (ImGui::MenuItem("Paste", "Ctrl+V")) {
					// Paste action
				}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Assets")) {
				if (ImGui::MenuItem("Import", "Ctrl+I")) {
					// Undo action
				}
				ImGui::EndMenu();
			}
		}
		ImGui::EndMenuBar();
		ImGui::SetWindowSize(_mGuiSize);
		ImGui::SetWindowCollapsed(false);
		ImGui::SetWindowPos(ImVec2(0, -_mGuiOffsetY));
		ImGui::End();
	}

private:
	sf::RenderWindow* window;
	int _mWindowWidth, _mWindowHeight;
	int _mGuiOffsetY = 20;
	ImVec2 _mGuiSize = ImVec2((float)_mWindowWidth, (float)_mWindowHeight + _mGuiOffsetY);
};


