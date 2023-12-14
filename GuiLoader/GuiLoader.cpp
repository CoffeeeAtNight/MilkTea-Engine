#include "GuiLoader.h"
#include <ChaiBusAddress.h>

GuiLoader::GuiLoader(sf::RenderWindow* sfWin, ChaiBus& eventbus) : window(sfWin), _bus(eventbus) {};

GuiLoader::GuiLoader(sf::RenderWindow* sfWin, float mWinWidth, float mWinHeight, ChaiBus& eventbus)
	: window(sfWin), _bus(eventbus), _mWindowWidth(mWinWidth), _mWindowHeight(mWinHeight)
{
	_mGuiSize = ImVec2(_mWindowWidth, _mWindowHeight + _mGuiOffsetY);

	// Now calculate _assetManagerGuiSize
	_assetManagerGuiSize = ImVec2(_mWindowWidth, (_mWindowHeight / 2.5));
	_assetManagerGuiPos = ImVec2(0, (_mWindowHeight - _assetManagerGuiSize.y));
}


GuiLoader::~GuiLoader() {}

ImVec2 GuiLoader::getGuiSize() const
{
	return _mGuiSize;
}

float GuiLoader::getGuiSizeX() const
{
	return _mGuiSize.x;
}

float GuiLoader::getGuiSizeY() const
{
	return _mGuiSize.y;
}

ImVec2 GuiLoader::getAssetManagerGuiSize() const
{
	return _assetManagerGuiSize;
}

void GuiLoader::setAssetManagerGuiSize(float newGuiSizeXorY, GUI_SIZE_DIRECTION direc)
{
	if (direc == GUI_SIZE_DIRECTION::X)
		_assetManagerGuiSize.x = newGuiSizeXorY;
	else if (direc == GUI_SIZE_DIRECTION::Y)
		_assetManagerGuiSize.y = newGuiSizeXorY;
}

void GuiLoader::setAssetManagerGuiPos(ImVec2 pos)
{
	_assetManagerGuiPos = pos;
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
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

	ImGui::SetNextWindowSize(_mGuiSize);
	ImGui::SetWindowCollapsed(false);
	ImGui::SetNextWindowPos(ImVec2(0, -_mGuiOffsetY));
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

	ImGui::PopStyleVar();

	displayAssetManagerGuiWindow(); // Displaying the AssetManager Window

	ImGui::End();
}

void GuiLoader::displayAssetManagerGuiWindow()
{
	// Set the border size
	ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0.5f); // A thinner border

	// Set the border color to light green (using normalized RGBA values)
	ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.56f, 0.93f, 0.56f, 1.0f));

	ImGui::SetNextWindowPos(_assetManagerGuiPos);
	ImGui::BeginChild("assetManager", getAssetManagerGuiSize(), true);

	// Content for the asset manager goes here

	ImGui::EndChild();

	// Reset styles to default
	ImGui::PopStyleColor();
	ImGui::PopStyleVar();
}

void GuiLoader::onImportButtonClicked(const string& filePath)
{
	ChaiEvent event(ChaiBusAddress::IMPORT_ASSET);
	event.message["path"] = filePath;

	_bus.publish(event);
}
