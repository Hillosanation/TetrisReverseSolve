#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <chrono>

#include "../SettingsData.h"
#include "./StorageDataTransfer.h"
#include "../Misc/CommonFunctions.h"

void StorageDataTransfer::OutputPresentPiece(PresentPieces PPiece, std::ofstream& os) {
	for (auto Piece : PPiece) {
		os << Piece;
	}
}

//void StorageDataTransfer::TestIO() {
//	StorageDataTransfer DataAccess; //I/O test
//	Merger merge;
//	std::vector<FuSol> FileInput = DataAccess.ReadInputFile();
//	/*for (auto i : FileInput) { //print out what was read
//		std::cout << "Fumen: " << i.Fumen << " | ";
//		std::cout << "Solves: ";
//		for (auto j : i.Solves) {
//			std::cout << j << " ";
//		}
//		std::cout << std::endl;
//	}*/
//	FileInput = merge.MergeDuplicates(FileInput);
//	DataAccess.WriteOutputFile(FileInput);
//}

//std::vector<StrSol> StorageDataTransfer::ReadInputCSV(std::string InputName) { //parses stored csv //this version assumes solutions come in the form of numbers
//	std::ifstream fs;
//	fs.open("../" + InputName, std::fstream::in);
//	std::string line;
//	bool FirstLine = true;
//
//	std::vector<StrSol> tmpStrSols;
//
//	while (std::getline(fs, line)) { //reads a line from fs
//		if (FirstLine) { //has column names, ignore them
//			FirstLine = !FirstLine;
//			continue;
//		}
//		StrSol tmpStrSol;
//		std::stringstream linestream(line); //a stream but data is like a string
//		std::string value;
//		bool FieldPart = true;
//		while (std::getline(linestream, value, ',')) { //reads a value from linestream
//			if (FieldPart) {
//				tmpStrSol.Str = value;
//				FieldPart = !FieldPart;
//				continue;
//			}
//			if (value == "") continue; //failsafe: annoying artifacts when editing csv from excel
//			PresentPieces tmpSol = StringToSol(value);
//			tmpStrSol.Solves.push_back(tmpSol);
//			//std::cout << value << " ";
//		}
//		if (tmpStrSol.Solves.size() == 0) { //no previous entries, add empty entry
//			tmpStrSol.Solves.push_back({});
//		}
//		tmpStrSols.push_back(tmpStrSol);
//		//std::cout << std::endl;
//	};
//	fs.close();
//
//	return tmpStrSols;
//}

std::vector<StrFieldStrPiece> StorageDataTransfer::ReadInputCSV(std::string InputName) { //parses stored csv 
	std::ifstream fs;
	fs.open("./" + InputName, std::fstream::in);
	std::string line;
	bool FirstLine = true;

	std::vector<StrFieldStrPiece> tmpSFieldSPieces;

	while (std::getline(fs, line)) { //reads a line from fs
		if (FirstLine) { //has column names, ignore them
			FirstLine = !FirstLine;
			continue;
		}
		StrFieldStrPiece tmpSFieldSPiece;
		std::stringstream linestream(line); //a stream but data is like a string
		std::string value;
		bool FieldPart = true;
		while (std::getline(linestream, value, ',')) { //reads a value from linestream
			if (FieldPart) {
				tmpSFieldSPiece.Field = value;
				FieldPart = !FieldPart;
				continue;
			}
			if (value == "") continue; //failsafe: annoying artifacts when editing csv from excel
			tmpSFieldSPiece.Solves.push_back(value);
			//std::cout << value << " ";
		}
		if (tmpSFieldSPiece.Solves.size() == 0) { //no previous entries, add empty entry
			tmpSFieldSPiece.Solves.push_back("");
		}
		tmpSFieldSPieces.push_back(tmpSFieldSPiece);
		//std::cout << std::endl;
	};
	fs.close();

	return tmpSFieldSPieces;
}

//void StorageDataTransfer::WriteOutputCSV(std::vector<StrSol> SSols, std::string OutputName) { //converts into the 
//	std::ofstream os;
//	os.open("../" + OutputName, std::fstream::trunc);
//	if (!os) { //doesn't exist, make new
//		std::ofstream file("../" + OutputName);
//		os.open("../" + OutputName, std::fstream::trunc);
//	}
//	os << "fumen code, solution pieces" << std::endl;
//	for (auto i : SSols) {
//		os << i.Str << ",";
//		for (size_t j = 0; j < i.Solves.size(); j++) {
//			if (j == i.Solves.size() - 1) { //last value
//				OutputPresentPiece(i.Solves.at(j), os);
//				break;
//			}
//			OutputPresentPiece(i.Solves.at(j), os);
//			os << ",";
//		}
//		os << std::endl;
//	}
//}

void StorageDataTransfer::WriteOutputCSV(std::vector<StrFieldStrPiece> SFieldSPieces, std::string OutputName) {
	std::ofstream os;
	std::string path = "./" + OutputName;
	os.open(path, std::fstream::trunc);
	if (!os) { //doesn't exist, make new
		std::ofstream file(path);
		os.open(path, std::fstream::trunc);
	}
	os << "fumen code, solution pieces" << std::endl;
	for (auto SFieldSPiece : SFieldSPieces) {
		std::string buffer;
		buffer += SFieldSPiece.Field + ",";
		for (auto Sol : SFieldSPiece.Solves) {
			buffer += Sol + ",";
		}
		buffer.pop_back(); //remove last ,
		os << buffer << "\n";
	}
}

void StorageDataTransfer::ReadSettings(const std::string& SettingsName, SettingsData& Settings) {
	std::ifstream fs;
	fs.open("./" + SettingsName, std::fstream::in);
	std::string line;
	int enumIndex = 0;

	while (std::getline(fs, line) and enumIndex < Settings.SearchData.size()) { //reads a line from fs
		SettingsData::SearchItem MatchItem = Settings.SearchData[enumIndex];
		auto ItToSearch = line.find("=");

		if (ItToSearch == std::string::npos) continue; //couldn't find the setting in this line, skipping
		ItToSearch += 1; //move iterator to the value part of line

		std::string ValueInputted(line.begin() + ItToSearch, line.end());
		if (!(IsInteger(ValueInputted) xor IsInteger(MatchItem.Value))) { //if either or both are integers
			Settings.SearchData[enumIndex].Value = ValueInputted;
		}
		enumIndex++;
	};
	fs.close();
}

std::vector<PFFSol> StorageDataTransfer::DecodeCSVFormat(std::vector<StrFieldStrPiece> SFieldSPieces, SettingsData& Settings) {
	auto StartTime = std::chrono::system_clock::now();
	std::vector<StrSol> StrSols;

	//converts string input -> sol
	if (std::stoi(Settings.GetValue(SettingsData::SettingsEnum::INPUT_FORMAT)) / 2 == 0) { //index of pieces 
		for (const auto& SFieldSPiece : SFieldSPieces) {
			StrSol tmp;
			tmp.Str = SFieldSPiece.Field;
			tmp.Solves = StringsToSols(SFieldSPiece.Solves);
			StrSols.push_back(tmp);
		}
	}
	else { //tetrominos
		for (const auto& SFieldSPiece : SFieldSPieces) {
			StrSol tmp;
			tmp.Str = SFieldSPiece.Field;
			tmp.Solves = TetrominossToSols(SFieldSPiece.Solves);
			StrSols.push_back(tmp);
		}
	}

	std::vector<PFFSol> PFFSols;
	PFFSols.reserve(StrSols.size());

	//converts string input -> PFF
	if (std::stoi(Settings.GetValue(SettingsData::SettingsEnum::INPUT_FORMAT)) % 2 == 0) { //PFF String Representation
		int height = std::stoi(Settings.GetValue(SettingsData::SettingsEnum::FIELD_HEIGHT));
		PFFSols = PFFStrRepsToPFFSols(StrSols, height);
	}
	else { //Fumen
		int height = std::stoi(Settings.GetValue(SettingsData::SettingsEnum::FIELD_HEIGHT));
		int width = std::stoi(Settings.GetValue(SettingsData::SettingsEnum::FIELD_WIDTH));
		std::vector<FuSol> tmp = StrSolsToFuSols(StrSols);
		PFFSols = FuSolsToPFFSols(tmp, height, width);
	}
	auto EndTime = std::chrono::system_clock::now();
	std::cout << "Time taken for decoding: " << std::chrono::duration_cast<std::chrono::microseconds>(EndTime - StartTime).count() / 1000.0 << "ms\n";
	return PFFSols;
}

std::vector<StrFieldStrPiece> StorageDataTransfer::EncodeCSVFormat(std::vector<PFFSol> PFFSols, SettingsData& Settings) {
	auto StartTime = std::chrono::system_clock::now();
	std::vector<StrFieldStrPiece> SFieldSPieces;
	std::vector<StrSol> StrSols;

	//make format of field
	if (std::stoi(Settings.GetValue(SettingsData::SettingsEnum::OUTPUT_FORMAT)) % 2 == 0) { //PFF String Representation
		StrSols = PFFSolsToPFFSStrReps(PFFSols);
	}
	else { //Fumen
		std::vector<FuSol> tmp = PFFSolsToFuSols(PFFSols);
		StrSols = FuSolsToStrSols(tmp);
	}

	//make format of solutions
	SFieldSPieces.clear();
	if (std::stoi(Settings.GetValue(SettingsData::SettingsEnum::OUTPUT_FORMAT)) / 2 == 0) { //index of pieces
		for (const auto& StrSolItem : StrSols) {
			StrFieldStrPiece tmp;
			tmp.Field = StrSolItem.Str;
			tmp.Solves = SolsToStrings(StrSolItem.Solves);
			SFieldSPieces.push_back(tmp);
		}
	}
	else { //tetrominos
		for (const auto& StrSolItem : StrSols) {
			StrFieldStrPiece tmp;
			tmp.Field = StrSolItem.Str;
			tmp.Solves = SolsToTetrominoss(StrSolItem.Solves);
			SFieldSPieces.push_back(tmp);
		}
	}

	auto EndTime = std::chrono::system_clock::now();
	std::cout << "Time taken for encoding: " << std::chrono::duration_cast<std::chrono::microseconds>(EndTime - StartTime).count() / 1000.0 << "ms\n";
	return SFieldSPieces;
}
