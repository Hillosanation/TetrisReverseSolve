#include <chrono>
#include <iostream>

#include "FieldResizer.h"

PlayFieldFilled FieldResizer::RemoveExtraLines(PlayFieldFilled FilledField) { //removes full lines of blank, they shouldn't be there for extension
	//DebugPrintVector is from DebugFunctions.h
	bool KeepBool = false;
	PlayFieldFilled tmp = FilledField;
	int width = (int)tmp[0].size(); //the width before any reduction
	std::vector<int> EmptyRow = {};
	for (size_t i = 0; i < FilledField.size(); i++) { //check if row is empty
		auto row = FilledField[i];
		auto it = std::find(row.begin(), row.end(), KeepBool);
		if (it == row.end()) {
			EmptyRow.push_back((int)i); //no filled mino in row, mark as empty
		}
	}
	std::vector<int> EmptyCol = {};
	for (size_t row = 0; row < FilledField[0].size(); row++) { //check if col is empty
		bool Empty = true;
		for (size_t col = 0; col < FilledField.size(); col++) {
			if (FilledField[col][row] == KeepBool) { //filled, cannot remove
				Empty = false;
				break;
			}
		}
		if (Empty) {
			EmptyCol.push_back((int)row);
		}
	}
	std::reverse(EmptyRow.begin(), EmptyRow.end());
	//DebugPrintVector(EmptyRow);
	//DebugPrintVector(EmptyCol);
	//DebugPrintPlayField(tmp);
	for (auto index : EmptyRow) { //remove col
		tmp.erase(tmp.begin() + index);
	}
	//DebugPrintPlayField(tmp);
	/*for (size_t i = 0; i < tmp.size(); i++) { //remove selected rows from each col (uneeded actually)
		for (auto const index : EmptyCol) {
			//std::cout << "(" << index << tmp[i][index] << ")" << std::endl;
			tmp[i].erase(tmp[i].begin() + index);
		}
	}*/
	for (int i = width - 1; i >= 0 ; i--) { //remove selected rows from each col from only the right
		if (std::find(EmptyCol.begin(), EmptyCol.end(), i) == EmptyCol.end()) break;
		for (size_t j = 0; j < tmp.size(); j++) {
			tmp[j].erase(tmp[j].end() - 1);
		}
	}
	for (int i = 0; i < width; i++) { //remove selected rows from each col from only the left
		if (std::find(EmptyCol.begin(), EmptyCol.end(), i) == EmptyCol.end()) break;
		for (size_t j = 0; j < tmp.size(); j++) {
			tmp[j].erase(tmp[j].begin()); //take account the shifting
		}
	}
	//DebugPrintPlayField(tmp);
	return tmp;
}

//void FieldResizer::Test_RemoveExtraLines() {
//	TetrominoDatav2 data;
//	PlayFieldFilled Field = data.PieceFilled(3, 1);
//	auto result = RemoveExtraLines({ Field });
//	std::cout << "Result:" << std::endl;
//	for (auto i : result[0]) {
//		for (auto j : i) {
//			std::cout << j;
//		}
//		std::cout << std::endl;
//	}
//}

std::vector<std::vector<int>> FieldResizer::RecurseInsertLines(int MaxNum, int SelectNum, int LengthLeft) { //maxnum starts with 1, selectnum starts with 0
	/*std::cout << "RecurseInsertLines: " << MaxNum << " " << SelectNum << " len: " << LengthLeft << std::endl;*/
	//terminate if no length left
	if (LengthLeft <= 0) { //capture negatives, flag error?
		/*std::cout << "t\n";*/
		return {};
	}
	else if (LengthLeft == 1) {
		/*std::cout << "s\n";*/
		return { {SelectNum} };
	}
	//terminate if remaining num equals the lengthleft, ie there is only one possible combination
	if ((MaxNum - 1) <= (SelectNum + LengthLeft - 1)) { //inequality is failsafe, equal is enough in theory
		//return all numbers from select to (maxnum - 1)
		std::vector<int> tmp;
		for (int i = SelectNum; i < MaxNum; i++) {
			tmp.push_back(i);
		}
		/*std::cout << "r\n";*/
		return { tmp };
	};
	//perform recusion since no terminating conditions apply
	std::vector<std::vector<int>> Output = {};
	for (int i = SelectNum + 1; i < MaxNum - LengthLeft + 2; i++) {
		/*std::cout << "call\n";*/
		auto tmp = RecurseInsertLines(MaxNum, i, LengthLeft - 1);
		for (auto& j : tmp) {
			j.insert(j.begin(), SelectNum); //prepend the results with the current selected number
		}
		Output.insert(Output.end(), tmp.begin(), tmp.end());
	}
	/*std::cout << "n\n";*/
	return Output;
}

std::vector<std::vector<int>> FieldResizer::ReturnInsertLines(int MaxNum, int Length) { //sort of over-engineered this
	std::vector<std::vector<int>> Output;
	for (int i = 0; i < MaxNum - Length + 1; i++) {
		auto tmp = RecurseInsertLines(MaxNum, i, Length);
		/*std::cout << "Output: \n";
		for (auto i : tmp) {
			std::cout << "( ";
			for (auto j : i) {
				std::cout << j << " ";
			}
			std::cout << "),";
		}
		std::cout << "\n";*/
		Output.insert(Output.end(), tmp.begin(), tmp.end());
	}
	return Output;
}

//void FieldResizer::Test_ReturnInsertLines() { //test the funcion of ReturnInsertLines
//	auto a = ReturnInsertLines(5, 3);
//	for (auto i : a) {
//		std::cout << "( ";
//		for (auto j : i) {
//			std::cout << j << " ";
//		}
//		std::cout << "),";
//	}
//};

std::vector<PlayFieldFilled> FieldResizer::ExpandToNHigh(PlayFieldFilled FilledField, int MaxHeight) { //find height of the playfield, insert blanks with combinatorics in mind
	std::vector<PlayFieldFilled> Output;
	FilledField = RemoveExtraLines(FilledField);
	int FieldHeight = (int)FilledField.size();
	bool flipped_placement = false;

	std::vector<bool> EmptyLine;
	for (auto i : FilledField[0]) {
		EmptyLine.push_back(0);
	}
	//unique fields generated is n choose FieldHeight (potential sanity check)
	if (FieldHeight > MaxHeight / 2.0) {
		FieldHeight = MaxHeight - FieldHeight;
		flipped_placement = true; //reduce computing time... maybe?
	}
	auto InsertLineChoice = ReturnInsertLines(MaxHeight, FieldHeight); //might be better to just calculate all the possibilities and search in memory
	//insert the emplty/filledfields accordingly;output the result
	if ((InsertLineChoice.size() == 0) and (FilledField.size() == MaxHeight)) { //there is only one way to place the field (in tetrominos, that is vertical I in 4 high)
		Output.push_back(FilledField);
	}
	if (flipped_placement) { //insert empty columns
		for (auto choice : InsertLineChoice) {
			auto tmp = FilledField;
			for (auto line : choice) { //inserted front to back, should bypass shifting issues (boilerplate)
				tmp.insert(tmp.begin() + line, EmptyLine);
			}
			Output.push_back(tmp);
		}
	}
	else { //insert lines from filledfields
		for (auto choice : InsertLineChoice) {
			std::vector<std::vector<bool>> tmp = {};
			for (size_t i = 0; i < MaxHeight - FilledField.size(); i++) {
				tmp.insert(tmp.begin(), EmptyLine);
			}
			for (size_t i = 0; i < choice.size(); i++) {
				tmp.insert(tmp.begin() + choice[i], FilledField[i]); //inserted front to back, should bypass shifting issues (boilerplate)
			}
			Output.push_back(tmp);
		}
	}
	return Output;
}

//void FieldResizer::Test_ReturnData() { //return all fields with inserted lines for 4 lines and tetrominos
//	auto result = ReturnData(4, 10);
//	for (auto section : result) {
//		for (auto board : section) {
//			for (auto col : board) {
//				for (auto mino : col) {
//					std::cout << mino;
//				}
//				std::cout << "\n";
//			}
//			std::cout << "\n";
//		}
//		std::cout << "\n";
//	}
//	std::cout << "\n";
//}

std::vector<PlayFieldFilled> FieldResizer::ReturnShiftedPossibilities(std::vector<PlayFieldFilled> FilledFields, int MaxWidth) {
	std::vector<PlayFieldFilled> Output;
	for (auto Field : FilledFields) {
		int FieldWidth = (int)Field[0].size();

		if (FieldWidth > MaxWidth) continue; //no shiftings possible if field is smaller than field width

		for (auto& col : Field) {
			for (int i = 0; i < MaxWidth - FieldWidth; i++) { //for maxfield equal or larger than the field width
				col.push_back(0);
			}
		}
		Output.push_back(Field); //normal position
		for (int i = 0; i < MaxWidth - FieldWidth; i++) {
			//remove right side, append left side
			for (auto& col : Field) {
				col.pop_back();
				col.insert(col.begin(), 0);
			}
			Output.push_back(Field);
		}
	}
	return Output;
}

//std::vector<PlayFieldFilled> FieldResizer::ReturnData(std::vector<PlayFieldFilled> input, int height, int width) {
//	auto StartTime = std::chrono::system_clock::now();
//
//	std::vector<PlayFieldFilled> result = ExpandToNHigh(input, height);
//	result = ReturnShiftedPossibilities(result, width);
//
//	auto EndTime = std::chrono::system_clock::now();
//	std::cout << "Time taken for expansion: " << std::chrono::duration_cast<std::chrono::microseconds>(EndTime - StartTime).count() / 1000.0 << "ms\n";
//
//	return result;
//}

std::vector<PlayFieldFilled> FieldResizer::ReturnData(PlayFieldFilled input, int height, int width) {
	std::vector<PlayFieldFilled> result = ExpandToNHigh(input, height);
	result = ReturnShiftedPossibilities(result, width);
	return result;
}

std::vector<PFFSol> FieldResizer::ExpandPFF(PFFSol PFFSolItem, int height, int width) {std::vector<PFFSol> Output;
	std::vector<PlayFieldFilled> expanded = ReturnData(PFFSolItem.PFFilled, height, width);
	for (auto field : expanded) {
		Output.push_back({field, PFFSolItem.Solves});
	}
	return Output;
}

std::vector<PFFSol> FieldResizer::ReducePFFs(std::vector<PFFSol> PFFSols, SettingsData& Settings) {
	if ((bool)std::stoi(Settings.GetValue(SettingsData::SettingsEnum::SQUASH_FINAL_FIELDS)) == false) return PFFSols;
	auto StartTime = std::chrono::system_clock::now();

	std::vector<PFFSol> Output;
	for (auto PFFSol : PFFSols) {
		Output.push_back({ RemoveExtraLines(PFFSol.PFFilled), PFFSol.Solves });
	}

	auto EndTime = std::chrono::system_clock::now();
	std::cout << "Time taken for reduction: " << std::chrono::duration_cast<std::chrono::microseconds>(EndTime - StartTime).count() / 1000.0 << "ms\n";
	return Output;
}

std::vector<PFFSol> FieldResizer::ExpandPFFs(std::vector<PFFSol> PFFSols, SettingsData& Settings) {
	if ((bool)std::stoi(Settings.GetValue(SettingsData::SettingsEnum::EXPAND_INIT_FIELDS)) == false) return PFFSols;
	auto StartTime = std::chrono::system_clock::now();

	std::vector<PFFSol> Output;
	int height = std::stoi(Settings.GetValue(SettingsData::SettingsEnum::FIELD_HEIGHT));
	int width = std::stoi(Settings.GetValue(SettingsData::SettingsEnum::FIELD_WIDTH));
	for (auto PFFSol : PFFSols) {
		auto expanded = ExpandPFF(PFFSol, height, width);
		Output.insert(Output.begin(), expanded.begin(), expanded.end());
	}

	auto EndTime = std::chrono::system_clock::now();
	std::cout << "Time taken for expansion: " << std::chrono::duration_cast<std::chrono::microseconds>(EndTime - StartTime).count() / 1000.0 << "ms\n";
	return Output;
}
