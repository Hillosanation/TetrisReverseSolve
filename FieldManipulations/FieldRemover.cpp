#include "FieldRemover.h"

std::vector<PFFSol> FieldRemover::Iterate(const std::vector<PFFSol>& FSol) {
	auto StartTime = std::chrono::system_clock::now();
	std::vector<PFFSol> Output;
	std::vector<PFFSol> Result = {};
	for (auto i : FSol) {
		Result = Matcher.MatchAll_2(i, PossibleFields);
		if (Result.size() == 0) {
			//move this field into the residue
			continue;
		}
		Output.insert(Output.end(), Result.begin(), Result.end());
	}
	Output = Merger.MergeDuplicates(Output);
	auto EndTime = std::chrono::system_clock::now();
	std::cout << "Time taken for iteration: " << std::chrono::duration_cast<std::chrono::milliseconds>(EndTime - StartTime).count() / 1000.0 << "s | Size: " << Output.size() << "\n";
	return Output;
}

/*void FieldRemover::Test_ReturnResults(){
	PlayFieldFilled field = {
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	};
	PFFSol FSol = { field, {{}} };
	auto output = ReturnResults({ FSol }, 5);
	for (auto i : output) {
		std::cout << "Solves: ";
		for (auto solves : i.Solves) {
			for (auto piece : solves) {
				std::cout << piece;
			}
			std::cout << " | ";
		}
		std::cout << "\n";
		for (auto col : i.PFFilled) {
			for (auto mino : col) {
				std::cout << mino;
			}
			std::cout << "\n";
		}
		std::cout << "\n";
	}
}*/

void FieldRemover::RecordToResidue(std::vector<PFFSol> FSol) {

}

/*std::vector<PFFSol> FieldRemover::ReturnResults(std::vector<PFFSol> FSols, int depth) { //vector input may be unecessary
	DataCacher cache;
	auto const& tmpField = FSols[0].PFFilled;
	PossibleFields = cache.ReturnData(tmpField.size(), tmpField[0].size()); //caches all possible ways to put tetromino in field
	std::vector<PFFSol> Output = FSols;
	for (size_t i = 0; i < depth; i++) {
		Output = Iterate(Output);
	}
	return Output;
}*/

std::vector<PFFSol> FieldRemover::ReturnResults_2(std::vector<PFFSol> FSols, int depth) { //vector input may be unecessary
	DataCacher cache;
	auto const& tmpField = FSols[0].PFFilled;
	PossibleFields = cache.ReturnData_2((int)tmpField.size(), (int)tmpField[0].size()); //caches all possible ways to put tetromino in field

	std::vector<PFFSol> Output = FSols;
	for (int i = 0; i < depth; i++) {
		Output = Iterate(Output);
	}
	return Output;
}