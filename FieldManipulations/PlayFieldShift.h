#pragma once
#include "..\Misc\CommonFunctions.h"
#include <olcPixelGameEngine.h>

class PlayFieldShift {
protected:
	template<typename T>
	void AppendLeft(std::vector<std::vector<T>>& a, int amount, T FillVal);

	template<typename T>
	void AppendRight(std::vector<std::vector<T>>& a, int amount, T FillVal);

	template<typename T>
	void AppendUp(std::vector<std::vector<T>>& a, int amount, T FillVal);

	template<typename T>
	void AppendDown(std::vector<std::vector<T>>& a, int amount, T FillVal);
public:
	template<typename T>
	std::vector<std::vector<T>> ShiftField(std::vector<std::vector<T>> field, olc::vi2d offset, T replaceVal);

	std::pair<TPlayFieldFilled, TPlayFieldFilled> ShiftFields(TPlayFieldFilled Cur, TPlayFieldFilled Sol, olc::vi2d offset);

};

