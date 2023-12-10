#pragma once
#include <unordered_map>

#include "Event/Event.h"
#include <functional>

using namespace std;

class ChaiBus
{
	unordered_map<string, list<function<void(const Event&)>>> subscribers;
public:
	ChaiBus();
	~ChaiBus();

	void subscribe(const string& eventName, function<void(const Event& event)>);
	void publish(const Event& event) const;

};
