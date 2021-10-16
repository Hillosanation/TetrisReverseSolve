#include "ReverseSolveFunctions.h"

std::string TConverter::SolToString(const PresentPieces& Sol) {
	std::string Output;
	for (auto i : Sol) {
		Output += (char)(i + '0');
	}
	return Output;
}

PresentPieces TConverter::StringToSol(const std::string& str) {
	PresentPieces Output;
	for (char i : str) {
		Output.push_back(i - '0'); //convert char to int
	}
	return Output;
}


std::string TConverter::PFFToString(const PlayFieldFilled& PFFilled) {
	std::string Output;
	for (auto col : PFFilled) {
		for (auto mino : col) {
			Output += mino ? '1' : '0';
		}
	}
	return Output;
}

PlayFieldFilled TConverter::StringToPFF_Hack(const std::string& str, int height) {
	int width = str.length() / height;
	PlayFieldFilled Output;
	Output.reserve(height);
	std::vector<bool> tmpRow;
	tmpRow.reserve(width);
	for (auto mino : str) {
		tmpRow.push_back((bool)(mino - '0'));
		if (tmpRow.size() == width) {
			Output.push_back(tmpRow);
			tmpRow.clear();
			tmpRow.reserve(width);
		}
	}
	return Output;
}

FuSol TConverter::PFFSolToFuSol_Hack(const PFFSol& PFFSol) { //should actually convert into fumen instead of just string
	FuSol Output;
	Output.Fumen = PFFToString(PFFSol.PFFilled);
	Output.Solves = PFFSol.Solves;
	return Output;
}

PFFSol TConverter::FuSolToPFFSol_Hack(const FuSol& FSol, int height) {
	PFFSol Output;
	Output.PFFilled = StringToPFF_Hack(FSol.Fumen, height);
	Output.Solves = FSol.Solves;
	return Output;
}

FuSol PFFSolToFuSol(const PFFSol& FSol) {
	FuSol Output;
	Output.Solves = FSol.Solves;
	//Output.Fumen = 
	return {}; //this function is unuesed
}