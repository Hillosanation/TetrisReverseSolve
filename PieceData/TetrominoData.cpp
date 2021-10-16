#include "TetrominoData.h"

//void TetrominoDatav2::SetPieceEnum() override {
//	PieceEnum['I'] = 0;
//	PieceEnum['L'] = 1;
//	PieceEnum['J'] = 2;
//	PieceEnum['O'] = 3;
//	PieceEnum['S'] = 4;
//	PieceEnum['T'] = 5;
//	PieceEnum['Z'] = 6;
//}

void TetrominoDatav2::SetPieces() {
	Pieces = { 'I', 'L', 'J', 'O', 'S', 'T', 'Z' };
}

void TetrominoDatav2::SetPieceFilled() {
	PiecesDataFilled = {
	{	{0,0,0,0,0},
		{0,0,0,0,0},
		{0,1,1,1,1},
		{0,0,0,0,0},
		{0,0,0,0,0},	},

	{	{0,0,1},
		{1,1,1},
		{0,0,0},	},

	{	{1,0,0},
		{1,1,1},
		{0,0,0},	},

	{	{0,1,1},
		{0,1,1},
		{0,0,0},	},

	{	{0,1,1},
		{1,1,0},
		{0,0,0},	},

	{	{0,1,0},
		{1,1,1},
		{0,0,0},	},

	{	{1,1,0},
		{0,1,1},
		{0,0,0},	},
	};
}

TetrominoDatav2::TetrominoDatav2() {
	SetPieces();
	//SetPieceEnum();
	SetPieceFilled();
}