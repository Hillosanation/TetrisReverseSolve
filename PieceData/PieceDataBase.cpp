#pragma once
#include "..\Misc\CommonFunctions.h"
#include "..\Misc\LogError.h"
#include "PieceDataBase.h"
#include <vector>
#include <functional>

//std::map<char, int> PieceEnum;
//virtual void SetPieceEnum() = 0;

int PieceDataBase::ConvertPieceToEnum(char piece) {
	std::vector<char>::iterator PieceIt = std::find(Pieces.begin(), Pieces.end(), piece);
	if (PieceIt != Pieces.end()) {
		return PieceIt - Pieces.begin();
	}
	else {
		LogError Error;
		Error.Log("Invalid Piece type", "PieceDataBase.ConvertPieceToEnum");
		return -1;
	}
}

int PieceDataBase::PieceBoxSize(int piece) {
	return PiecesDataFilled[piece].size();
}

char PieceDataBase::ConvertEnumToPiece(int Enum) {
	return Pieces[Enum];
}

std::vector<std::vector<bool>> PieceDataBase::PieceFilled(int piece, int state) {
	size_t size = PieceBoxSize(piece);

	PieceData RotatedPiece;

	std::function<bool(int, int)> RotatedDataElement;

	switch (state) {
	case 0:
		RotatedDataElement = [&](int i, int j) {return PiecesDataFilled[piece][i][j]; };
		break;
	case 1:
		RotatedDataElement = [&](int i, int j) {return PiecesDataFilled[piece][size - 1 - j][i]; };
		break;
	case 2:
		RotatedDataElement = [&](int i, int j) {return PiecesDataFilled[piece][size - 1 - i][size - 1 - j]; };
		break;
	case 3:
		RotatedDataElement = [&](int i, int j) {return PiecesDataFilled[piece][j][size - 1 - i]; };
		break;
	}

	ConstructNestedVectorByElements<bool>({ size, size }, [](int i, int j) { return true; }, RotatedDataElement, RotatedDataElement);
	return ConstructNestedVectorByElements<bool>({ size, size }, [](int i, int j) { return true; }, RotatedDataElement, RotatedDataElement);

	/* std::vector<std::vector<bool>> TempField;
		std::vector<bool> TempCol;
		for (int i = 0; i < size; i++)
		{
			TempCol = {};
			TempField = {};
			for (int j = 0; j < size; j++)
			{
				if (RotatedTetromino[i*size+j] == '.') {
					TempCol.emplace_back(false);
				}
				else if (RotatedTetromino[i * size + j] == 'X') {
					TempCol.emplace_back(true);
				}
			}
			TempField.emplace_back(TempCol);
		}
		return TempField; */ //extracted
}
