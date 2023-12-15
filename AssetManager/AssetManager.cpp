#include <AssetManager.h>

AssetManager::AssetManager(ChaiBus& eventbus)
	: _bus(eventbus)
{
	_bus.subscribe(
		ChaiBusAddress::IMPORT_ASSET,
		[this](ChaiEvent& event) {
			this->onEvent(event);
		}
	);
	// TODO Check if AssetFolder has Assets, if yes invoke readAssetDirContent()

	// ALSO when importing asset avoid reading ALL assets 
	// but only create the ONE and add to vec of all assets
};

void AssetManager::importAsset()
{
	fs::path filePath = OpenFileDialogToGetFileName();
	fs::path fileName = filePath.filename();

	_mLogger.log("Importing new asset...");

	if (!fs::exists(filePath)) {
		_mLogger.log("File was either deleted or not found");
		return;
	}

	fs::path pathOfFileToImport = fs::path(filePath);

	try
	{
		fs::path importTargetPath = _engineAssetDir;
		importTargetPath /= fileName;

		_mLogger.log("Now copying the file to: " + importTargetPath.string());
		bool fileWasCopied = fs::copy_file(
			pathOfFileToImport,
			importTargetPath,
			boost::filesystem::copy_options::overwrite_existing
		);

		if (fileWasCopied) {
			_mLogger.log("Successfully copied file to destination!");
			readAssetDirContent();

			AssetListUpdatedEvent event(listOfAssets);
			_bus.publish(event);
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

fs::path AssetManager::OpenFileDialogToGetFileName()
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
		fs::path path = fs::path(filePath);
		return path;
	}
	return fs::path();
}
void AssetManager::readAssetDirContent()
{
	try
	{
		if (fs::exists(_engineAssetDir) && fs::is_directory(_engineAssetDir))
		{
			fs::directory_iterator end_iter;
			_mLogger.log("Now iterating through the engine asset dir...");
			for (fs::directory_iterator dir_iter(_engineAssetDir); dir_iter != end_iter; ++dir_iter) {
				if (fs::is_regular_file(dir_iter->status())) {
					_mLogger.log("Creating unique asset pointer and moving it to asset vector...");

					unique_ptr<Asset> uniqueAssetPtr = make_unique<Asset>(
						Asset(
							dir_iter->path().filename().string(),
							fs::file_size(dir_iter->path()),
							dir_iter->path(),
							dir_iter->path().filename().string()
						)
					);

					//_mLogger.log(dir_iter->path().filename().string());
					//std::cout << fs::file_size(dir_iter->path()) << std::endl;
					//_mLogger.log(dir_iter->path().string());

					listOfAssets.push_back(move(uniqueAssetPtr));
				}
			}
		}
		else {
			_mLogger.log("Provided engine asset path does not exist or is not a directory");
		}
	}
	catch (const std::exception& ex)
	{
		_mLogger.log(ex.what());
	}
};