#include "Asset.h"

Asset::Asset()
{
	uuid = AssetUuid().generateUuid();
}

Asset::Asset(string assetName, size_t assetSize, string pathToAsset)
{
	uuid = AssetUuid().generateUuid();
	name = assetName;
	size = assetSize;
	filePath = pathToAsset;
}

Asset::~Asset()
{
}

string Asset::getAssetUuid()
{
	return uuid;
}


string Asset::getFilePath()
{
	return filePath;
}

void Asset::setFilePath(const string& path)
{
	filePath = path;
}

