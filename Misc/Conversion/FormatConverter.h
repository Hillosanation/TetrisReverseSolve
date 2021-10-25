#pragma once
#include <string>
#include "./FumenConvert.h"
#include "../CommonDataTypes.h"
#include "../../PieceData/PieceDataInherit.h"

struct TConverter : private FumenConvert { //individual conversions may not be needed, protect them?
private:
		TetrominoDatav2 data;

public:
	//LOOK AWAY YE EYES
	//DO NOT LOOK AT THE SPAGHETTI
	std::string SolToString(const PresentPieces& Sol);
	PresentPieces StringToSol(const std::string& str);
	std::vector<std::string> SolsToStrings(const std::vector<PresentPieces>& Sols);
	std::vector<PresentPieces> StringsToSols(const std::vector<std::string>& strs);

	std::string SolToTetrominos(const PresentPieces& Sol); //change to teto <-> sol, no need for intermediate step
	PresentPieces TetrominosToSol(const std::string& str);
	std::vector<std::string> SolsToTetrominoss(const std::vector<PresentPieces>& Sols);
	std::vector<PresentPieces> TetrominossToSols(const std::vector<std::string>& strs);
	
	std::string PFFToString(const PlayFieldFilled& PFFilled);
	PlayFieldFilled StringToPFF_Hack(const std::string& str, int height);

	StrSol PFFSolToPFFSStrRep(const PFFSol& PFFSol);
	PFFSol PFFStrRepToPFFSol(const StrSol& SSol, int height);
	std::vector<StrSol> PFFSolsToPFFSStrReps(const std::vector<PFFSol>& PFFSols);
	std::vector<PFFSol> PFFStrRepsToPFFSols(const std::vector<StrSol>& SSols, int height);

	FuSol PFFSolToFuSol(const PFFSol& FSol);
	PFFSol FuSolToPFFSol(const FuSol& FSol, int height, int width);
	std::vector<FuSol> PFFSolsToFuSols(const std::vector<PFFSol>& FSols);
	std::vector<PFFSol> FuSolsToPFFSols(const std::vector<FuSol>& FSols, int height, int width);

	FuSol StrSolToFuSol(const StrSol& SSol);
	StrSol FuSolToStrSol(const FuSol& FSol);
	std::vector<FuSol> StrSolsToFuSols(const std::vector<StrSol>& SSols);
	std::vector<StrSol> FuSolsToStrSols(const std::vector<FuSol>& FSols);
};

