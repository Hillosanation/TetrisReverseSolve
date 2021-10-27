#pragma once
#include <vector>
#include <chrono>
#include <iostream>

#include "../Misc/CommonDataTypes.h"
#include "../SettingsData.h"

class SolutionFilter {
	std::vector<PFFSol> Filter_MinimumSolutions(const std::vector<PFFSol>& PFFSols, int minimum) {
		std::vector<PFFSol> Output;
		for (auto PFFSol : PFFSols) {
			if (PFFSol.Solves.size() < minimum) continue;
			Output.push_back(PFFSol);
		}
		return Output;
	}
public:
	std::vector<PFFSol> Filter(const std::vector<PFFSol>& PFFSols, SettingsData& Settings) {
		auto StartTime = std::chrono::system_clock::now();
		std::vector<PFFSol> Output;
		Output = Filter_MinimumSolutions(PFFSols, std::stoi(Settings.GetValue(SettingsData::SettingsEnum::COUNT_MIN_FILTER)));
		
		auto EndTime = std::chrono::system_clock::now();
		std::cout << "Time taken for filter: " << std::chrono::duration_cast<std::chrono::microseconds>(EndTime - StartTime).count() / 1000.0 << "ms\n";
		return Output;

	}
};