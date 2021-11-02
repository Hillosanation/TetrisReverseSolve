#pragma once
#include <vector>
#include <chrono>
#include <iostream>

#include "../Misc/CommonDataTypes.h"
#include "../SettingsData.h"

class SolutionFilter {
	std::vector<PFFSol> Filter_MinimumSolutions(const std::vector<PFFSol>& PFFSols, int minimum);

	std::vector<PFFSol> Filter_PurePossible(const std::vector<PFFSol>& PFFSols);

public:
	std::vector<PFFSol> Filter(const std::vector<PFFSol>& PFFSols, SettingsData& Settings);
};
