#include "FieldMatcher.h"
#include <algorithm>
#include <unordered_set>

PlayFieldFilled FieldMatcher::NegateField(PlayFieldFilled Field) {
	for (auto& col : Field) {
		col.flip();
	}
	return Field;
}

PlayFieldFilled FieldMatcher::XORFields(PlayFieldFilled a, PlayFieldFilled b) { //assumes both are the same size
	for (size_t i = 0; i < a.size(); i++) {
		for (size_t j = 0; j < a[0].size(); j++) {
			a[i][j] = a[i][j] xor b[i][j];
		}
	}
	return a;
}

//void FieldMatcher::Test_MatchAll() {
//	PlayFieldFilled field = {
//		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//	};
//	PFFSol FSol = { field, {{}} };
//	DataCacher cache;
//	auto const& tmpField = FSol.PFFilled;
//	std::vector<std::vector<PlayFieldFilled>> PossibleFields = cache.ReturnData(tmpField.size(), tmpField[0].size());
//	auto output = MatchAll(FSol, PossibleFields);
//	for (auto i : output) {
//		std::cout << "Solves: ";
//		for (auto solves : i.Solves) {
//			for (auto piece : solves) {
//				std::cout << piece;
//			}
//			std::cout << " | ";
//		}
//		std::cout << "\n";
//		for (auto col : i.PFFilled) {
//			for (auto mino : col) {
//				std::cout << mino;
//			}
//			std::cout << "\n";
//		}
//		std::cout << "\n";
//	}
//}

std::vector<PresentPieces> FieldMatcher::InsertSorted(std::vector<PresentPieces> Solves, int InsertNum) {
	for (auto& Solve : Solves) {
		auto It = std::lower_bound(Solve.begin(), Solve.end(), InsertNum);
		Solve.insert(It, InsertNum);
	}
	return Solves;
}

//std::vector<PFFSol> FieldMatcher::MatchAll(PFFSol FSol, const std::vector<std::vector<PlayFieldFilled>>& PossibleFields) {
//	std::vector<PFFSol> Output;
//	auto FlippedField = NegateField(FSol.PFFilled);
//	for (size_t i = 0; i < PossibleFields.size(); i++) { //for each piece
//		for (auto PField : PossibleFields[i]) { //improve search by not considering fields that the separate to the original field..?
//			if (!HaveCollision(FlippedField, PField)) { //possible to put field
//				//remove that part from the field by XORing the original field and the current possiblefield
//				//std::cout << i << "\n"; 
//				auto NewField = XORFields(FSol.PFFilled, PField);
//				auto NewSol = InsertSorted(FSol.Solves, i);
//				Output.push_back({ NewField, NewSol });
//			}
//		}
//	}
//	return Output;
//}

//std::vector<PFFSol> FieldMatcher::MatchAll_2(PFFSol FSol, const DataCacher::TCache& Cache) {
//	std::vector<PFFSol> Output;
//	auto FlippedField = NegateField(FSol.PFFilled);
//
//	//accumulate all filled cells into the rows
//	std::vector<int> FlippedRow;
//	FlippedRow.resize(Cache.InvolvedRow.size());
//	for (size_t col = 0; col < FSol.PFFilled.size(); col++) {
//		for (size_t row = 0; row < FSol.PFFilled[col].size(); row++) {
//			FlippedRow[row] += FlippedField[col][row];
//		}
//	}
//	//special case: if there are no filled rows, all rows can be used
//	bool EmptyField = IsFieldEmpty({ FlippedRow }, 0);
//	////if (EmptyField) {
//	////	for (auto& i : FilledRow) {
//	////		i++;
//	////	}
//	////}
//	//std::cout << "FilledRow: ";
//	//for (auto i : FilledRow) {
//	//	std::cout << i;
//	//}
//	//std::cout << "\n";
//	//accumulate the possiblefields that are present in the relavent rows
//	std::unordered_set<int> PFieldIndexes;
//	std::unordered_set<int> RemoveIndexes;
//	//std::vector<int> RemoveIndexes;
//	if (!EmptyField) {
//		for (int i = 0; i < (int)FlippedRow.size(); i++) {
//			//if not filled, dont consider any possible field with that row filled
//			if (FlippedRow[i] == FlippedField.size()) { //cannot add to this row since it is already used, remove the candidates
//				for (auto const& index : Cache.InvolvedRow[i]) {
//					RemoveIndexes.insert(index);
//					//std::cout << index << " + ";
//				}
//				//std::cout << "//";
//				continue;
//			}
//			if (FlippedRow[std::max(i - 1, 0)] + FlippedRow[i] + FlippedRow[std::min((int)FlippedRow.size() - 1, i + 1)] == 0) continue; //if there are no minos to the left, current and right columns, do not add
//			for (auto const& index : Cache.InvolvedRow[i]) { //possible, add the candidates
//				PFieldIndexes.insert(index);
//			}
//		}
//		for (auto const& index : RemoveIndexes) {
//			if (PFieldIndexes.find(index) == PFieldIndexes.end()) continue;
//			PFieldIndexes.erase(index);
//			//std::cout << "!";
//		}
//	}
//	else {
//		for (size_t i = 0; i < Cache.PossibleFields.size(); i++) {
//			PFieldIndexes.insert((int)i); //all must be possible (1st stage)
//		}
//	}
//	//std::cout << PFieldIndexes.size(); //check size
//	//std::cout << ", ";
//
//	for (auto Index : PFieldIndexes) { //improve search by not considering fields that the separate to the original field
//		DataCacher::TCacheItem CacheItem = Cache.PossibleFields[Index];
//		if (!HaveCollision(FlippedField, CacheItem.Field)) { //possible to put field
//			//remove that part from the field by XORing the original field and the current possiblefield
//			//std::cout << i << "\n"; 
//			auto NewField = XORFields(FSol.PFFilled, CacheItem.Field);
//			auto NewSol = InsertSorted(FSol.Solves, CacheItem.piece);
//			Output.push_back({ NewField, NewSol });
//		}
//	}
//	return Output;
//}

void AddPiecesToSet(std::unordered_set<int>& Set, std::vector<int> PieceIndexes) {
	for (const auto& index : PieceIndexes) {
		Set.insert(index);
	}
}

std::vector<PFFSol> FieldMatcher::MatchAll_3(PFFSol FSol, const DataCacher::TPossibleFields& Cache) {
	std::vector<PFFSol> Output;
	auto FlippedField = NegateField(FSol.PFFilled);
	
	std::vector<bool> TouchingFilledColumns;
	TouchingFilledColumns.reserve(FlippedField[0].size());
	{
		std::vector<int> ColTotal;
		for (size_t i = 0; i < FlippedField[0].size(); i++) {
			ColTotal.push_back(0);
		}

		for (size_t col = 0; col < FlippedField.size(); col++) {
			for (size_t row = 0; row < FlippedField[0].size(); row++) {
				ColTotal[row]++;
			}
		}

		for (int i = 0; i < (int)FlippedField[0].size(); i++) {
			TouchingFilledColumns.push_back(ColTotal[std::max(i - 1, 0)] + ColTotal[i] + ColTotal[std::min((int)ColTotal.size() - 1, i + 1)] == 0); //false if total mino of all neibouring is zero
		}
	}
	//if completely empty, that means all cominations are possible, reverse the whole thing
	if (std::find(TouchingFilledColumns.begin(), TouchingFilledColumns.end(), true) == TouchingFilledColumns.end()) {
		TouchingFilledColumns.flip();
	}
	//next optimization level: only include leftmost sides?

	std::unordered_set<int> PFieldIndexes;
	std::unordered_set<int> RemoveIndexes;
	for (size_t row = 0; row < FlippedField[0].size(); row++) {
		//check if column should be searched
		if (!TouchingFilledColumns[row] and OptimizeLevel == 1) continue;

		for (size_t col = 0; col < FlippedField.size(); col++ ){
			if (FlippedField[col][row] == false) { //not used yet, add the possible entries
				AddPiecesToSet(PFieldIndexes, Cache.ContainedMino[col][row]);
			}
			else {
				AddPiecesToSet(RemoveIndexes, Cache.ContainedMino[col][row]);
			}

		}
	}
	for (auto const& index : RemoveIndexes) {
		if (PFieldIndexes.find(index) == PFieldIndexes.end()) continue;
		PFieldIndexes.erase(index);
	}
	
	for (auto Index : PFieldIndexes) { //improve search by not considering fields that the separate to the original field
		//remove that part from the field by XORing the original field and the current possiblefield
		auto NewField = XORFields(FSol.PFFilled, Cache.PFields[Index].Field);
		auto NewSol = InsertSorted(FSol.Solves, Cache.PFields[Index].piece);
		Output.push_back({ NewField, NewSol });
	}

	return Output;
}

FieldMatcher::FieldMatcher(const int& OptimizeLvl) {
	OptimizeLevel = OptimizeLvl;
}
