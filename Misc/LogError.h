#pragma once
#include <string>

class LogError {
public:
	void Log(std::string reason, std::string origin);

	~LogError();
};