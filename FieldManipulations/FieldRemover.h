#pragma once
#include <chrono>
#include <vector>

#include "../cache/DataCacher.h"
#include "FieldMatcher.h"
#include "FieldMerger.h"
class FieldRemover {
	FieldMatcher Matcher;
	FieldMerger Merger;
	DataCacher::TCache PossibleFields;

	std::vector<PFFSol> Iterate(const std::vector<PFFSol>& FSol);

	/*void Test_ReturnResults();*/

	void RecordToResidue(std::vector<PFFSol> FSol); //todo

public:
	/*std::vector<PFFSol> ReturnResults(std::vector<PFFSol> FSols, int depth);*/

	std::vector<PFFSol> ReturnResults_2(std::vector<PFFSol> FSols, int depth);

};