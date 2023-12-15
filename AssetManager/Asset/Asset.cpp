#include "Asset.h"

Asset::Asset()
{
	uuid = AssetUuid().generateUuid();
}

Asset::Asset(
	string assetName,
	uintmax_t assetSize,
	boost::filesystem::path pathToAsset,
	string fileNameToDetermineType
) {
	uuid = AssetUuid().generateUuid();
	name = assetName;
	size = assetSize;
	filePath = pathToAsset;
	fileType = determineFileType(fileNameToDetermineType);
}

string Asset::getAssetUuid()
{
	return uuid;
}


boost::filesystem::path Asset::getFilePath()
{
	return filePath;
}

void Asset::setFilePath(const string& path)
{
	filePath = path;
}

FileTypes Asset::determineFileType(string fileName)
{
	size_t posOfDot = fileName.find_first_of(".") + 1;
	string typeOfFile = fileName.substr(posOfDot);

	if (typeOfFile == "jpg" || typeOfFile == "png")
	{
		return FileTypes::ImageAsset();
	}
	// TODO INCLUDE MORE DATA TYPES
}

