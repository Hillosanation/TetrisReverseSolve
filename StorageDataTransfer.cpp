#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>

#include "CommonDataTypes.h"
#include "ReverseSolveFunctions.h"

struct StorageDataTransfer : protected TConverter {
private:
	void OutputPresentPiece(PresentPieces PPiece, std::ofstream& os) {
		for (auto Piece : PPiece) {
			os << Piece;
		}
	}

	//void TestIO() {
	//	StorageDataTransfer DataAccess; //I/O test
	//	Merger merge;
	//	std::vector<FuSol> FileInput = DataAccess.ReadInputFile();
	//	/*for (auto i : FileInput) { //print out what was read
	//		std::cout << "Fumen: " << i.Fumen << " | ";
	//		std::cout << "Solves: ";
	//		for (auto j : i.Solves) {
	//			std::cout << j << " ";
	//		}
	//		std::cout << std::endl;
	//	}*/
	//	FileInput = merge.MergeDuplicates(FileInput);
	//	DataAccess.WriteOutputFile(FileInput);
	//}

public:
	std::vector<FuSol> ReadInputFile() { //parses stored csv 
		std::ifstream fs;
		fs.open("../test.csv", std::fstream::in);
		std::string line;
		bool FirstLine = true;

		std::vector<FuSol> tmpFuSols;

		while (std::getline(fs, line)) { //reads a line from fs
			if (FirstLine) { //gives column names, ignore them
				FirstLine = !FirstLine;
				continue;
			}
			FuSol tmpFuSol;
			std::stringstream linestream(line); //a stream but data is like a string
			std::string value;
			bool FumenPart = true;
			while (std::getline(linestream, value, ',')) { //reads a value from linestream
				if (FumenPart) {
					tmpFuSol.Fumen = value;
					FumenPart = !FumenPart;
					continue;
				}
				PresentPieces tmpSol = StringToSol(value);
				tmpFuSol.Solves.push_back(tmpSol);
				//std::cout << value << " ";
			}
			if (tmpFuSol.Solves.size() == 0) { //no previous entries, add empty entry
				tmpFuSol.Solves.push_back({});
			}
			tmpFuSols.push_back(tmpFuSol);
			//std::cout << std::endl;
		};
		fs.close();

		return tmpFuSols;
	}

	void WriteOutputFile(std::vector<FuSol> FuSols) { //converts into the 
		std::ofstream os;
		os.open("../testout.csv", std::fstream::trunc);
		if (!os) { //doesn't exist
			std::ofstream file("../testout.csv");
			os.open("../testout.csv", std::fstream::trunc);
		}
		os << "fumen code, solution pieces" << std::endl;
		for (auto i : FuSols) {
			os << i.Fumen << ",";
			for (size_t j = 0; j < i.Solves.size(); j++) {
				if (j == i.Solves.size() - 1) { //last value
					OutputPresentPiece(i.Solves.at(j), os);
					break;
				}
				OutputPresentPiece(i.Solves.at(j), os);
				os << ",";
			}
			os << std::endl;
		}

	}
};