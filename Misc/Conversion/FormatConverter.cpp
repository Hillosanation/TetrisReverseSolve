#include "FormatConverter.h"

std::string TConverter::SolToString(const PresentPieces& Sol) {
	std::string Output;
	for (auto i : Sol) {
		Output += (char)(i + '0');
	}
	return Output;
}

std::vector<std::string> TConverter::SolsToStrings(const std::vector<PresentPieces>& Sols) {
	std::vector<std::string> Output;
	for (const auto& Sol : Sols) {
		Output.push_back(SolToString(Sol));
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

std::vector<PresentPieces> TConverter::StringsToSols(const std::vector<std::string>& strs) {
	std::vector<PresentPieces> Output;
	for (const auto& str : strs) {
		Output.push_back(StringToSol(str));
	}
	return Output;
}

std::string TConverter::SolToTetrominos(const PresentPieces& Sol) {
	std::string Output;
	for (const auto& piece : Sol) {
		Output += data.ConvertEnumToPiece(piece);
	}
	return Output;
	
}

PresentPieces TConverter::TetrominosToSol(const std::string& str) {
	PresentPieces Output;
	for (const auto& letter : str) {
		Output.push_back(data.ConvertPieceToEnum(letter));
	}
	return Output;
}

std::vector<std::string> TConverter::SolsToTetrominoss(const std::vector<PresentPieces>& Sols) {
	std::vector<std::string> Output;
	for (const auto& Sol : Sols) {
		Output.push_back(SolToTetrominos(Sol));
	}
	return Output;
}

std::vector<PresentPieces> TConverter::TetrominossToSols(const std::vector<std::string>& strs) {
	std::vector<PresentPieces> Output;
	for (const auto& str : strs) {
		Output.push_back(TetrominosToSol(str));
	}
	return Output;
}


std::string TConverter::PFFToString(const PlayFieldFilled& PFFilled) {
	std::string Output;
	for (auto col : PFFilled) {
		for (auto mino : col) {
			Output += mino ? '1' : '0';
		}
		Output += "/";
	}
	return Output;
}

PlayFieldFilled TConverter::StringToPFF_Hack(const std::string& str) {
	PlayFieldFilled Output;
	std::vector<bool> tmpRow;
	for (const auto letter : str) {
		if (letter == '/') { //delimiter
			Output.push_back(tmpRow);
			tmpRow.clear();
			continue;
		}
		tmpRow.push_back((bool)(letter - '0'));
	}
	return Output;
}

StrSol TConverter::PFFSolToPFFSStrRep(const PFFSol& PFFSol) { //should actually convert into fumen instead of just string
	StrSol Output;
	Output.Str = PFFToString(PFFSol.PFFilled);
	Output.Solves = PFFSol.Solves;
	return Output;
}

std::vector<StrSol> TConverter::PFFSolsToPFFSStrReps(const std::vector<PFFSol>& PFFSols) {
	std::vector<StrSol> Output;
	for (const auto& PFFSol : PFFSols) {
		Output.push_back(PFFSolToPFFSStrRep(PFFSol));
	}
	return Output;
}

PFFSol TConverter::PFFStrRepToPFFSol(const StrSol& SSol) {
	PFFSol Output;
	Output.PFFilled = StringToPFF_Hack(SSol.Str);
	Output.Solves = SSol.Solves;
	return Output;
}

std::vector<PFFSol> TConverter::PFFStrRepsToPFFSols(const std::vector<StrSol>& SSols) {
	std::vector<PFFSol> Output;
	for (const auto& SSol : SSols) {
		Output.push_back(PFFStrRepToPFFSol(SSol));
	}
	return Output;
}

FuSol TConverter::PFFSolToFuSol(const PFFSol& FSol) {
	return { ConvertPFF(FSol.PFFilled), FSol.Solves };
}

std::vector<FuSol> TConverter::PFFSolsToFuSols(const std::vector<PFFSol>& FSols) {
	std::vector<FuSol> Output;
	for (auto PFFSolItem : FSols) {
		Output.push_back(PFFSolToFuSol(PFFSolItem));
	}
	return Output;
}

PFFSol TConverter::FuSolToPFFSol(const FuSol& FSol, int height, int width) {
	return { ConvertFumen(FSol.Fumen, height, width), FSol.Solves };
};


std::vector<PFFSol> TConverter::FuSolsToPFFSols(const std::vector<FuSol>& FSols, int height, int width) {
	std::vector<PFFSol> Output;
	for (auto FSolItem : FSols) {
		Output.push_back(FuSolToPFFSol(FSolItem, height, width));
	}
	return Output;
};

FuSol TConverter::StrSolToFuSol(const StrSol& SSol) { //only use when strsol conatins fumen, not when it is PFFSStrRep
	return { SSol.Str, SSol.Solves };
}

std::vector<FuSol> TConverter::StrSolsToFuSols(const std::vector<StrSol>& SSols) {
	std::vector<FuSol> Output;
	for (const auto& SSol : SSols) {
		Output.push_back(StrSolToFuSol(SSol));
	}
	return Output;
}

StrSol TConverter::FuSolToStrSol(const FuSol& FSol) {
	return FSol; //converted by class (safe conversion)
}

std::vector<StrSol> TConverter::FuSolsToStrSols(const std::vector<FuSol>& FSols) {
	std::vector<StrSol> Output;
	for (const auto& FSol : FSols) {
		Output.push_back(FuSolToStrSol(FSol));
	}
	return Output;
}
