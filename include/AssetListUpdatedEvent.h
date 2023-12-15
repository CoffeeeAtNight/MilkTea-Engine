#pragma once
#include <memory>

#include <ChaiEvent.h>
#include <Asset.h>
#include <ChaiBusAddress.h>

class AssetListUpdatedEvent : public ChaiEvent {
public:
	std::vector<std::unique_ptr<Asset>>& assetList;

	AssetListUpdatedEvent(std::vector<std::unique_ptr<Asset>>& assets);
};