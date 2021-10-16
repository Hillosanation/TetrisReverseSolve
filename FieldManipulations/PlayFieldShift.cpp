#include "PlayFieldShift.h"

template<typename T>
void PlayFieldShift::AppendLeft(std::vector<std::vector<T>>& a, int amount, T FillVal) {
	for (auto& i : a) {
		for (int j = 0; j < amount; j++) {
			i.insert(i.begin(), FillVal);
		}
	}
}

template<typename T>
void PlayFieldShift::AppendRight(std::vector<std::vector<T>>& a, int amount, T FillVal) {
	for (auto& i : a) {
		for (int j = 0; j < amount; j++) {
			i.push_back(FillVal);
		}
	}
}

template<typename T>
void PlayFieldShift::AppendUp(std::vector<std::vector<T>>& a, int amount, T FillVal) {
	std::vector<T> tmp;
	for (size_t i = 0; i < a[0].size(); i++) {
		tmp.push_back(FillVal);
	}
	for (int j = 0; j < amount; j++) {
		a.insert(a.begin(), tmp);
	}
}

template<typename T>
void PlayFieldShift::AppendDown(std::vector<std::vector<T>>& a, int amount, T FillVal) {
	std::vector<T> tmp;
	for (size_t i = 0; i < a[0].size(); i++) {
		tmp.push_back(FillVal);
	}
	for (int j = 0; j < amount; j++) {
		a.push_back(tmp);
	}
}

template<typename T>
std::vector<std::vector<T>> PlayFieldShift::ShiftField(std::vector<std::vector<T>> field, olc::vi2d offset, T replaceVal) {
	if (offset.y > 0) { //down
		AppendDown(field, std::abs(offset.y), replaceVal);
	}
	else if (offset.y < 0) { //up
		AppendUp(field, std::abs(offset.y), replaceVal);
	}
	if (offset.x > 0) { //right
		AppendRight(field, std::abs(offset.x), replaceVal);
	}
	else if (offset.x < 0) { //left
		AppendLeft(field, std::abs(offset.x), replaceVal);
	}
	return field;
}

std::pair<TPlayFieldFilled, TPlayFieldFilled> PlayFieldShift::ShiftFields(TPlayFieldFilled Cur, TPlayFieldFilled Sol, olc::vi2d offset) { //offsets cur
	if (offset.y > 0) { //down
		PlayFieldShift::AppendUp(Cur, std::abs(offset.y), false);
		PlayFieldShift::AppendDown(Sol, std::abs(offset.y), true);
	}
	else if (offset.y < 0) { //up
		PlayFieldShift::AppendDown(Cur, std::abs(offset.y), false);
		PlayFieldShift::AppendUp(Sol, std::abs(offset.y), true);
	}
	if (offset.x > 0) { //right
		PlayFieldShift::AppendLeft(Cur, std::abs(offset.x), false);
		PlayFieldShift::AppendRight(Sol, std::abs(offset.x), true);
	}
	else if (offset.x < 0) { //left
		PlayFieldShift::AppendRight(Cur, std::abs(offset.x), false);
		PlayFieldShift::AppendLeft(Sol, std::abs(offset.x), true);
	}
	return std::make_pair(Cur, Sol);
}

template std::vector<std::vector<bool>> PlayFieldShift::ShiftField(std::vector<std::vector<bool>> field, olc::vi2d offset, bool replaceVal);
template std::vector<std::vector<int>> PlayFieldShift::ShiftField(std::vector<std::vector<int>> field, olc::vi2d offset, int replaceVal);
