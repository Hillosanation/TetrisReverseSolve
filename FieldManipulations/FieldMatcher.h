#pragma once
#include "./CollisionChecker.h"
#include "../cache/DataCacher.h"
class FieldMatcher : protected CollisionChecker {
private:
	PlayFieldFilled NegateField(PlayFieldFilled Field);

	PlayFieldFilled XORFields(PlayFieldFilled a, PlayFieldFilled b);

	//void Test_MatchAll();

	std::vector<PresentPieces> InsertSorted(std::vector<PresentPieces> Solves, int InsertNum);

public:
	//std::vector<PFFSol> MatchAll(PFFSol FSol, const std::vector<std::vector<PlayFieldFilled>>& PossibleFields);

	std::vector<PFFSol> MatchAll_2(PFFSol FSol, const DataCacher::TCache& Cache);

};