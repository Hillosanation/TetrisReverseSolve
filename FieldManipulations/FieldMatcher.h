#pragma once
#include "../cache/DataCacher.h"
class FieldMatcher {
private:
	int OptimizeLevel = 0;

	PlayFieldFilled NegateField(PlayFieldFilled Field);

	PlayFieldFilled XORFields(PlayFieldFilled a, PlayFieldFilled b);

	//void Test_MatchAll();

	std::vector<PresentPieces> InsertSorted(std::vector<PresentPieces> Solves, int InsertNum);

public:
	//std::vector<PFFSol> MatchAll(PFFSol FSol, const std::vector<std::vector<PlayFieldFilled>>& PossibleFields);

	/*std::vector<PFFSol> MatchAll_2(PFFSol FSol, const DataCacher::TCache& Cache);*/

	std::vector<PFFSol> MatchAll_3(PFFSol FSol, const DataCacher::TPossibleFields& Cache);

	FieldMatcher(const int& OptimizeLvl);
};
