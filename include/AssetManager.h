#pragma once
#include <string>
#include <iostream>
#include <windows.h>
#include <commdlg.h>
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <thread>

#include <Asset.h>
#include <ISubscriber.h>
#include <ChaiEvent.h>
#include <ChaiBus.h>
#include <MatchaLogger.h>
#include <ChaiBusAddress.h>
#include <AssetListUpdatedEvent.h>

namespace fs = boost::filesystem;
namespace range = boost::range;


class AssetManager : public ISubscriber
{
	MatchaLogger _mLogger = MatchaLogger::MatchaLogger();

	fs::path _engineAssetDir = "C:\\MilkTea-Engine\\Assets";

	void importAsset();
	void onEvent(ChaiEvent& event) override;
	fs::path OpenFileDialogToGetFileName();
	void readAssetDirContent();
	ChaiBus& _bus;

public:
	AssetManager(ChaiBus& eventbus);
	vector<unique_ptr<Asset>> listOfAssets = vector<unique_ptr<Asset>>();

	// Implement logic to add assets to list and show thumbnail in asset manager ui

	// Write method to generate down scaled thumbnail of img
};


