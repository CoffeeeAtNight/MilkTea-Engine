#pragma once
#include <string>

#include "ChaiEvent.h"

class ISubscriber
{
public:
	virtual void onEvent(ChaiEvent& event) = 0;
};