#pragma once
#include <string>
#include "CommonDataTypes.h"

struct TConverter {
	std::string SolToString(const PresentPieces& Sol);

	PresentPieces StringToSol(const std::string& str);
	
	std::string PFFToString(const PlayFieldFilled& PFFilled);

	PlayFieldFilled StringToPFF_Hack(const std::string& str, int height);

	FuSol PFFSolToFuSol_Hack(const PFFSol& PFFSol);

	PFFSol FuSolToPFFSol_Hack(const FuSol& FSol, int height);

	FuSol PFFSolToFuSol(const PFFSol& FSol);
};

