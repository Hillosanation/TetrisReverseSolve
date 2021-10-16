#include "CommandLineExecution.h"

#include <iostream>
#include <fstream>

std::string ExecutePowerShellCommand(std::string Command) {
	std::string PowerShellCommand = "Powershell.exe -Command " + Command;
	std::cout << PowerShellCommand << std::endl;
	FILE* pFile = _popen(PowerShellCommand.c_str(), "rt");
	if (pFile == NULL) exit(1);
	std::ifstream ifs(pFile);
	std::string content((std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));
	return content;
}

std::string ExecuteCMDCommand(std::string Command) {
	std::cout << Command << std::endl;
	FILE* pFile = _popen(Command.c_str(), "rt");
	if (pFile == NULL) exit(1);
	std::ifstream ifs(pFile);
	std::string content((std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));
	return content;
}