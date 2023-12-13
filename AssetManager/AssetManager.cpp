#include <AssetManager.h>
#include <ChaiBusAddress.h>

AssetManager::AssetManager(ChaiBus& eventbus)
	: _bus(eventbus),
	_assetParentExpDir("C:\\MilkTea-Engine\\Assets")
{
	_bus.subscribe(
		ChaiBusAddress::IMPORT_ASSET,
		[this](ChaiEvent& event) {
			this->onEvent(event);
		}
	);
};

void AssetManager::importAsset()
{
	string assetName = "test.jpg";
	size_t assetSize = 0;

	string filePath = OpenFileDialogToGetFileName();

	Asset asset = Asset::Asset(assetName, assetSize, filePath);
	_mLogger.log("Importing new asset...");
	_mLogger.log(asset.getAssetUuid());
	_mLogger.log(asset.getFilePath());

	if (!fs::exists(filePath)) {
		_mLogger.log("File was either deleted or not found");
		return;
	}

	fs::path pathOfFileToImport = fs::path(filePath);

	try
	{
		_assetParentExpDir /= "images";
		_assetParentExpDir /= assetName;

		_mLogger.log("Now copying the file to: " + _assetParentExpDir.string());
		bool fileWasCopied = fs::copy_file(
			pathOfFileToImport,
			_assetParentExpDir,
			boost::filesystem::copy_options::overwrite_existing
		);

		if (fileWasCopied) {
			_mLogger.log("Successfully copied file to destination!");
		}
		else {
			_mLogger.log("Something wrong happened while trying to copy the file");
		}
	}
	catch (const std::exception& ex)
	{
		_mLogger.log("Error occurred while tring to copy file:");
		_mLogger.log(ex.what());
	}
}

void AssetManager::onEvent(ChaiEvent& event)
{
	_mLogger.log("Event recieved!!");

	try
	{
		if (event.name == ChaiBusAddress::IMPORT_ASSET)
		{
			importAsset();
		}
	}
	catch (const std::exception& e)
	{
		_mLogger.log(e.what());
	}
}

string AssetManager::OpenFileDialogToGetFileName()
{
	OPENFILENAME ofn;       // common dialog box structure
	wchar_t szFile[260]{};  // buffer for file name
	HWND hwnd = NULL;       // owner window
	HANDLE hf = nullptr;    // file handle

	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = szFile;
	// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
	// use the contents of szFile to initialize itself.
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	wchar_t szFilter[] = L"JPG (*.jpg)\0*.jpg\0PNG (*.png)\0*.png\0";
	ofn.lpstrFilter = szFilter;
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Display the Open dialog box.
	if (GetOpenFileName(&ofn) == TRUE) {
		// Convert wide-character string (LPWSTR) to a multi-byte string (std::string)
		int size_needed = WideCharToMultiByte(CP_UTF8, 0, &ofn.lpstrFile[0], -1, NULL, 0, NULL, NULL);
		std::string filePath(size_needed, 0);
		WideCharToMultiByte(CP_UTF8, 0, &ofn.lpstrFile[0], -1, &filePath[0], size_needed, NULL, NULL);
		return filePath;
	}
	return "";
};