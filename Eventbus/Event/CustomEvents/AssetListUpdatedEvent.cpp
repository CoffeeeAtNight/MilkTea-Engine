#include <AssetListUpdatedEvent.h>

AssetListUpdatedEvent::AssetListUpdatedEvent(std::vector<std::unique_ptr<Asset>>& assets)
	: ChaiEvent(ChaiBusAddress::INIT_ASSET_LIST),
	assetList(assets) {
}
