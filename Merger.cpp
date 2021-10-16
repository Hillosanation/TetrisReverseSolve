#include <unordered_set>
#include <algorithm>
#include <unordered_map>
#include <map>

#include "CommonDataTypes.h"
#include "ReverseSolveFunctions.h"

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
	std::vector<PresentPieces> MergeSol(std::vector<PresentPieces> Original, std::vector<PresentPieces> New) {
		std::unordered_set<std::string> uSet;
		std::vector<PresentPieces> tmp;
		tmp.insert(tmp.end(), Original.begin(), Original.end()); //merge
		tmp.insert(tmp.end(), New.begin(), New.end());
		for (auto const i : tmp) { //removes duplicates by moving into set
			uSet.insert(SolToString(i));
		}
		tmp = {};
		for (auto const i : uSet) {
			tmp.push_back(StringToSol(i)); //convert set back to vec
		}
		//std::sort(tmp.begin(), tmp.end()); //not really required, can be added if needed
		return tmp;
	}

public:
	std::vector<FuSol> MergeDuplicates(std::vector<FuSol> FuSols) { //combines identical fields, grouping solves together
		std::unordered_map<std::string, FuSol> HashTable;
		for (auto const i : FuSols) {
			auto it = HashTable.find(i.Fumen);
			if (it == HashTable.end()) { //no matching fumen, add a new fumen
				HashTable[i.Fumen] = i;
				continue;
			}
			it->second.Solves = MergeSol(it->second.Solves, i.Solves); //matching fumen, combine sol together
		}
		//IMPROVE: this conversion might not be necessary, but im attempting to be SOLID
		std::vector<FuSol> Output = {};
		for (auto i : HashTable) {
			Output.push_back(i.second);
		}
		return Output;
	}

	std::vector<PFFSol> MergeDuplicates(std::vector<PFFSol> PFFSols) { //combines identical fields, grouping solves together
		std::map<PlayFieldFilled, PFFSol> HashTable;
		std::vector<PFFSol> Output = {};
		for (auto const i : PFFSols) {
			auto it = HashTable.find(i.PFFilled);
			if (it == HashTable.end()) { //not found
				HashTable[i.PFFilled] = i;
				continue;
			}
			it->second.Solves = MergeSol(it->second.Solves, i.Solves); //found, append
		}
		for (auto i : HashTable) {
			Output.push_back(i.second);
		}
		return Output;
	}
};