#pragma once
#include "..\Misc\CommonFunctions.h"

class CollisionChecker {
private:
	bool test(std::vector<std::vector<bool>> input, int i, int j);

	bool FillOutOfBounds(TPlayFieldFilled current, int x, int y, bool FillBool);

public:
	CollisionChecker();

	bool HaveCollision(TPlayFieldFilled a, TPlayFieldFilled b);

	bool HaveCollisionPartial(std::vector<std::vector<bool>> a, std::vector<std::vector<bool>> b, bool FillBool);

};
