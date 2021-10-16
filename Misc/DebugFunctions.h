#pragma once
#include <vector>

template<class T>
void DebugPrintLambda(T x);

template<typename elementType>
void DebugPrintPlayField(std::vector<std::vector<elementType>> field);

template<typename elementType>
void DebugPrintPlayFields(std::vector<std::vector<std::vector<elementType>>> fields); //assums fields are the same height

template<typename elementType>
void DebugPrintVector(std::vector<elementType> vec);