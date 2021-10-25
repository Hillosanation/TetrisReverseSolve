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

struct StrSol { //general struct, encompassing both structs
	std::string Str = "";
	std::vector<PresentPieces> Solves = {};

	StrSol() {};
	StrSol(const FuSol& FSol) : Str(FSol.Fumen), Solves(FSol.Solves) {};
};

struct StrFieldStrPiece { //even more general, pieces are not converted to nested array of integers immediately
	std::string Field;
	std::vector<std::string> Solves = {};
};
