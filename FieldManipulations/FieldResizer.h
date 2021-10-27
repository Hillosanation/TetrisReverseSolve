#pragma once
#include <vector>

#include "../SettingsData.h"
#include "../Misc/CommonDataTypes.h"

class FieldResizer { //taken from DataCacher and generalized, de-serialized the depreciated functions, made functions work as elements and not whole vector
private:
	//void Test_RemoveExtraLines();

	std::vector<std::vector<int>> RecurseInsertLines(int MaxNum, int SelectNum, int LengthLeft);

	std::vector<std::vector<int>> ReturnInsertLines(int MaxNum, int Length);

	//void Test_ReturnInsertLines();

	std::vector<PlayFieldFilled> ExpandToNHigh(PlayFieldFilled FilledField, int MaxHeight);

	//void Test_ReturnData();

	std::vector<PlayFieldFilled> ReturnShiftedPossibilities(std::vector<PlayFieldFilled> FilledFields, int MaxWidth);

	PlayFieldFilled RemoveExtraLines(PlayFieldFilled FilledField);

	std::vector<PlayFieldFilled> ReturnData(PlayFieldFilled input, int height, int width);
	
	std::vector<PFFSol> ExpandPFF(PFFSol PFFSolItem, int height, int width);

public:
	std::vector<PFFSol> ReducePFFs(std::vector<PFFSol> PFFSols, SettingsData& Settings);

	std::vector<PFFSol> ExpandPFFs(std::vector<PFFSol> PFFSols, SettingsData& Settings);
};

