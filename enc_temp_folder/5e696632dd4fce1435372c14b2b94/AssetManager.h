#pragma once
#include <string>
#include <iostream>
#include <windows.h>
#include <commdlg.h>

#include "Asset.h" 
#include "ISubscriber.h"
#include "ChaiEvent.h"
#include <ChaiBus.h>

using namespace std;


class AssetManager : public ISubscriber
{
	void importAsset(string pathToAsset);
	void onEvent(ChaiEvent& event) override;
	ChaiBus& _bus;

public:
	AssetManager(ChaiBus& eventbus);

	//void showOpenFileDialog();
};


