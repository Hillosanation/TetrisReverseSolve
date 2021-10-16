#pragma once
#include "PieceDataBase.h"

class TetrominoDatav2 : public PieceDataBase { //IMPROVE: just use enums?


	void SetPieces() override;

	void SetPieceFilled() override;

public:
	TetrominoDatav2();

};