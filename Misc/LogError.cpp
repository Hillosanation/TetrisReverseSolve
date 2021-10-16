#include "LogError.h"
#include <iostream>

void LogError::Log(std::string reason, std::string origin) {
	std::cout << "Error in " + origin + " | Reason: " + reason << std::endl;
}

LogError::~LogError() {};