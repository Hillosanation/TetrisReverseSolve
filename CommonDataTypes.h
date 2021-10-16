#pragma once
#include <vector>
#include <string>

typedef int Piece;
typedef std::vector<Piece> PresentPieces;
typedef std::vector<std::vector<bool>> PlayFieldFilled; //standard is col(row(mino))

struct FuSol { //fumen + solutions (pieces in order)
	std::string Fumen = "";
	std::vector<PresentPieces> Solves = {};
};

struct PFFSol { //playfieldfilled + solutions (pieces in order)
	PlayFieldFilled PFFilled;
	std::vector<PresentPieces> Solves = {};
};