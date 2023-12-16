#include "GuiLoader.h"

GuiLoader::GuiLoader(sf::RenderWindow* sfWin, ChaiBus& eventbus) : window(sfWin), _bus(eventbus) {};

GuiLoader::GuiLoader(sf::RenderWindow* sfWin, float mWinWidth, float mWinHeight, ChaiBus& eventbus)
	: window(sfWin), _bus(eventbus), _mWindowWidth(mWinWidth), _mWindowHeight(mWinHeight)
{
	_mGuiSize = ImVec2(_mWindowWidth, _mWindowHeight + _mGuiOffsetY);

	// Now calculate _assetManagerGuiSize
	_assetManagerGuiSize = ImVec2(_mWindowWidth, (_mWindowHeight / 2.5));
	_assetManagerGuiPos = ImVec2(0, (_mWindowHeight - _assetManagerGuiSize.y));

	_bus.subscribe(
		ChaiBusAddress::INIT_ASSET_LIST,
		[this](ChaiEvent& event) {
			auto* assetEvent = dynamic_cast<AssetListUpdatedEvent*>(&event);
			if (assetEvent) {
				this->updateAssetManagerGui(assetEvent->assetList);
			}
		}
	);
}

void GuiLoader::updateAssetManagerGui(const std::vector<std::unique_ptr<Asset>>& assetListRef)
{
	assetListPtr = &assetListRef;
	_mLogger.log("GOT THE MESSAGE IN UPDATE METHOD INSIDE GUILOADER: ");
	std::cout << assetListPtr->at(0)->getFilePath() << std::endl;

	sf::Texture texture = sf::Texture();
	bool is_textureCreated = texture.create(30, 30);
	const string filePath = assetListPtr->at(0)->getFilePath().string();
	if (!texture.loadFromFile(filePath)) {
		// Handle the error, such as logging or displaying a message
		_mLogger.log("Failed to load the image/texture from file: " + filePath);
		return;
	}

	GLuint textureID = texture.getNativeHandle();
	unique_ptr<GLuint> textureIdPtr = make_unique<GLuint>(textureID);
	textureIdList.push_back(move(textureIdPtr));
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
	// Set the background color to a light dark color (adjust the RGBA values as needed)
	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.15f, 0.15f, 0.15f, 1.0f)); // Example: dark gray

	ImGui::SetNextWindowPos(_assetManagerGuiPos);
	ImGui::BeginChild("assetManager", getAssetManagerGuiSize(), true);

	for (size_t i = 0; i < textureIdList.size(); i++)
	{
		ImGui::ImageButton(
			(ImTextureID)textureIdList[i].get(),
			ImVec2(
				(float)300,
				(float)300
			)
		);
	}

	ImGui::EndChild();

	// Reset styles to default
	ImGui::PopStyleColor();
}

void GuiLoader::onImportButtonClicked(const string& filePath)
{
	ChaiEvent event(ChaiBusAddress::IMPORT_ASSET);
	event.message["path"] = filePath;

	_bus.publish(event);
}