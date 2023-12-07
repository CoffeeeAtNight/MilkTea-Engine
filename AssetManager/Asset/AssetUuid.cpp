#include "AssetUuid.h"

AssetUuid::AssetUuid() {}
AssetUuid::~AssetUuid() {}

long long AssetUuid::buildDaytimeInSeconds()
{
	// Get current time from system clock
	auto currentTimePoint = chrono::system_clock::now();

	// Convert the time point to a duration in seconds
	chrono::seconds secondsSinceEpoch =
		chrono::duration_cast<std::chrono::seconds>(
			currentTimePoint.time_since_epoch()
		);

	// Get the number of seconds as a long long integer
	return secondsSinceEpoch.count();
}

string AssetUuid::generateUuid() {
	string tmpUuid;
	int randNum = 0;
	long long seconds = buildDaytimeInSeconds();

	srand(time(NULL));

	for (size_t i = 0; i < 19; i++)
	{
		if ((i + 1) % 5 != 0) {
			int randNum = rand() % (_upperBoundNum - _lowerBoundNum + 1) + _lowerBoundNum;
			char randChar = static_cast<char>(randNum);
			tmpUuid.append(1, randChar);
		}
		else {
			tmpUuid.append("-");
		}
	}

	return tmpUuid;
}