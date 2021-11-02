#include "SolutionFilter.h"

std::vector<PFFSol> SolutionFilter::Filter_MinimumSolutions(const std::vector<PFFSol>& PFFSols, int minimum) {
	std::vector<PFFSol> Output;
	for (auto PFFSol : PFFSols) {
		if (PFFSol.Solves.size() < minimum) continue;
		Output.push_back(PFFSol);
	}
	return Output;
}

std::vector<PFFSol> SolutionFilter::Filter_PurePossible(const std::vector<PFFSol>& PFFSols) { //there are some field that cannot be created with only normal pieces

}

std::vector<PFFSol> SolutionFilter::Filter(const std::vector<PFFSol>& PFFSols, SettingsData& Settings) {
	int MinimumNum = std::stoi(Settings.GetValue(SettingsData::SettingsEnum::COUNT_MIN_FILTER));
	auto StartTime = std::chrono::system_clock::now();
	std::vector<PFFSol> Output = PFFSols;
	if (MinimumNum != 1) Output = Filter_MinimumSolutions(Output, MinimumNum);

	auto EndTime = std::chrono::system_clock::now();
	std::cout << "Time taken for filter: " << std::chrono::duration_cast<std::chrono::microseconds>(EndTime - StartTime).count() / 1000.0 << "ms\n";
	return Output;

}
