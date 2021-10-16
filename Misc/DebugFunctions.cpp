#include "DebugFunctions.h"
#include <iostream>

template<class T>
void DebugPrintLambda(T x) {
	for (size_t i = 0; i < 24; i++) {
		for (size_t j = 0; j < 10; j++)
		{
			std::cout << x(i, j);
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

template<typename elementType>
void DebugPrintPlayField(std::vector<std::vector<elementType>> field) {
	for (auto i : field) {
		for (auto j : i) {
			std::cout << j;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

template<typename elementType>
void DebugPrintPlayFields(std::vector<std::vector<std::vector<elementType>>> fields) { //assums fields are the same height
	for (size_t i = 0; i < fields[0].size(); i++) {
		for (size_t j = 0; j < fields.size(); j++) {
			for (size_t k = 0; k < fields[j][0].size(); k++) {
				std::cout << fields[j][i][k];
			}
			std::cout << " ";
		}
		std::cout << std::endl;
	}
}

template<typename elementType>
void DebugPrintVector(std::vector<elementType> vec) {
	for (auto i : vec) {
		std::cout << i;
	}
	std::cout << std::endl;
}

template void DebugPrintVector<int>(std::vector<int> vec);