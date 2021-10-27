#include <iosfwd>
#include <iostream>
#include <vector>

#include "./Misc/CommonDataTypes.h"
#include "./IO/StorageDataTransfer.h"
#include "./FieldManipulations/FieldMerger.h"
//for these I might want to parallelize them
#include "./FieldManipulations/FieldRemover.h"
#include "./FieldManipulations/FieldResizer.h"
#include "./Filter/SolutionFilter.h"

//std::vector<Piece> PossibleExtensions(PresentPieces Input) { //unuesd
//	std::vector<Piece> Output = {};
//	for (int i = 0; i < 7; i++) {
//		if (!(Input.empty()) and !(i <= Input.at(0))) break;
//		Output.push_back(i);
//	}
//	return Output;
//
//	//auto out = PossibleExtensions({ 2, 5, 3 });
//	//for (auto i : out) {
//	//	std::cout << i << " ";
//	//}
//	//std::cout << std::endl;
//}



#include <chrono>
int main() {
	auto StartTime = std::chrono::system_clock::now(); //I/O test
	
	StorageDataTransfer DataAccess; 

	SettingsData Settings;
	DataAccess.ReadSettings("settings.ini", Settings); //fixed name (otherwise how am i going to find it lol)

	std::vector<StrFieldStrPiece> SFieldSPieces = DataAccess.ReadInputCSV(Settings.GetValue(SettingsData::SettingsEnum::INPUT_FILE_CSV));
	std::vector<PFFSol> PFFSols = DataAccess.DecodeCSVFormat(SFieldSPieces, Settings);

	FieldMerger Merger;
	PFFSols = Merger.MergeDuplicates(PFFSols); //failsafe: get rid of duplicates

	FieldResizer resizer;
	PFFSols = resizer.ExpandPFFs(PFFSols, Settings);
	
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

	FieldRemover remover;
	PFFSols = remover.ReturnResults_2(PFFSols, std::stoi(Settings.GetValue(SettingsData::SettingsEnum::PIECE_DEPTH))); //does the field extension

	PFFSols = resizer.ReducePFFs(PFFSols, Settings);
	PFFSols = Merger.MergeDuplicates(PFFSols);

	SolutionFilter filter;
	PFFSols = filter.Filter(PFFSols, Settings);

	SFieldSPieces = DataAccess.EncodeCSVFormat(PFFSols, Settings);
	DataAccess.WriteOutputCSV(SFieldSPieces, Settings.GetValue(SettingsData::SettingsEnum::OUTPUT_FILE_CSV));

	auto EndTime = std::chrono::system_clock::now();
	std::cout << "Total time taken: " << std::chrono::duration_cast<std::chrono::seconds>(EndTime - StartTime).count() / 60.0 << "min\n";

	std::string x;
	std::cin >> x;
	
	return 0;
}
