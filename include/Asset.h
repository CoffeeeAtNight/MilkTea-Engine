#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <ctime>
#include <vector>
#include <map>
#include <AssetUuid.h>
#include <boost/filesystem/path.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <MatchaLogger.h>

using namespace std;

enum class FileTypes { ImageAsset, AudioAsset, ScriptAsset };

class Asset
{
	MatchaLogger _mLogger = MatchaLogger::MatchaLogger();

public:
	Asset();
	Asset(
		string assetName,
		uintmax_t assetSize,
		boost::filesystem::path filePath,
		string fileNameToDetermineType
	);
	~Asset() = default;

	string getAssetUuid();

	boost::filesystem::path getFilePath();
	void setFilePath(const string& path);

	sf::Texture getTextureInstance();

	FileTypes determineFileType(string nameOfFileWithExtension);

	// Write function to load file content into buffer


private:
	string uuid;
	string name;
	uintmax_t size = 0;
	boost::filesystem::path filePath;
	FileTypes fileType;
	sf::Texture assetIconTexture;
	//time_t dateModified;
	bool loaded = false;
	int referenceCount = 0;
	vector<string> tags;
	map<string, string> metadata;
};

