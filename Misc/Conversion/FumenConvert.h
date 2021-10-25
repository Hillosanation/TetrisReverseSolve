#pragma once
#include "../CommonDataTypes.h"
#include <string>

class FumenConvert { //uses tetris-fumen parser by knewjade thrpugh v8
private: //debug
	//FumenConvert(int argc, char* argv[]) {
	//	// Initialize V8.
	//	v8::V8::Initialize();
	//}

	//PlayFieldFilled FumenToField(std::string Fumen) {
	//	v8::Isolate::CreateParams create_params;
	//	create_params.array_buffer_allocator =
	//		v8::ArrayBuffer::Allocator::NewDefaultAllocator();
	//	v8::Isolate* isolate = v8::Isolate::New(create_params);
	//	v8::Local<v8::String> v8String = v8::String::NewFromUtf8(isolate, "dd", v8::NewStringType::kNormal).ToLocalChecked();
	//}

	struct TBoardInfo {
		int BlockNum;
		int Consecutive;

		TBoardInfo(int extBlockNum, int extConsecutive) : BlockNum(extBlockNum + 8), Consecutive(extConsecutive - 1) {}; //convert to the storage format instead of the actual values

		TBoardInfo(const TBoardInfo& other) : BlockNum(other.BlockNum), Consecutive(other.Consecutive) {};

		~TBoardInfo() {};

		//bool operator==(const TBoardInfo& other) {
		//	if ((this->BlockNum == other.BlockNum) && (this->Consecutive == other.Consecutive)) {
		//		return true;
		//	}
		//	else {
		//		return false;
		//	}
		//}
	};
	typedef std::vector<TBoardInfo> TBoard;
	typedef std::vector<bool> TPFFilledLine;
	const int FieldWidth = 10;
	const std::string FumenString = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"; //weird that this isn't just ascii tbh

	TBoard MakePartialBoardRepresentation(const TPFFilledLine& PFFLine);

	TBoard MakeBoardRepresentation(const PlayFieldFilled& PFFilled);

	PlayFieldFilled ExpandToFullWidth(PlayFieldFilled PFFilled);

	std::vector<int> ConvertTo64(TBoard Board);

	std::string IntVecToFuString(std::vector<int> IntVec);

	void test_FieldToFumen();

	std::string TrimFumen(std::string Fumen);

	std::vector<int> StringToIntVec(std::string Fumen);

	TBoard IntVecToBoard(std::vector<int> IntVecRep);

	PlayFieldFilled BoardToPFF(TBoard BoardRep);

	PlayFieldFilled RemoveExtraRows(PlayFieldFilled FilledField);

	PlayFieldFilled GetSection(PlayFieldFilled PFFilled, int height, int width);

	void test_FumenToField();

public:
	std::string ConvertPFF(PlayFieldFilled PFFilled);

	PlayFieldFilled ConvertFumen(std::string Fumen, int height, int width);

};