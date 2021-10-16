#include <vector>
#include <algorithm>
#include <chrono>
#include <iosfwd>

#include "CommonDataTypes.h"
#include "PieceData/PieceDataInherit.h"

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
	std::vector<PlayFieldFilled> RemoveExtraLines(std::vector<PlayFieldFilled> FilledFields) { //removes full lines of blank, they shouldn't be there for extension
		//DebugPrintVector is from DebugFunctions.h
		std::vector<PlayFieldFilled> Output = {};
		for (auto FilledField : FilledFields) {
			PlayFieldFilled tmp = FilledField;
			std::vector<int> EmptyRow = {};
			for (size_t i = 0; i < FilledField.size(); i++) { //check if row is empty
				auto row = FilledField[i];
				auto it = std::find(row.begin(), row.end(), true);
				if (it == row.end()) {
					EmptyRow.push_back(i); //no filled mino in row, mark as empty
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
					EmptyCol.push_back(row);
				}
			}
			//remove from back to front, to avoid shifting index issues
			std::reverse(EmptyRow.begin(), EmptyRow.end());
			std::reverse(EmptyCol.begin(), EmptyCol.end());
			//DebugPrintVector(EmptyRow);
			//DebugPrintVector(EmptyCol);
			//DebugPrintPlayField(tmp);
			for (auto index : EmptyRow) { //remove col
				tmp.erase(tmp.begin() + index);
			}
			//DebugPrintPlayField(tmp);
			for (size_t i = 0; i < tmp.size(); i++) { //remove selected rows from each col (uneeded actually)
				for (auto const index : EmptyCol) {
					//std::cout << "(" << index << tmp[i][index] << ")" << std::endl;
					tmp[i].erase(tmp[i].begin() + index);
				}
			}
			//DebugPrintPlayField(tmp);
			Output.push_back(tmp);
		}
		return Output;
	}

	//void Test_RemoveExtraLines() {
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

	std::vector<std::vector<int>> RecurseInsertLines(int MaxNum, int SelectNum, int LengthLeft) { //maxnum starts with 1, selectnum starts with 0
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

	std::vector<std::vector<int>> ReturnInsertLines(int MaxNum, int Length) { //sort of over-engineered this
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

	//void Test_ReturnInsertLines() { //test the funcion of ReturnInsertLines
	//	auto a = ReturnInsertLines(5, 3);
	//	for (auto i : a) {
	//		std::cout << "( ";
	//		for (auto j : i) {
	//			std::cout << j << " ";
	//		}
	//		std::cout << "),";
	//	}
	//};

	/*std::vector<std::vector<PlayFieldFilled>> ReturnAllRotations() {
		//using tetrominodata, return all possible rotation states
		std::vector<std::vector<PlayFieldFilled>> tmp;
		TetrominoDatav2 data;
		std::vector<int> RepeatInterval = { 2, 4, 4, 1, 2, 4, 2 }; // 'I', 'L', 'J', 'O', 'S', 'T', 'Z' //saves time instead of using merge

		for (int i = 0; i < 7; i++) { //for tetrominos, there are 4 states for 7 pieces
			std::vector<PlayFieldFilled> section;
			for (int j = 0; j < RepeatInterval[i]; j++) {
				section.push_back(data.PieceFilled(i, j));
			}
			tmp.push_back(section);
		}
		return tmp;
	}*/

	std::vector<TCacheItem> ReturnAllRotations_2() {
		//using tetrominodata, return all possible rotation states
		std::vector<TCacheItem> Output;
		TetrominoDatav2 data;
		std::vector<int> RepeatInterval = { 2, 4, 4, 1, 2, 4, 2 }; // 'I', 'L', 'J', 'O', 'S', 'T', 'Z' //saves time instead of using merge

		for (int i = 0; i < 7; i++) { //for tetrominos, there are 4 states for 7 pieces
			for (int j = 0; j < RepeatInterval[i]; j++) {
				Output.push_back({ data.PieceFilled(i, j), i });
			}
		}
		return Output;
	}

	/*std::vector<PlayFieldFilled> ExpandToNHigh(std::vector<PlayFieldFilled> FilledFields, int MaxHeight) { //find height of the playfield, insert blanks with combinatorics in mind
		std::vector<PlayFieldFilled> Output;
		for (auto FilledField : FilledFields) {
			FilledField = RemoveExtraLines({ FilledField })[0];
			int FieldHeight = FilledField.size();
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
		}
		return Output;
	}*/

	std::vector<TCacheItem> ExpandToNHigh_2(std::vector<TCacheItem> CacheItems, int MaxHeight) { //find height of the playfield, insert blanks with combinatorics in mind
		std::vector<TCacheItem> Output;
		for (auto CacheItem : CacheItems) {
			PlayFieldFilled FilledField = CacheItem.Field;
			Piece piece = CacheItem.piece;
			FilledField = RemoveExtraLines({ FilledField })[0];
			int FieldHeight = FilledField.size();
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
				Output.push_back({ FilledField, piece });
			}
			if (flipped_placement) { //insert empty columns
				for (auto choice : InsertLineChoice) {
					auto tmp = FilledField;
					for (auto line : choice) { //inserted front to back, should bypass shifting issues (boilerplate)
						tmp.insert(tmp.begin() + line, EmptyLine);
					}
					Output.push_back({ tmp, piece });
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
					Output.push_back({ tmp, piece });
				}
			}
		}
		return Output;
	}

	//void Test_ReturnData() { //return all fields with inserted lines for 4 lines and tetrominos
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

	/*std::vector<PlayFieldFilled> ReturnShiftedPossibilities(std::vector<PlayFieldFilled> FilledFields, int MaxWidth) {
		std::vector<PlayFieldFilled> Output;
		for (auto Field : FilledFields) {
			int FieldWidth = Field[0].size();
			for (auto& col : Field) {
				for (int i = 0; i < MaxWidth - FieldWidth; i++) {
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
	}*/

	std::vector<TCacheItem> ReturnShiftedPossibilities_2(std::vector<TCacheItem> CacheItems, int MaxWidth) {
		std::vector<TCacheItem> Output;
		for (auto CacheItem : CacheItems) {
			PlayFieldFilled Field = CacheItem.Field;
			Piece piece = CacheItem.piece;
			int FieldWidth = Field[0].size();

			if (FieldWidth > MaxWidth) continue; //no shiftings possible if field is smaller than field width

			for (auto& col : Field) {
				for (int i = 0; i < MaxWidth - FieldWidth; i++) { //for maxfield equal or larger than the field width
					col.push_back(0);
				}
			}
			Output.push_back({ Field, piece }); //normal position
			for (int i = 0; i < MaxWidth - FieldWidth; i++) {
				//remove right side, append left side
				for (auto& col : Field) {
					col.pop_back();
					col.insert(col.begin(), 0);
				}
				Output.push_back({ Field, piece });
			}
		}
		return Output;
	}

	std::vector<std::vector<int>> ReturnInvolvedRow(std::vector<TCacheItem> CacheItems) {
		std::vector<std::vector<int>> Output = {};
		for (size_t i = 0; i < CacheItems[0].Field[0].size(); i++) {
			Output.push_back({});
		}

		for (size_t CacheItem = 0; CacheItem < CacheItems.size(); CacheItem++) {
			//std::cout << "Item:\n";
			//for (auto i : CacheItems[CacheItem].Field) {
			//	for (auto j : i) {
			//		std::cout << j;
			//	}
			//	std::cout << "\n";
			//}
			//std::cout << "\n";
			std::vector<bool> RowFilled;
			RowFilled.resize(CacheItems[0].Field[0].size());
			//accumulate all filled cells into the rows
			for (size_t col = 0; col < CacheItems[CacheItem].Field.size(); col++) {
				for (size_t row = 0; row < CacheItems[CacheItem].Field[col].size(); row++) {
					RowFilled[row] = RowFilled[row] or CacheItems[CacheItem].Field[col][row];
				}
			}
			//std::cout << "Collect:\n";
			//for (auto i : RowFilled) {
			//	std::cout << i;
			//}
			//std::cout << "\n";
			//add entry to each row + 1 row extra (for touching pieces)
			/*std::vector<bool> NewRow;
			NewRow.resize(RowFilled.size());
			for (size_t i = 0; i < RowFilled.size(); i++) {
				if ((i != 0) and (RowFilled[i - 1])) {
					NewRow[i] = true;
				}
			}
			for (size_t i = 0; i < RowFilled.size(); i++) {
				if ((i != RowFilled.size()) and (RowFilled[i+1])) {
					NewRow[i] = true;
				}
			}
			RowFilled = NewRow;*/ //not needed in new approach
			//std::cout << "Collect:\n";
			//for (auto i : RowFilled) {
			//	std::cout << i;
			//}
			//std::cout << "\n";
			//std::cout << "\n";

			for (size_t i = 0; i < RowFilled.size(); i++) {
				if (!RowFilled[i]) { continue; }
				Output[i].push_back(CacheItem);
			}
		}
		return Output;
	}

public:
	/*std::vector<std::vector<PlayFieldFilled>> ReturnData(int height, int width) {
		auto StartTime = std::chrono::system_clock::now();
		std::vector<std::vector<PlayFieldFilled>> Output;
		auto input = ReturnAllRotations();
		for (auto section : input) {
			auto result = ExpandToNHigh(section, height);
			auto b = ReturnShiftedPossibilities(result, width);
			Output.push_back(b);
		}
		auto EndTime = std::chrono::system_clock::now();
		std::cout << "Time taken for cache: " << std::chrono::duration_cast<std::chrono::microseconds>(EndTime - StartTime).count() / 1000.0 << "ms\n";
		return Output;
	} //also do cache on what the lines of the results include, so it can be used to select relavent pieces*/

	TCache ReturnData_2(int height, int width) {
		auto StartTime = std::chrono::system_clock::now();
		TCache Output;

		std::vector<TCacheItem> input = ReturnAllRotations_2();
		std::vector<TCacheItem> result = ExpandToNHigh_2(input, height);
		result = ReturnShiftedPossibilities_2(result, width);
		Output.PossibleFields = result;

		Output.InvolvedRow = ReturnInvolvedRow(result);

		auto EndTime = std::chrono::system_clock::now();
		std::cout << "Time taken for cache: " << std::chrono::duration_cast<std::chrono::microseconds>(EndTime - StartTime).count() / 1000.0 << "ms\n";

		return Output;
	}
};