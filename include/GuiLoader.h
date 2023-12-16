
#ifndef GUILOADER
#define GUILOADER
#include <SFML/Graphics.hpp>
#include <imgui-SFML.cpp>
#include <functional>

#include <imgui.h>
#include <ChaiEvent.h>
#include <MatchaLogger.h>
#include <ChaiBus.h>
#include <ChaiBusAddress.h>
#include <AssetListUpdatedEvent.h>
#endif

enum class GUI_SIZE_DIRECTION { X, Y };

class GuiLoader
{
	MatchaLogger _mLogger = MatchaLogger::MatchaLogger();

	sf::RenderWindow* window;
	float _mWindowWidth, _mWindowHeight;
	float _mGuiOffsetY = 20;
	ImVec2 _mGuiSize = ImVec2(_mWindowWidth, _mWindowHeight + _mGuiOffsetY);

	ImVec2 _assetManagerGuiSize = ImVec2(_mWindowWidth, _mWindowHeight / 3);
	ImVec2 _assetManagerGuiPos = ImVec2(0, _mWindowHeight - _assetManagerGuiSize.y);

	const std::vector<std::unique_ptr<Asset>>* assetListPtr = nullptr;

	std::vector<std::unique_ptr<GLuint>> textureIdList;

	ChaiBus& _bus;


public:
	GuiLoader(sf::RenderWindow* sfWin, ChaiBus& eventbus);
	GuiLoader(
		sf::RenderWindow* sfWin,
		float mWinWidth,
		float mWinHeight,
		ChaiBus& eventbus
	);

	~GuiLoader();

	ImVec2 getGuiSize() const;
	float getGuiSizeX() const;
	float getGuiSizeY() const;
	float getGuiOffsetY() const;

	void setGuiSize(ImVec2 newGuiSize);
	void setGuiSize(float newGuiSizeXorY, GUI_SIZE_DIRECTION direc);
	void setOffsetY(float guiOffsetY);
	void setOffsetX(float guiOffsetX);

	ImVec2 getAssetManagerGuiSize() const;

	void setAssetManagerGuiSize(float newGuiSizeXorY, GUI_SIZE_DIRECTION direc);
	void setAssetManagerGuiPos(ImVec2 pos);

	void displayMainGuiWindow();
	void displayAssetManagerGuiWindow();
	void onImportButtonClicked(const std::string& filePath);

	void updateAssetManagerGui(const std::vector<std::unique_ptr<Asset>>& assets);
};