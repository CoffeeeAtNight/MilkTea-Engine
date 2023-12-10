#pragma once
#include <string>

class ISubscriber
{
public:
	virtual void onEvent(const std::string& event) = 0;
};


