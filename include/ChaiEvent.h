#pragma once
#include <string>
#include <unordered_map>

class ChaiEvent
{
public:
	virtual ~ChaiEvent() = default;
	std::string name;
	std::unordered_map<std::string, std::string> message;
	ChaiEvent(const std::string& eventName) : name(eventName) {}
};