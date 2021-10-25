#include "FumenConvert.h"
#include <iostream>

FumenConvert::TBoard FumenConvert::MakePartialBoardRepresentation(const TPFFilledLine& PFFLine) {
	TBoard Output;
	bool SegmentBool = false;
	TPFFilledLine::const_iterator it = std::find(PFFLine.begin(), PFFLine.end(), SegmentBool);
	if (it != PFFLine.begin()) { //the first mino is not false
		Output.push_back({ 8,(int)(it - PFFLine.begin()) });
	}
	while (it != PFFLine.end()) {
		SegmentBool = !SegmentBool;
		TPFFilledLine::const_iterator newIt = std::find(it, PFFLine.end(), SegmentBool); //find start of the next segment
		TBoardInfo tmp(!SegmentBool * 8, (int)(newIt - it));
		Output.emplace_back(tmp); //check end iterator edge case works here
		it = newIt;
	}
	return Output;
}

FumenConvert::TBoard FumenConvert::MakeBoardRepresentation(const PlayFieldFilled& PFFilled) {
	TBoard Output = {};
	int height = (int)PFFilled.size();
	std::vector<int> prefix = { 0, (23 - height) * 10 }; //prepending omitted empty field
	std::vector<bool> PFFLine = {};
	for (const auto& col : PFFilled) {
		PFFLine.insert(PFFLine.end(), col.begin(), col.end());
	}
	Output = MakePartialBoardRepresentation(PFFLine);
	if (Output.at(0).BlockNum == 0+8) { //merge the blanks together
		prefix.at(1) += Output.at(0).Consecutive + 1; //offset of storage
		Output.erase(Output.begin());
	}
	TBoardInfo tmp(prefix[0], prefix[1]);
	Output.emplace(Output.begin(), tmp); //check if ctor works
	std::vector<int> suffix = { 0, 10 };
	if (Output.at(Output.size()-1).BlockNum == 0 + 8) { //merge the blanks together
		suffix.at(1) += Output.at(Output.size() - 1).Consecutive + 1; //offset of storage
		Output.erase(Output.end() - 1);
	}
	TBoardInfo tmp2(suffix[0], suffix[1]);
	Output.emplace_back(tmp2);
	return Output;
}

PlayFieldFilled FumenConvert::ExpandToFullWidth(PlayFieldFilled PFFilled) {
	while (PFFilled[0].size() != FieldWidth) {
		for (auto& col : PFFilled) {
			col.push_back(1);
		}
	}
	return PFFilled;
}

std::vector<int> FumenConvert::ConvertTo64(TBoard Board) {
	std::vector<int> Output = {};
	for (const auto& item : Board) {
		int total = 240 * item.BlockNum + item.Consecutive;
		std::vector<int> tmp = {total % 64, total / 64};
		Output.insert(Output.end(), tmp.begin(), tmp.end());
	}
	return Output;
}

std::string FumenConvert::IntVecToFuString(std::vector<int> IntVec) {
	std::string Output;
	for (const auto& item : IntVec) {
		Output += FumenString[item]; //strings are zero-indexed, huh.
	}
	return Output;
}

void FumenConvert::test_FieldToFumen() {
	FumenConvert FuConv;
	PlayFieldFilled field = {
		{0,0,0,0,0,1,1},
		{0,0,0,0,1,1,1},
		{0,0,0,1,1,1,1},
		{0,0,0,0,1,1,1},
	};
	std::cout << FuConv.ConvertPFF(field);
}

std::string FumenConvert::ConvertPFF(PlayFieldFilled PFFilled) {
	std::string prefix = "v115@";
	std::string suffix = "AgH";
	TPFFilledLine PFFLine;
	TBoard BoardRep = MakeBoardRepresentation(ExpandToFullWidth(PFFilled));
	std::vector<int> IntVecRep = ConvertTo64(BoardRep);
	return prefix + IntVecToFuString(IntVecRep) + suffix;
}

std::vector<int> FumenConvert::StringToIntVec(std::string Fumen) {
	std::vector<int> Output;
	for (const auto& item : Fumen) { 
		size_t index = FumenString.find(item);
		Output.push_back((int)index);
	}
	return Output;
}

FumenConvert::TBoard FumenConvert::IntVecToBoard(std::vector<int> IntVecRep) {
	TBoard Output;
	for (size_t i = 0; i < 3; i++) {
		IntVecRep.pop_back(); //remove mino flag
	}
	if (IntVecRep.size() % 2 == 1) return {}; //error, the int vec should not be odd length.
	for (size_t i = 0; i < IntVecRep.size() / 2; i++) {
		int total = IntVecRep.at(2 * i) + IntVecRep.at(2 * i + 1) * 64;
		Output.push_back({total / 240 - 8, total % 240 + 1});
	}
	return Output;
}

PlayFieldFilled FumenConvert::BoardToPFF(FumenConvert::TBoard BoardRep) {
	PlayFieldFilled Output;
	std::vector<bool> PFFLine;
	for (auto const BoardItem : BoardRep) {
		for (int i = 0; i < BoardItem.Consecutive + 1; i++) {
			PFFLine.push_back((bool)(BoardItem.BlockNum - 8));
		}
	}
	if (PFFLine.size() % 10 != 0) return {}; //error
	for (size_t i = 0; i < PFFLine.size() / 10; i++) {
		std::vector<bool> tmp(PFFLine.begin() + 10 * i, PFFLine.begin() + 10 * i + 10);
		Output.push_back(tmp);
	}
	return Output;
}

PlayFieldFilled FumenConvert::RemoveExtraRows(PlayFieldFilled FilledField) { //from DataCacher, made to be contiguous removal
//DebugPrintVector is from DebugFunctions.h
	if (FilledField.size() == 0) return {{ false }};
	PlayFieldFilled Output;
	{
		PlayFieldFilled tmp = FilledField;
		std::vector<int> EmptyRow = {};
		for (size_t i = 0; i < FilledField.size(); i++) { //check if row is empty
			auto row = FilledField[i];
			auto it = std::find(row.begin(), row.end(), true);
			if (it == row.end()) {
				EmptyRow.push_back((int)i); //no filled mino in row, mark as empty
			}
		}
		std::vector<int> EmptyCol = {};
		for (size_t row = 0; row < FilledField[0].size(); row++) { //check if col is empty
			bool Empty = true;
			for (size_t col = 0; col < FilledField.size(); col++) {
				if (FilledField[col][row]) { //filled, cannot remove
					Empty = false;
					break;
				}
			}
			if (Empty) {
				EmptyCol.push_back((int)row);
			}
		}
		//remove from back to front, to avoid shifting index issues
		std::reverse(EmptyRow.begin(), EmptyRow.end());
		std::reverse(EmptyCol.begin(), EmptyCol.end());
		//DebugPrintVector(EmptyRow);
		//DebugPrintVector(EmptyCol);
		//DebugPrintPlayField(tmp);
		//for (auto index : EmptyRow) { //remove col
		//	tmp.erase(tmp.begin() + index);
		//}
		for (size_t i = 0; i < FilledField.size(); i++) { //must remove from the top
			if (std::find(EmptyRow.begin(), EmptyRow.end(), i) == EmptyRow.end()) break;
			tmp.erase(tmp.begin());
		}
		tmp.erase(tmp.end() - 1); //the bottom unseen line
		//DebugPrintPlayField(tmp);
		//## commented out, dont want this functionality in fumenconvert
		//for (size_t i = 0; i < tmp.size(); i++) { //remove selected rows from each col
		//	for (auto const index : EmptyCol) {
		//		//std::cout << "(" << index << tmp[i][index] << ")" << std::endl;
		//		tmp[i].erase(tmp[i].begin() + index);
		//	}
		//}
		//DebugPrintPlayField(tmp);
		Output = tmp;
	}
	return Output;
}

PlayFieldFilled FumenConvert::GetSection(PlayFieldFilled PFFilled, int height, int width) {
	PlayFieldFilled Output;
	PlayFieldFilled PFF(PFFilled.end() - std::min(height, (int)PFFilled.size()), PFFilled.end());
	for (const auto& col : PFF) {
		std::vector<bool> tmp(col.begin(), col.begin() + width);
		Output.push_back(tmp);
	}
	return Output;
}

std::string FumenConvert::TrimFumen(std::string Fumen) {
	std::string format = "v115@";
	std::string delim = "?";
	Fumen = Fumen.erase(Fumen.find(format), format.length()); //now ready for use
	size_t index = 0;
	while (index != std::string::npos) {
		index = Fumen.find(delim);
		if (index == std::string::npos) break;
		Fumen = Fumen.erase(index, delim.length());
	}
	return Fumen;
}

PlayFieldFilled FumenConvert::ConvertFumen(std::string Fumen, int height, int width) {
	PlayFieldFilled field;
	Fumen = TrimFumen(Fumen);
	std::vector<int> IntVecRep = StringToIntVec(Fumen);
	TBoard BoardRep = IntVecToBoard(IntVecRep);
	field = BoardToPFF(BoardRep);
	field = RemoveExtraRows(field);
	field = 
	field = GetSection(field, height, width);
	return field;
}

void FumenConvert::test_FumenToField() {
	FumenConvert FuConv;
	std::string FuRep = "v115@MgA8HeA8AeA8BeB8DeD8AeA8AeA8BeC8AeA8AeB8Be?A8AeB8AeA8AeB8CeA8AeA8BeA8AeA8AeB8AeF8AeG8DeA8A?eA8AeA8AeA8JeAgH";
	PlayFieldFilled field = FuConv.ConvertFumen(FuRep, 4, 10);
	for (auto col : field) {
		for (auto mino : col) {
			std::cout << mino;
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}