#pragma once
#include <vector>
#include <algorithm>
#include <chrono>
#include <iosfwd>

#include "../Misc/CommonDataTypes.h"
#include "../PieceData/PieceDataInherit.h"

#include <iostream>

class DataCacher {
public:
	struct TCacheItem {
		PlayFieldFilled Field;
		Piece piece;
	};

	struct TCache {
		std::vector<TCacheItem> PossibleFields;
		std::vector<std::vector<int>> InvolvedRow;
	};

private:
	std::vector<PlayFieldFilled> RemoveExtraLines(std::vector<PlayFieldFilled> FilledFields);

	//void Test_RemoveExtraLines();

	std::vector<std::vector<int>> RecurseInsertLines(int MaxNum, int SelectNum, int LengthLeft);

	std::vector<std::vector<int>> ReturnInsertLines(int MaxNum, int Length);

	//void Test_ReturnInsertLines();

	/*std::vector<std::vector<PlayFieldFilled>> ReturnAllRotations();*/

	std::vector<TCacheItem> ReturnAllRotations_2();

	/*std::vector<PlayFieldFilled> ExpandToNHigh(std::vector<PlayFieldFilled> FilledFields, int MaxHeight);*/

	std::vector<TCacheItem> ExpandToNHigh_2(std::vector<TCacheItem> CacheItems, int MaxHeight);

	//void Test_ReturnData();

	/*std::vector<PlayFieldFilled> ReturnShiftedPossibilities(std::vector<PlayFieldFilled> FilledFields, int MaxWidth);*/

	std::vector<TCacheItem> ReturnShiftedPossibilities_2(std::vector<TCacheItem> CacheItems, int MaxWidth);

	std::vector<std::vector<int>> ReturnInvolvedRow(std::vector<TCacheItem> CacheItems);

public:
	/*std::vector<std::vector<PlayFieldFilled>> ReturnData(int height, int width);*/

	TCache ReturnData_2(int height, int width);
};