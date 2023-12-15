#pragma once
#include <string>
#include <iostream>

class MatchaLogger
{
public:
	MatchaLogger() = default;
	~MatchaLogger() = default;

	void log(const std::string&);
};