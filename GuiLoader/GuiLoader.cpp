#include "GuiLoader.h"
#include <ChaiBusAddress.h>

GuiLoader::GuiLoader(sf::RenderWindow* sfWin, ChaiBus& eventbus) : window(sfWin), _bus(eventbus) {};

GuiLoader::GuiLoader(sf::RenderWindow* sfWin, float mWinWidth, float mWinHeight, ChaiBus& eventbus)
	: window(sfWin),
	_bus(eventbus)
{
	_mWindowWidth = mWinWidth;
	_mWindowHeight = mWinHeight;
	GuiLoader::setGuiSize(ImVec2(mWinWidth, mWinHeight + _mGuiOffsetY));
}

GuiLoader::~GuiLoader() {}

ImVec2 GuiLoader::getGuiSize() const
{
	return _mGuiSize;
}

float GuiLoader::getGuiOffsetY() const
{
	return _mGuiOffsetY;
}

void GuiLoader::setGuiSize(ImVec2 newGuiSize)
{
	_mGuiSize = newGuiSize;
}

void GuiLoader::setGuiSize(float newGuiSizeXorY, GUI_SIZE_DIRECTION direc)
{
	if (direc == GUI_SIZE_DIRECTION::X)
		_mGuiSize.x = newGuiSizeXorY;
	else if (direc == GUI_SIZE_DIRECTION::Y)
		_mGuiSize.y = newGuiSizeXorY;
}

void GuiLoader::setOffsetY(float guiOffsetY) {
	_mGuiSize.y += guiOffsetY;
}

void GuiLoader::setOffsetX(float guiOffsetX) {
	_mGuiSize.x += guiOffsetX;
}

void GuiLoader::displayMainGuiWindow() {
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
				onImportButtonClicked("/path/to/asset");
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

void GuiLoader::onImportButtonClicked(const string& filePath)
{
	ChaiEvent event(ChaiBusAddress::IMPORT_ASSET);
	event.message["path"] = filePath;

	_bus.publish(event);
}
