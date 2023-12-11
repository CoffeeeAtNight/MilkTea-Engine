#include "AssetManager.h"
#include <ChaiBusAddress.h>

AssetManager::AssetManager(ChaiBus& eventbus) : _bus(eventbus)
{
	_bus.subscribe(
		ChaiBusAddress::IMPORT_ASSET,
		[this](ChaiEvent& event) {
			this->onEvent(event);
		}
	);
};

void AssetManager::importAsset(string pathToAsset)
{
	string assetName = "";
	size_t assetSize = 0;

	Asset asset = Asset::Asset(assetName, assetSize, pathToAsset);

	std::cout << "\n" << asset.getAssetUuid() << "\n";
	std::cout << asset.getFilePath() << "\n";

}

void AssetManager::onEvent(ChaiEvent& event)
{
	cout << "Event recieved!!" << "\n";
	try
	{
		auto it = event.message.find("path");
		if (it == event.message.end()) {
			throw std::runtime_error("Path could not be found in AssetManager event");
		}

		const std::string& assetPath = it->second;

		if (event.name == ChaiBusAddress::IMPORT_ASSET)
		{
			importAsset(assetPath);
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << "\n";
	}
};