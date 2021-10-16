#pragma once
#include <vector>

class PieceDataBase {
protected:
	typedef std::vector<std::vector<bool>> PieceData;

	std::vector<PieceData> PiecesDataFilled;

	std::vector<char> Pieces;
	
	virtual void SetPieces() = 0;
	virtual void SetPieceFilled() = 0;

public:
	int PieceBoxSize(int piece);

	char ConvertEnumToPiece(int Enum);

	std::vector<std::vector<bool>> PieceFilled(int piece, int state);
};