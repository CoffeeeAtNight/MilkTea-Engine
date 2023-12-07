#include "AssetManager.h"

AssetManager::AssetManager()
{

}

AssetManager::~AssetManager()
{
}

void AssetManager::importAsset(string pathToAsset)
{
	string assetName = "";
	size_t assetSize = 0;

	Asset asset = Asset::Asset(assetName, assetSize, pathToAsset);

	std::cout << "\n" << asset.getAssetUuid() << "\n";
	std::cout << asset.getFilePath() << "\n";

}