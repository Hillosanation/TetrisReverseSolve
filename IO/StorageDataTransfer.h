#pragma once
#include <vector>
#include <string>

#include "../Misc/CommonDataTypes.h"
#include "../Misc/Conversion/FormatConverter.h"
#include "../SettingsData.h"

struct StorageDataTransfer : protected TConverter {
private:
	void OutputPresentPiece(PresentPieces PPiece, std::ofstream& os);

	std::string PathPrefix = "./";

public:
	std::vector<StrFieldStrPiece> ReadInputCSV(std::string InputName);

	void WriteOutputCSV(std::vector<StrFieldStrPiece> SFieldSPieces, std::string OutputName);

	void ReadSettings(const std::string& SettingsName, SettingsData& Settings);

	std::vector<PFFSol> DecodeCSVFormat(std::vector<StrFieldStrPiece> SFieldSPieces, SettingsData& Settings);

	std::vector<StrFieldStrPiece> EncodeCSVFormat(std::vector<PFFSol> PFFSols, SettingsData& Settings);
};
