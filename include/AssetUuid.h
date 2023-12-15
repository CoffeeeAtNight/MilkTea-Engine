#pragma once
#include "string"
#include "vector"
#include <chrono>
#include <iomanip>

#include "UuidFactory.h"

using namespace std;

class AssetUuid : public IUuidFactory
{
public:
	AssetUuid();
	~AssetUuid();

	string generateUuid();
private:
	string _Uuid;

	int _lowerBoundNum = 65;
	int _upperBoundNum = 90;

	long long buildDaytimeInSeconds();
};

