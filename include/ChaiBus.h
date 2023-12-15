#pragma once
#include <unordered_map>
#include <iostream>

#include "ChaiEvent.h"
#include <functional>

using namespace std;

class ChaiBus
{
	unordered_map<string, list<function<void(ChaiEvent&)>>> subscribers;
public:
	ChaiBus() = default;
	~ChaiBus() = default;

	void subscribe(const string& eventName, function<void(ChaiEvent& event)> callback);
	void publish(ChaiEvent& event);
};
