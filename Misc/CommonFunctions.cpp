#include "CommonFunctions.h"
#include <vector>
#include <utility>
// uncomment to disable assert()
// #define NDEBUG
#include <assert.h>
#include <functional>

int positive_modulo(int i, int n) {
	return (i % n + n) % n;
}

bool InRange(int value, int low, int high) { //inclusive for both bounds
	return ((low <= value) and (value <= high));
}

template<typename elementType> //idk how to make template work, IMPROVE
std::vector<std::vector<elementType>> ConstructNestedVectorByElements(std::vector<size_t> LoopBounds, TCondition condition, std::function<elementType(int, int)> TrueVal, std::function<elementType(int, int)> FalseVal) { //IMPROVE: more discriptive name
	assert((LoopBounds[0] != 0) and (LoopBounds[1] != 0));
	std::vector<std::vector<elementType>> TempField;
	std::vector<elementType> TempCol;
	TempField.reserve(LoopBounds[0]);
	TempCol.reserve(LoopBounds[0]);

	for (size_t i = 0; i < LoopBounds[0]; i++) {
		TempCol.clear();
		for (size_t j = 0; j < LoopBounds[1]; j++)
		{
			if (condition(i, j)) {
				TempCol.push_back(TrueVal(i, j));		//IMPROVE: seems like there is no need for true/falseval, as it's always T/F anyways
			}
			else {
				//bool tmp = FalseVal;
				TempCol.push_back(FalseVal(i, j));
			}
		}
		TempField.push_back(TempCol);
	}
	return TempField;
}


template std::vector<std::vector<int>> ConstructNestedVectorByElements(std::vector<size_t> LoopBounds, TCondition condition, std::function<int(int, int)> TrueVal, std::function<int(int, int)> FalseVal);
template std::vector<std::vector<bool>> ConstructNestedVectorByElements(std::vector<size_t> LoopBounds, TCondition condition, std::function<bool(int, int)> TrueVal, std::function<bool(int, int)> FalseVal);

//std::vector<std::vector<int>> ConstructNestedVectorByElements(std::vector<size_t> LoopBounds, TCondition condition, std::function<int(int, int)> TrueVal, std::function<int(int, int)> FalseVal) {
//	assert((LoopBounds[0] != 0) and (LoopBounds[1] != 0));
//	std::vector<std::vector<int>> TempField;
//	std::vector<int> TempCol;
//	TempField.reserve(LoopBounds[0]);
//	TempCol.reserve(LoopBounds[0]);
//
//	for (size_t i = 0; i < LoopBounds[0]; i++) {
//		TempCol.clear();
//		for (size_t j = 0; j < LoopBounds[1]; j++)
//		{
//			if (condition(i, j)) {
//				TempCol.push_back(TrueVal(i, j));		//IMPROVE: seems like there is no need for true/falseval, as it's always T/F anyways
//			}
//			else {
//				//bool tmp = FalseVal;
//				TempCol.push_back(FalseVal(i, j));
//			}
//		}
//		TempField.push_back(TempCol);
//	}
//	return TempField;
//}
//
//std::vector<std::vector<bool>> ConstructNestedVectorByElements(std::vector<size_t> LoopBounds, TCondition condition, std::function<bool(int, int)> TrueVal, std::function<bool(int, int)> FalseVal) {
//	assert((LoopBounds[0] != 0) and (LoopBounds[1] != 0));
//	std::vector<std::vector<bool>> TempField;
//	std::vector<bool> TempCol;
//	TempField.reserve(LoopBounds[0]);
//	TempCol.reserve(LoopBounds[0]);
//
//	for (size_t i = 0; i < LoopBounds[0]; i++) {
//		TempCol.clear();
//		for (size_t j = 0; j < LoopBounds[1]; j++)
//		{
//			if (condition(i, j)) {
//				TempCol.push_back(TrueVal(i, j));		//IMPROVE: seems like there is no need for true/falseval, as it's always T/F anyways
//			}
//			else {
//				//bool tmp = FalseVal;
//				TempCol.push_back(FalseVal(i, j));
//			}
//		}
//		TempField.push_back(TempCol);
//	}
//	return TempField;
//}
//
template<typename elementType>
std::vector<std::vector<elementType>> ConstructNestedVectorByElements(std::vector<size_t> LoopBounds, TCondition condition, elementType TrueVal, elementType FalseVal) {
	assert((LoopBounds[0] != 0) and (LoopBounds[1] != 0));
	std::vector<std::vector<elementType>> TempField;
	std::vector<elementType> TempCol;

	for (size_t i = 0; i < LoopBounds[0]; i++) {
		TempCol.clear();
		for (size_t j = 0; j < LoopBounds[1]; j++)
		{
			if (condition(i, j)) {
				TempCol.push_back(TrueVal);
			}
			else {
				//bool tmp = FalseVal;
				TempCol.push_back(FalseVal);
			}
		}
		/*std::cout << i << " | TempCol:" << std::endl;
		for (size_t j = 0; j < TempCol.size(); j++)
		{
			std::cout << TempCol[j] << " ";
		}
		std::cout << std::endl;*/


		TempField.push_back(TempCol);
		/*std::cout << "TempField:" << std::endl;
		for (size_t i = 0; i < TempField.size(); i++)
		{
			for (size_t j = 0; j < TempField[i].size(); j++)
			{
				std::cout << TempField[i][j] << " ";
			}
			std::cout << std::endl;
		}*/
	}
	/*std::cout << "Final:" << std::endl;
	for (size_t i = 0; i < TempField.size(); i++)
	{
		for (size_t j = 0; j < TempField[i].size(); j++)
		{
			std::cout << TempField[i][j] << " ";
		}
		std::cout << std::endl;
	}*/
	return TempField;
}
//
//std::vector<std::vector<int>> ConstructNestedVectorByElements(std::vector<size_t> LoopBounds, TCondition condition, int TrueVal, int FalseVal) {
//	assert((LoopBounds[0] != 0) and (LoopBounds[1] != 0));
//	std::vector<std::vector<int>> TempField;
//	std::vector<int> TempCol;
//
//	for (size_t i = 0; i < LoopBounds[0]; i++) {
//		TempCol.clear();
//		for (size_t j = 0; j < LoopBounds[1]; j++)
//		{
//			if (condition(i, j)) {
//				TempCol.push_back(TrueVal);
//			}
//			else {
//				//bool tmp = FalseVal;
//				TempCol.push_back(FalseVal);
//			}
//		}
//		TempField.push_back(TempCol);
//	}
//	return TempField;
//}
//
//std::vector<std::vector<bool>> ConstructNestedVectorByElements(std::vector<size_t> LoopBounds, TCondition condition, bool TrueVal, bool FalseVal) {
//	assert((LoopBounds[0] != 0) and (LoopBounds[1] != 0));
//	std::vector<std::vector<bool>> TempField;
//	std::vector<bool> TempCol;
//
//	for (size_t i = 0; i < LoopBounds[0]; i++) {
//		TempCol.clear();
//		for (size_t j = 0; j < LoopBounds[1]; j++)
//		{
//			if (condition(i, j)) {
//				TempCol.push_back(TrueVal);
//			}
//			else {
//				//bool tmp = FalseVal;
//				TempCol.push_back(FalseVal);
//			}
//		}
//		/*std::cout << i << " | TempCol:" << std::endl;
//		for (size_t j = 0; j < TempCol.size(); j++)
//		{
//			std::cout << TempCol[j] << " ";
//		}
//		std::cout << std::endl;*/
//
//
//		TempField.push_back(TempCol);
//		/*std::cout << "TempField:" << std::endl;
//		for (size_t i = 0; i < TempField.size(); i++)
//		{
//			for (size_t j = 0; j < TempField[i].size(); j++)
//			{
//				std::cout << TempField[i][j] << " ";
//			}
//			std::cout << std::endl;
//		}*/
//	}
//	/*std::cout << "Final:" << std::endl;
//	for (size_t i = 0; i < TempField.size(); i++)
//	{
//		for (size_t j = 0; j < TempField[i].size(); j++)
//		{
//			std::cout << TempField[i][j] << " ";
//		}
//		std::cout << std::endl;
//	}*/
//	return TempField;
//}

template std::vector<std::vector<int>> ConstructNestedVectorByElements<int>(std::vector<size_t> LoopBounds, TCondition condition, int TrueVal, int FalseVal);
template std::vector<std::vector<bool>> ConstructNestedVectorByElements<bool>(std::vector<size_t> LoopBounds, TCondition condition, bool TrueVal, bool FalseVal);

bool IsFieldEmpty(TPlayField Field, int compare) {
	for (auto i : Field) {
		for (auto j : i) {
			if (j != compare) {
				return false;
			}
		}
	}
	return true;
}

bool IsInteger(std::string& s) {
	return (s.find_first_not_of("1234567890") == std::string::npos);
}
