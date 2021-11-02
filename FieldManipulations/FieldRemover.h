#pragma once
#include <chrono>
#include <vector>

#include "../cache/DataCacher.h"
#include "FieldMatcher.h"
#include "FieldMerger.h"
class FieldRemover {
	FieldMatcher Matcher;
	FieldMerger Merger;
	DataCacher::TPossibleFields PossibleFields;

	std::vector<PFFSol> Iterate(const std::vector<PFFSol>& FSol);

	/*void Test_ReturnResults();*/

	void RecordToResidue(const std::vector<PFFSol>& PFFSols); //todo

public:
	/*std::vector<PFFSol> ReturnResults(std::vector<PFFSol> FSols, int depth);*/

	std::vector<PFFSol> ReturnResults_2(const std::vector<PFFSol>& PFFSols, int depth);

};
