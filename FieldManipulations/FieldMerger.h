#pragma once
#include <unordered_set>
#include <algorithm>
#include <unordered_map>
#include <map>

#include "../Misc/CommonDataTypes.h"
#include "../Misc/Conversion/FormatConverter.h"

namespace std {

	template <>
	struct hash<PFFSol>
	{
		std::size_t operator()(const PlayFieldFilled& PFF) const
		{
			using std::size_t;
			using std::hash;

			TConverter converter;
			return (hash<string>()(converter.PFFToString(PFF)));
		}
	};

}

class FieldMerger : protected TConverter {
private:
	std::vector<PresentPieces> MergeSol(std::vector<PresentPieces> Original, std::vector<PresentPieces> New);

public:
	std::vector<FuSol> MergeDuplicates(std::vector<FuSol> FuSols);

	std::vector<PFFSol> MergeDuplicates(std::vector<PFFSol> PFFSols);

	std::vector<StrSol> MergeDuplicates(std::vector<StrSol> PFFSols);
};