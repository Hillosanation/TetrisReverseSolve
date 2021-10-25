#pragma once
#include <vector>
#include <tuple>
#include <string>
struct SettingsData {
	enum class SettingsEnum { //unused..?
		FIELD_WIDTH=0, FIELD_HEIGHT, PIECE_DEPTH,
		INPUT_FORMAT, OUTPUT_FORMAT, RESIDUE_LOG, SFINDER_FILTER, RAW_POSSIBLE_FILTER,
		INPUT_FILE_CSV, OUTPUT_FILE_CSV, RESIDUE_FILE_CSV, PATH_TO_SFINDER,
		OPTIMIZE
	};
	struct SearchItem {
		const std::string Keyword;
		std::string Value;
	};

	std::vector<SearchItem> SearchData =
	{
		{"FIELD_WIDTH",			"10"				},
		{"FIELD_HEIGHT",		"4"					},
		{"PIECE_DEPTH",			"1"					},
		{"INPUT_FORMAT",		"0"					},
		{"OUTPUT_FORMAT",		"0"					},
		{"RESIDUE_LOG",			"0"					},
		{"SFINDER_FILTER",		"0"					},
		{"RAW_POSSIBLE_FILTER",	"0"					},
		{"INPUT_FILE_CSV",		"input.csv"			},
		{"OUTPUT_FILE_CSV",		"output.csv"		},
		{"RESIDUE_FILE_CSV",	"residue.csv"		},
		{"PATH_TO_SFINDER",		"sfinder.jar"		},
		{"OPTIMIZE",			"1"					}
	};

	std::string GetValue(SettingsEnum Enum) {
		return SearchData[static_cast<int>(Enum)].Value;
	}

};