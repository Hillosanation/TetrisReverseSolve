#include <iosfwd>
#include <iostream>
#include <vector>

#include "CommonDataTypes.h"
#include "PieceData/PieceDataInherit.h"
#include "StorageDataTransfer.cpp"
#include "Merger.cpp"

std::vector<Piece> PossibleExtensions(PresentPieces Input) {
	std::vector<Piece> Output = {};
	for (int i = 0; i < 7; i++) {
		if (!(Input.empty()) and !(i <= Input.at(0))) break;
		Output.push_back(i);
	}
	return Output;
}

#include "PieceData/TetrominoData.h"

//for these I might want to parallelize them


#include "FieldManipulations/CollisionChecker.h"
#include "DataCacher.cpp"
#include <algorithm>
#include <unordered_map>
class FieldMatcher : protected CollisionChecker {
private:
	PlayFieldFilled NegateField(PlayFieldFilled Field) {
		for (auto& col : Field) {
			for (auto mino : col) {
				mino = !mino;
			}
		}
		return Field;
	}

	PlayFieldFilled XORFields(PlayFieldFilled a, PlayFieldFilled b) { //assumes both are the same size
		for (size_t i = 0; i < a.size(); i++) {
			for (size_t j = 0; j < a[0].size(); j++) {
				a[i][j] = a[i][j] xor b[i][j];
			}
		}
		return a;
	}

	//void Test_MatchAll() {
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

	std::vector<PresentPieces> InsertSorted(std::vector<PresentPieces> Solves, int InsertNum) {
		for (auto& Solve : Solves) {
			auto It = std::lower_bound(Solve.begin(), Solve.end(), InsertNum);
			Solve.insert(It, InsertNum);
		}
		return Solves;
	}

public:
	//std::vector<PFFSol> MatchAll(PFFSol FSol, const std::vector<std::vector<PlayFieldFilled>>& PossibleFields) {
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
	
	std::vector<PFFSol> MatchAll_2(PFFSol FSol, const DataCacher::TCache& Cache) {
		std::vector<PFFSol> Output;
		auto FlippedField = NegateField(FSol.PFFilled);

		//accumulate all filled cells into the rows
		std::vector<int> FlippedRow;
		FlippedRow.resize(Cache.InvolvedRow.size());
		for (size_t col = 0; col < FSol.PFFilled.size(); col++) {
			for (size_t row = 0; row < FSol.PFFilled[col].size(); row++) {
				FlippedRow[row] += FlippedField[col][row];
			}
		}
		//special case: if there are no filled rows, all rows can be used
		bool EmptyField = IsFieldEmpty({ FlippedRow }, 0);
		////if (EmptyField) {
		////	for (auto& i : FilledRow) {
		////		i++;
		////	}
		////}
		//std::cout << "FilledRow: ";
		//for (auto i : FilledRow) {
		//	std::cout << i;
		//}
		//std::cout << "\n";
		//accumulate the possiblefields that are present in the relavent rows
		std::unordered_set<int> PFieldIndexes;
		std::unordered_set<int> RemoveIndexes;
		//std::vector<int> RemoveIndexes;
		if (!EmptyField) {
			for (size_t i = 0; i < FlippedRow.size(); i++) {
				//if not filled, dont consider any possible field with that row filled
				if (FlippedRow[i] == FlippedField.size()) { //cannot add to this row since it is already filled, remove the candidates
					for (auto const& index : Cache.InvolvedRow[i]) { 
						RemoveIndexes.insert(index);
						//std::cout << index << " + ";
					}
					//std::cout << "//";
					continue;
				} 
				for (auto const& index : Cache.InvolvedRow[i]) { //possible, add the candidates
					PFieldIndexes.insert(index);
				}
			}
			for (auto const& index : RemoveIndexes) {
				if (PFieldIndexes.find(index) == PFieldIndexes.end()) continue;
				PFieldIndexes.erase(index); 
				//std::cout << "!";
			}
		}
		else {
			for (size_t i = 0; i < Cache.PossibleFields.size(); i++) {
				PFieldIndexes.insert(i); //all must be possible (1st stage)
			}
		}
		//std::cout << PFieldIndexes.size(); //check size
		//std::cout << ", ";

		for (auto Index : PFieldIndexes) { //improve search by not considering fields that the separate to the original field
			DataCacher::TCacheItem CacheItem = Cache.PossibleFields[Index];
			if (!HaveCollision(FlippedField, CacheItem.Field)) { //possible to put field
				//remove that part from the field by XORing the original field and the current possiblefield
				//std::cout << i << "\n"; 
				auto NewField = XORFields(FSol.PFFilled, CacheItem.Field);
				auto NewSol = InsertSorted(FSol.Solves, CacheItem.piece);
				Output.push_back({ NewField, NewSol });
			}
		}
		return Output;
	}

};

#include <chrono>
class FieldRemover {
	FieldMatcher Matcher;
	FieldMerger Merger;
	DataCacher::TCache PossibleFields;

	std::vector<PFFSol> Iterate(const std::vector<PFFSol>& FSol) {
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
		std::cout << "Time taken for iteration: " << std::chrono::duration_cast<std::chrono::milliseconds>(EndTime - StartTime).count()/1000.0 << "s | Size: " << Output.size() << "\n";
		return Output;
	}

	/*void Test_ReturnResults(){
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

	void RecordToResidue(std::vector<PFFSol> FSol) {

	}

public:
	/*std::vector<PFFSol> ReturnResults(std::vector<PFFSol> FSols, int depth) { //vector input may be unecessary
		DataCacher cache;
		auto const& tmpField = FSols[0].PFFilled;
		PossibleFields = cache.ReturnData(tmpField.size(), tmpField[0].size()); //caches all possible ways to put tetromino in field
		std::vector<PFFSol> Output = FSols;
		for (size_t i = 0; i < depth; i++) {
			Output = Iterate(Output);
		}
		return Output;
	}*/

	std::vector<PFFSol> ReturnResults_2(std::vector<PFFSol> FSols, int depth) { //vector input may be unecessary
		DataCacher cache;
		auto const& tmpField = FSols[0].PFFilled;
		PossibleFields = cache.ReturnData_2(tmpField.size(), tmpField[0].size()); //caches all possible ways to put tetromino in field
		
		std::vector<PFFSol> Output = FSols;
		for (int i = 0; i < depth; i++) {
			Output = Iterate(Output);
		}
		return Output;
	}


};

#include <chrono>
int main() {
	auto StartTime = std::chrono::system_clock::now();
	StorageDataTransfer DataAccess; //I/O test
	FieldMerger Merger;
	TConverter Converter;
	std::vector<FuSol> FuSols = DataAccess.ReadInputFile();
	std::vector<PFFSol> PFFSols;
	PFFSols.reserve(FuSols.size());
	FuSols = Merger.MergeDuplicates(FuSols); //failsafe: get rid of duplicates
	//for (auto i : FuSols) { //print out what was read
	//	std::cout << "Fumen: " << i.Fumen << " | ";
	//	std::cout << "Solves: ";
	//	for (auto choice : i.Solves) {
	//		for (auto piece : choice) {
	//			std::cout << piece;
	//		}
	//		std::cout << " ";
	//	}
	//	std::cout << std::endl;
	//}
	
	for (auto FSolItem : FuSols) {
		auto PFFSolItem = Converter.FuSolToPFFSol_Hack(FSolItem, 4); //a hardcoded 4
		PFFSols.push_back(PFFSolItem);
	}
	FieldRemover remover;
	PFFSols = remover.ReturnResults_2(PFFSols, 4); //does the field extension
	FuSols.clear();
	for (auto PFFSolItem : PFFSols) {
		auto FuSolItem = Converter.PFFSolToFuSol_Hack(PFFSolItem);
		FuSols.push_back(FuSolItem);
	}
	//for (auto i : FuSols) { //print out what was read
	//	std::cout << "Fumen: " << i.Fumen << " | ";
	//	std::cout << "Solves: ";
	//	for (auto choice : i.Solves) {
	//		for (auto piece : choice) {
	//			std::cout << piece;
	//		}
	//		std::cout << " ";
	//	}
	//	std::cout << std::endl;
	//}

	DataAccess.WriteOutputFile(FuSols);

	//###

	/*FieldRemover remover;
	PlayFieldFilled field = {
		{1,1,1,1},
		{1,1,1,1},
		{1,1,1,1},
		{1,1,1,1}
	};
	PFFSol FSol = { field, {{}}};
	auto output = remover.ReturnResults_2({ FSol }, 1);
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
	*/
	auto EndTime = std::chrono::system_clock::now();
	std::cout << "Total time taken: " << std::chrono::duration_cast<std::chrono::seconds>(EndTime - StartTime).count() / 60.0 << "min\n";

	//StorageDataTransfer transfer;
	//transfer.WriteOutputFile();

	//#include <chrono>
	//auto StartTime = std::chrono::system_clock::now();
	//DataCacher cache;
	//auto result = cache.ReturnData(4, 10);
	//auto EndTime = std::chrono::system_clock::now();
	//std::cout << "Time taken for cache: " << std::chrono::duration_cast<std::chrono::microseconds>(EndTime - StartTime).count()/1000.0 << "ms\n";
	
	//auto out = PossibleExtensions({ 2, 5, 3 });
	//for (auto i : out) {
	//	std::cout << i << " ";
	//}
	//std::cout << std::endl;
	//
	return 0;
}