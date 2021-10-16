#pragma once
#include <olcPixelGameEngine.h>

class SettingsMenu {
	//IMPROVE: put customizations here
public:
	std::vector<int> Movement = { 120, 0 };
	std::vector<int> Dropping = { 0, 0 };
	std::vector<int> HistoryTraversal = { 300, 100 };
	//std::vector<char> UserKeys = { '\x25', '\x27', '\x28', '\x20', '\x43', '\x5A', '\xA0', '\x58', '\x52', '\x51', '\x12' };	//left, right, soft, hard, hold, ccw, 180, cw, reset, cycle bag, alt(for order)
	std::vector<olc::Key> BoardKeys = {
		olc::Key::LEFT,
		olc::Key::RIGHT,
		olc::Key::DOWN,
		olc::Key::SPACE,
		olc::Key::C,
		olc::Key::Z,
		olc::Key::SHIFT,
		olc::Key::X,
		olc::Key::W,
		olc::Key::Q,
		olc::Key::CTRL,
		olc::Key::CTRL,//reserved for easier left/right navigation implementation
		olc::Key::R,
		olc::Key::K1,
		olc::Key::K2,
		olc::Key::K3,
		olc::Key::K4,
		olc::Key::K5,
		olc::Key::K6,
		olc::Key::K7,
		olc::Key::A,
		olc::Key::P,
	};

	const std::vector<bool> HasInterrupt = { true, true, true, false, false, false, false, false, false, false, true, true, false, false, false, false, false, false, false, false, false, false };
	
	std::vector<olc::Key> PieceOrderKeys = {
		olc::Key::I,
		olc::Key::J,
		olc::Key::L,
		olc::Key::O,
		olc::Key::S,
		olc::Key::T,
		olc::Key::Z,
		olc::Key::ESCAPE,
		olc::Key::BACK,
		olc::Key::DEL,
		olc::Key::ENTER,
	};
	
	std::vector<olc::Key> PerfectClearKeys = {
			olc::Key::I,
			olc::Key::J,
			olc::Key::L,
			olc::Key::O,
			olc::Key::S,
			olc::Key::T,
			olc::Key::Z,
			olc::Key::K1,
			olc::Key::K2,
			olc::Key::K3,
			olc::Key::K4,
			olc::Key::K5,
			olc::Key::K6,
			olc::Key::K7,
			olc::Key::LEFT,
			olc::Key::RIGHT,
			olc::Key::SHIFT, //(!)
			olc::Key::SHIFT, //{^}
			olc::Key::K8, //{*}
			olc::Key::BACK,
			olc::Key::DEL,
			olc::Key::ESCAPE,
			olc::Key::ENTER,
	};


	std::vector<olc::Pixel> ColorOrder = { olc::CYAN, olc::BLUE, olc::Pixel(255, 128, 0), olc::YELLOW, olc::GREEN, olc::DARK_MAGENTA, olc::RED, olc::GREY , olc::WHITE };
	enum class CellStates { I, J, L, O, S, T, Z, X, Blank };
	size_t NumOfPreview = 5;
	bool GhostEnabled = false;

};