#include "Chaibus.h"

ChaiBus::ChaiBus()
{
}

ChaiBus::~ChaiBus()
{
}


void ChaiBus::subscribe(const string& eventName, function<void(const Event& event)> callback)
{
	subscribers[eventName].push_back(callback);
}

void ChaiBus::publish(const Event& event) const
{
	auto& subs = subscribers[event.name];

	for (auto& sub : subs)
	{
		sub();
	}

}
