#pragma once
#include <utility>
#include <vector>
#include <functional>

typedef std::vector<std::vector<int>> TPlayField; //IMPROVE: replace with this type for readability
typedef std::vector<std::vector<bool>> TPlayFieldFilled;

int positive_modulo(int i, int n);

bool InRange(int value, int low, int high); //inclusive for both bounds

typedef std::function<bool(int, int)> TCondition;

template<typename elementType>
std::vector<std::vector<elementType>> ConstructNestedVectorByElements(std::vector<size_t> LoopBounds, TCondition condition, std::function<elementType(int, int)> TrueVal, std::function<elementType(int, int)> FalseVal);
template<typename elementType>
std::vector<std::vector<elementType>> ConstructNestedVectorByElements(std::vector<size_t> LoopBounds, TCondition condition, elementType TrueVal, elementType FalseVal);

bool IsFieldEmpty(TPlayField Field, int compare);